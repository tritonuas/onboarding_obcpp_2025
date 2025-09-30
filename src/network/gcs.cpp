#include "network/gcs.hpp"
#include <iostream>
#include "network/gcs_routes.hpp"

GCSServer::GCSServer(uint16_t port, std::shared_ptr<MissionState> state)
    : state{state} {
    
    this->_bindHandlers();

    this->server_thread = std::thread([this, port]() {
        std::cout << "Starting GCS HTTP server on port " << port << std::endl;
        if (!this->server.listen("0.0.0.0", port)) {
            std::cerr << "ERROR: GCS server stopped!" << std::endl;
        }
    });
}

GCSServer::~GCSServer() {
    this->server.stop();
    this->server_thread.join();
}

void GCSServer::_bindHandlers() {
    // Use our macro to bind the GET /status route
    BIND_HANDLER(Get, status);
    BIND_HANDLER(Get, tick);
}