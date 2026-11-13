#include "ticks/cvloiter.hpp"
#include "ticks/switch.hpp"
#include <iostream>
#include <chrono>

CVLoiterTick::CVLoiterTick(std::shared_ptr<MissionState> state) 
        : Tick(state, TickID::CVLoiter) {
    // ^w^
    state->captureFinished = false;
}

void CVLoiterTick::init() {
    
}

Tick* CVLoiterTick::tick() {
    if (state->captureFinished) {
        return new SwitchTick(state);
    } else {
        return nullptr;
    }
}

std::chrono::milliseconds CVLoiterTick::getWait() const {
    return std::chrono::milliseconds(250);
}
