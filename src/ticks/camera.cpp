#include "ticks/camera.hpp"
#include "ticks/switch.hpp"
#include "camera/mock.hpp"
#include "ticks/end.hpp"
#include "core/mission_state.hpp"
#include "ticks/cvloiter.hpp"

#include <iostream>

CameraTick::CameraTick(std::shared_ptr<MissionState> state) : Tick(state, TickID::Camera), camera() {}

void CameraTick::init() {
    // Optional setup code for camera
    std::cout << "CameraTick initialized." << std::endl;
}

Tick* CameraTick::tick() {
  state->current_tick_name = "Camera";
  std::optional<ImageData> image = camera.takePicture(std::chrono::milliseconds(600));
  // set image
  if(image.has_value()){
    state->image = image;
  }

  // return nullptr for next tick state
  return new CvLoiterTick(state);
}

std::chrono::milliseconds CameraTick::getWait() const {
    return std::chrono::milliseconds(1000);  // Example: 1-second interval
}