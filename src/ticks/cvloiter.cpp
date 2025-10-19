#include "ticks/cvloiter.hpp"
#include "ticks/switch.hpp"
#include "core/mission_state.hpp"
#include "ticks/end.hpp"

#include <iostream>

CVLoiterTick::CVLoiterTick(std::shared_ptr<MissionState> state)
    : Tick(state, TickID::CVLoiter) {}

std::chrono::milliseconds CVLoiterTick::getWait() const {
    return std::chrono::milliseconds(250);
}

Tick* CVLoiterTick::tick() {
    std::lock_guard<std::mutex> lock(state->state_mut);
    if (state->loiter_finished) {
        return new EndTick(state);
    }
    if (state->has_captured) {
        state->has_captured = false;
        return new SwitchTick(state);
    }
    return nullptr;
}
