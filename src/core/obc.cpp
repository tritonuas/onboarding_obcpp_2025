#include "core/obc.hpp"
#include <memory>
#include <thread>

#include "ticks/mission_prep.hpp"

OBC::OBC() {
    // 1. Create the shared MissionState object that all ticks will use.
    this->state = std::make_shared<MissionState>();

    // 2. Create an instance of our mission's *first* tick.
    //    We pass the shared state to its constructor.
    Tick* initial_tick = new MissionPrepTick(this->state);

    // 3. Set this as the starting tick in the MissionState.
    //    This is analogous to the real project's setup.
    this->state->setInitialTick(initial_tick);
}

void OBC::run() {
    while (true) {
        auto wait_duration = this->state->doTick();
        std::this_thread::sleep_for(wait_duration);
    }
}