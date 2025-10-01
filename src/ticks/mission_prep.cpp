#include "ticks/mission_prep.hpp"
#include "core/mission_state.hpp"
#include "ticks/switch.hpp"

#include <iostream>

MissionPrepTick::MissionPrepTick(std::shared_ptr<MissionState> state)
    : Tick(state, TickID::MissionPrep) {}

void MissionPrepTick::init() {
    std::cout << "Starting Mission Preparation..." << std::endl;
    std::cout << "(Simulating system checks for 2 seconds)" << std::endl;

    state->is_prepared = false;
    state->task_progress = 0;

    start_time = std::chrono::steady_clock::now();
}


std::chrono::milliseconds MissionPrepTick::getWait() const {
    return std::chrono::milliseconds(250);
}

Tick* MissionPrepTick::tick() {
    auto now = std::chrono::steady_clock::now();
    auto time_elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start_time);

    if (time_elapsed.count() >= 2) {
        std::cout << "Preparation complete. System is ready." << std::endl;

        state->is_prepared = true;

        return new SwitchTick(state);

    } else {
        std::cout << "  - Preparing... (Current time: " << time_elapsed.count() << ")" << std::endl;

        return nullptr;
    }
}