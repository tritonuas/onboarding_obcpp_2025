#include "ticks/verify.hpp"
#include "ticks/end.hpp"
#include "core/mission_state.hpp"

#include <iostream>

VerifyTick::VerifyTick(std::shared_ptr<MissionState> state)
    : Tick(state, TickID::Verify) {}

void VerifyTick::init() {
	state->image_state = MissionState::ImageState::WAITING;
}

std::chrono::milliseconds VerifyTick::getWait() const {
    return std::chrono::milliseconds(250);
}


Tick* VerifyTick::tick() {
	// Enums are set in the gcs handler

	// Waiting for verification from handler
	// if (state->image_state == MissionState::ImageState::WAITING) {
	// 	return new VerifyTick(state);
	// } else if (state->image_state == MissionState::ImageState::VALID) {
	// 	// Image is valid, we can end the mission
	// 	return new EndTick(state);
	// } else if (state->image_state == MissionState::ImageState::INVALID) {
	// 	// Image is invalid, we need to capture a new image
	// 	return new CameraTick(state);
	// }

	// Uncomment above and comment below to actually verify the image
	return new EndTick(state);
	
}