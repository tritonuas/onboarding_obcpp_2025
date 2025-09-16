#include "core/mission_state.hpp"
#include <iostream>

MissionState::MissionState() : current_tick(nullptr) {
    // Initialize our simplified state variables
    this->is_prepared = false;
    this->task_progress = 0;
    std::cout << "Mission State initialized." << std::endl;
}

MissionState::~MissionState() {
    // Cleanup
    if (current_tick != nullptr) {
        delete current_tick;
    }
}


void MissionState::setInitialTick(Tick* first_tick) {
    this->current_tick = first_tick;
    if (this->current_tick != nullptr) {
        // Lock the mutex before writing to shared data
        std::lock_guard<std::mutex> lock(state_mut);
        this->current_tick_name = "MissionPrepTick"; // Manually set the name
        std::cout << "Transitioning to initial tick: " << this->current_tick_name << std::endl;
        this->current_tick->init();
    }
}

std::chrono::milliseconds MissionState::doTick() {
    if (current_tick == nullptr) {
        // State where there is no tick == end of mission ?
        return std::chrono::milliseconds(1000);
    }

    Tick* next_tick = current_tick->tick();

    // Once a tick returns a new tick, the obc state changes
    if (next_tick != nullptr) {
        std::cout << "--- STATE TRANSITION ---" << std::endl;

        delete current_tick;
        current_tick = next_tick;

        // Lock the mutex before writing to shared data
        std::lock_guard<std::mutex> lock(state_mut);
        this->current_tick_name = "CompletionTick";
        std::cout << "Transitioning to new tick: " << this->current_tick_name << std::endl;
        current_tick->init();
    }
    // If next_tick was nullptr, we do nothing and stay in the current state.

    return current_tick->getWait();
}