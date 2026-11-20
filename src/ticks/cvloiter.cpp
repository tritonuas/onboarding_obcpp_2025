#include "ticks/cvloiter.hpp"
#include "ticks/verify.hpp"

#include <chrono>
#include <iostream>

CVLoiter::CVLoiter(std::shared_ptr<MissionState> state)
    : Tick(state, TickID::CVLoiter){}

void CVLoiter::init() {
    state->has_captured = false;
}

Tick* CVLoiter::tick(){
    if (state->has_captured == true){
        return new VerifyTick(state);
    }
    return {};
}