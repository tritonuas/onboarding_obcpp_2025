#include "ticks/camera.hpp"
#include "ticks/cvloiter.hpp"
#include "ticks/switch.hpp"
#include "camera/mock.hpp"
#include "ticks/end.hpp"
#include "core/mission_state.hpp"
#include "camera/interface.hpp"

#include <iostream>

CvLoiterTick::CvLoiterTick(std::shared_ptr<MissionState> state) : Tick(state, TickID::CvLoiter) {}

void CvLoiterTick::init() {
  std::cout << "CvLoiterTick initialized" << std::endl;
}

Tick* CvLoiterTick::tick() {
  state->current_tick_name = "CvLoiter";

  switch (state->image_state)
  {
  case MissionState::ImageState::WAITING:
    /* code */
    return new CvLoiterTick(state);
  case MissionState::ImageState::INVALID:
    return new SwitchTick(state);
  case MissionState::ImageState::VALID:
    return new EndTick(state);
  default:
    break;
  }

}

std::chrono::milliseconds CvLoiterTick::getWait() const {
    return std::chrono::milliseconds(1000);  // Example: 1-second interval
}

