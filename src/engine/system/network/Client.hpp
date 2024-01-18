#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <asio.hpp>
#include <cstdint>

using asio::ip::udp;

namespace ge {
    struct Client {
        uint32_t clientId;
        uint32_t sceneId;
        udp::endpoint endpoint;
    };
} // namespace ge

#endif /* !CLIENT_HPP_ */
