#ifndef NetworkSystem_HPP_
#define NetworkSystem_HPP_

#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <vector>

#include "../../EngineApi.hpp"
#include "../../component/spatial/SpatialComp.hpp"
#include "../../event/Event.hpp"
#include "../../event/Publisher.hpp"
#include "../../math/Time.hpp"
#include "../../math/Utils.hpp"
#include "../ASystem.hpp"
#include "Client.hpp"
#include "snappy.h"

using asio::ip::udp;

namespace kln {
#define MAX_CLIENTS 20

    class ENGINE_API NetworkSystem : public ASystem {
      public:
        NetworkSystem(SystemType type, asio::io_context &ioContext, const std::string &port);
        NetworkSystem(SystemType type, asio::io_context &ioContext, const std::string &host, const std::string &port);
        ~NetworkSystem();

        void update(std::shared_ptr<Scene> &scene) override;

        void startReceive();
        void connectionCheck(Event &event);
        void transferEntityPositions(std::shared_ptr<Scene> &scene);

        Event deserialize(std::uint32_t bytesReceived, const std::string &data);
        void publishEvent(Event event);

        template <typename T> void send(T &data, uint32_t sceneId) {
            std::ostringstream os(std::ios::binary);
            cereal::BinaryOutputArchive oarchive(os);
            oarchive(data);
            std::string serialized_str = os.str();

            // Compress
            std::string compressedData;
            std::size_t compressedLength =
                snappy::Compress(serialized_str.data(), serialized_str.size(), &compressedData);

            if (_systemType == SystemType::client) {
                _socket.async_send_to(asio::buffer(compressedData), _serverEndpoint,
                                      [this](const std::error_code &ec, std::uint32_t /*bytes_transferred*/) {
                                          if (ec) {
                                              std::cerr << "Send failed: " << ec.message() << "\n";
                                          }
                                      });
            } else {
                for (auto client : _clients) {
                    if (client.sceneId == sceneId) {
                        _socket.async_send_to(asio::buffer(compressedData), client.endpoint,
                                              [this](const std::error_code &ec, std::uint32_t /*bytes_transferred*/) {
                                                  if (ec) {
                                                      std::cerr << "Send failed: " << ec.message() << "\n";
                                                  }
                                              });
                    }
                }
            }
        }

      private:
        asio::ip::udp::socket _socket;
        asio::ip::udp::endpoint _remoteEndpoint;
        asio::ip::udp::endpoint _serverEndpoint;
        std::array<char, 1024> _recvBuffer;

        uint32_t _id = 0;
        std::unordered_set<uint32_t> _clientIds;
        std::vector<Client> _clients;
    };
} // namespace kln

#endif /* !NetworkSystem_HPP_ */