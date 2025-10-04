#include "ticks/cvloiter.hpp"
#include "ticks/switch.hpp"
#include "ticks/camera.hpp"
#include "core/mission_state.hpp"

#include <iostream>

CVLoiterTick::CVLoiterTick(std::shared_ptr<MissionState> state)
    : Tick(state, TickID::CVLoiter) {}

void CVLoiterTick::init() {
	std::cout << "Initializing CVLoiter..." << std::endl;
	state->has_captured = false;
}

std::chrono::milliseconds CVLoiterTick::getWait() const {
    return std::chrono::milliseconds(250);
}


Tick* CVLoiterTick::tick() {
	std::cout << "CVLoiterTick: has_captured = " << state->has_captured << std::endl;
	if (state->has_captured) {
		return new SwitchTick(state);
	} else {
		return nullptr;
	}
}