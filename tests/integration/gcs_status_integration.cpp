#include <iostream>
#include <thread>
#include <chrono>

#include <httplib.h>

#include "core/mission_state.hpp"
#include "network/gcs.hpp"

int main() {
    // Prepare shared mission state
    auto state = std::make_shared<MissionState>();
    {
        std::lock_guard<std::mutex> lock(state->state_mut);
        state->is_prepared = true;
        state->task_progress = 42;
        state->current_tick_name = "MissionPrep";
    }

    // Start GCS server on a test port
    const uint16_t port = 18080;
    GCSServer server(port, state);

    // Give the server a brief moment to start
    std::this_thread::sleep_for(std::chrono::milliseconds(250));

    // Simple HTTP GET to /status
    httplib::Client client("localhost", port);
    auto res = client.Get("/status");

    if (!res) {
        std::cerr << "Request failed" << std::endl;
        return 1;
    }

    std::cout << "HTTP " << res->status << "\n";
    std::cout << res->body << std::endl;

    // Basic manual verification hint for humans
    std::cout << "Expect: status 200 and JSON with fields: current_tick_name, is_connected, mission_progress_percent" << std::endl;

    return res->status == 200 ? 0 : 2;
}

