#include "ticks/cameratick.hpp"
#include "ticks/cvloiter.hpp"
#include "ticks/end.hpp"
#include "core/mission_state.hpp"
#include "camera/mock.hpp"
#include <iostream>
#include <chrono>

using namespace std::chrono_literals;

/**
 * This is the constructor for the tick. All it does is pass through the mission
 * state.
 *
 * The following syntax uses an initializer list to call the parent constructor.
 * If you are unfamiliar with this syntax, you can read more about it
 * here: https://www.cppreference.com/w/cpp/language/initializer_list.html
 */
CameraTick::CameraTick(std::shared_ptr<MissionState> state) : Tick(state, TickID::Camera) {
    this->state = state;
    this->cam = std::make_unique<MockCamera>();
}

/**
 * This is the initialization function for the tick. It is called once when the
 * tick is first started.
 */
void CameraTick::init() {

}

/**
 * This is the main function for the tick. It is called periodically based on
 * how long getWait() returns (the quantization of tick time is dependent on the 
 * tick).
 *
 * At the end of the tick, return the next tick to transition to. If the tick
 * should stay the same, return nullptr
 */
Tick* CameraTick::tick() {
    this->state->image = this->cam->takePicture(250ms);
    std::cout << this->state->image.has_value() << std::endl;
    return new CVLoiterTick(state);
}

/**
 * This function returns how long the tick should wait before calling tick() 
 * again.
 */
std::chrono::milliseconds CameraTick::getWait() const {
    return std::chrono::milliseconds(50);
}