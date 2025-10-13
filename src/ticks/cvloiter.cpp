#include "ticks/camera.hpp"
#include "ticks/cvloiter.hpp"
#include "ticks/switch.hpp"
#include "camera/mock.hpp"
#include "ticks/end.hpp"
#include "core/mission_state.hpp"

#include <iostream>

CvLoiterTick::CvLoiterTick(std::shared_ptr<MissionState> state) : Tick(state, TickID::CvLoiter) {}

void CvLoiterTick::init() {
  std::cout << "CvLoiterTick initialized" << std::endl;
}

Tick* CvLoiterTick::tick() {
  state->current_tick_name = "CvLoiter";

  while(!state->has_captured) {
    std::cout << "waiting" << std::endl;
  }

  return new SwitchTick(state);
}

std::chrono::milliseconds CvLoiterTick::getWait() const {
    return std::chrono::milliseconds(1000);  // Example: 1-second interval
}

