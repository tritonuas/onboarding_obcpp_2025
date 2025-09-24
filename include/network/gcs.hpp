#ifndef INCLUDE_NETWORK_GCS_HPP_
#define INCLUDE_NETWORK_GCS_HPP_

#include <httplib.h>
#include <thread>
#include <memory>
#include <mutex>
#include <cstdint>
#include "core/mission_state.hpp"

class GCSServer {
public:
    GCSServer(uint16_t port, std::shared_ptr<MissionState> state);
    ~GCSServer();

private:
    void _bindHandlers();
    httplib::Server server;
    std::thread server_thread;
    std::shared_ptr<MissionState> state;
};

#endif // INCLUDE_NETWORK_GCS_HPP_