#include "ticks/switch.hpp"
#include "ticks/verify.hpp"
#include "ticks/camera.hpp"
#include "core/mission_state.hpp"

#include <iostream>

SwitchTick::SwitchTick(std::shared_ptr<MissionState> state)
    : Tick(state, TickID::Switch) {}

void SwitchTick::init() {

}

std::chrono::milliseconds SwitchTick::getWait() const {
    return std::chrono::milliseconds(250);
}


Tick* SwitchTick::tick() {

	// If we have an image, we need to verify it
	// If we don't have an image, we need to capture it
	// if (state->image.has_value()) {
	// 	return new VerifyTick(state);
	// } else {
	// 	return new CameraTick(state);
	// }

	// Uncomment above and comment below to use the actual camera
	return new VerifyTick(state);
}