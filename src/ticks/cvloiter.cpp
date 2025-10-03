#include "ticks/cvloiter.hpp"
#include "ticks/switch.hpp"
#include "ticks/camera.hpp"
#include "core/mission_state.hpp"

#include <iostream>

CVLoiterTick::CVLoiterTick(std::shared_ptr<MissionState> state)
    : Tick(state, TickID::CVLoiter) {}

void CVLoiterTick::init() {

}

std::chrono::milliseconds CVLoiterTick::getWait() const {
    return std::chrono::milliseconds(250);
}


Tick* CVLoiterTick::tick() {

	if (state->has_captured) {
		std::cout << "Switching to SwitchTick" << std::endl;
		return new SwitchTick(state);
	} else {
		return new CVLoiterTick(state);
	}
}