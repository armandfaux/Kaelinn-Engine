#include "NetworkSystem.hpp"

using namespace kln;
using asio::ip::udp;

NetworkSystem::NetworkSystem(SystemType type, asio::io_context &ioContext, const std::string &port)
    : _socket(ioContext, udp::endpoint(udp::v4(), std::atoi(port.c_str()))) {
    _name = "Network";
    _systemType = SystemType::server;

    std::cout << "[SYSTEM] Network System successfully created\n";
    std::cout << "-> [Server NETWORK] Port: " << port << "\n";

    startReceive();
}

NetworkSystem::NetworkSystem(SystemType type, asio::io_context &ioContext, const std::string &host,
                             const std::string &port)
    : _socket(ioContext, udp::endpoint(udp::v4(), 0)) {
    _name = "Network";
    _systemType = SystemType::client;

    std::cout << "[SYSTEM] Network System successfully created\n";
    udp::resolver resolver(ioContext);
    udp::resolver::results_type endpoints = resolver.resolve(udp::v4(), host, port);
    _serverEndpoint = *endpoints.begin();
    std::cout << "-> [Client NETWORK] Host: " << host << "\n";

    Event event;

    event.type = Type::clientConnection;
    event.clientId = _id;

    send(event, 1);
    startReceive();
}

void NetworkSystem::startReceive() {
    _socket.async_receive_from(
        asio::buffer(_recvBuffer), _remoteEndpoint, [this](std::error_code ec, std::uint32_t bytes_recvd) {
            if (!ec && bytes_recvd > 0) {
                publishEvent(
                    deserialize(bytes_recvd, std::string(_recvBuffer.begin(), _recvBuffer.begin() + bytes_recvd)));
                startReceive();
            } else {
                std::cerr << "Receive failed: " << ec.message() << "\n";
                startReceive();
            }
        });
}

void NetworkSystem::update(std::shared_ptr<Scene> &scene) {
    if (_systemType == SystemType::server) {
        transferEntityPositions(scene);
    }

    // Send the local events over the network
    for (auto &event : _eventQueue) {
        if (_systemType == SystemType::client) {
            event.clientId = _id;
        }

        if (scene->getId()) {
            send(event, scene->getId());
        }
    }
}

void NetworkSystem::transferEntityPositions(std::shared_ptr<Scene> &scene) {
    for (auto &entity : scene->getEntities()) {
        if (entity->hasComp("Spatial")) {
            SpatialComp *spatialComp = dynamic_cast<SpatialComp *>(entity->getComp("Spatial").get());
            Event event{
                .type = Type::pos,
                .entityId1 = entity->getId(),
                // .entityName = entity->getName(),
                .pos = spatialComp->getPos(),
            };
            send(event, scene->getId());
        }
    }
}

Event NetworkSystem::deserialize(std::uint32_t bytesReceived, const std::string &data) {
    Event newEvent;

    try {
        std::string decompressedData;
        size_t decompressedLength = snappy::Uncompress(data.data(), data.size(), &decompressedData);

        std::istringstream is(decompressedData, std::ios::binary);
        cereal::BinaryInputArchive iarchive(is);
        iarchive(newEvent);
    } catch (std::exception &e) {
        std::cerr << "[WARNING] Exception while receiving an event: " << e.what() << "\n";
    }
    return newEvent;
}

void NetworkSystem::connectionCheck(Event &event) {
    if (_systemType == SystemType::server) {
        uint32_t clientId = getAvailableId(_clientIds, MAX_CLIENTS);

        if (clientId) {
            Client newClient{.clientId = clientId, .sceneId = 1, .endpoint = _remoteEndpoint};

            _clients.push_back(newClient);
            _clientIds.insert(clientId);
        } else {
            // TODO throw an exception
            std::cout << "[NETWORK] Maximum amount of concurrent clients reached\n";
            throw std::runtime_error("Maximum amount of concurrent clients reached\n");
        }

        Event response{.type = Type::clientConnection, .clientId = clientId};

        std::cout << "[NETWORK] Client " << clientId << " connected\n";
        event.clientId = clientId;
        send(response, 1);
    } else if (_id == 0) {
        _id = event.clientId;
    }
}

void NetworkSystem::publishEvent(Event event) {
    if (event.type == Type::clientConnection) {
        connectionCheck(event);
    }

    if (event.type == Type::switchScene) {
        for (auto &client : _clients) {
            if (client.clientId == event.clientId) {
                client.sceneId = event.sceneId;
            }
        }
    }

    // Publish the event locally if it's a valid one
    if (event.type != Type::unknown) {
        _publisher.publish(event);
    }
}

NetworkSystem::~NetworkSystem() { _socket.close(); }
