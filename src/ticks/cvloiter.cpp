#include "ticks/cvloiter.hpp"
#include "ticks/end.hpp"
#include "core/mission_state.hpp"
#include "ticks/switch.hpp"
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
CVLoiterTick::CVLoiterTick(std::shared_ptr<MissionState> state) : Tick(state, TickID::CVLoiter) {
    this->state = state;

}

/**
 * This is the initialization function for the tick. It is called once when the
 * tick is first started.
 */
void CVLoiterTick::init() {

}

/**
 * This is the main function for the tick. It is called periodically based on
 * how long getWait() returns (the quantization of tick time is dependent on the 
 * tick).
 *
 * At the end of the tick, return the next tick to transition to. If the tick
 * should stay the same, return nullptr
 */
Tick* CVLoiterTick::tick() {
    if (state->has_captured == true) {
        return new SwitchTick(state);
    }
}

/**
 * This function returns how long the tick should wait before calling tick() 
 * again.
 */
std::chrono::milliseconds CVLoiterTick::getWait() const {
    return std::chrono::milliseconds(250);
}