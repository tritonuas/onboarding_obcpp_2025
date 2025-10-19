#include "ticks/cvloiter.hpp"
#include "ticks/ids.hpp"
#include "core/mission_state.hpp" 
#include "ticks/switch.hpp"

    CVLoiterTick::CVLoiterTick(std::shared_ptr<MissionState> state) : Tick(state, TickID::CVLoiter){
    }
    Tick* CVLoiterTick::tick(){
        if(state->capture_called){
            state->capture_called = false;
            return new SwitchTick(state);
        }
    }
    std::chrono::milliseconds CVLoiterTick::getWait() const {
    return std::chrono::milliseconds(500);
}

void CVLoiterTick::init(){
    state->verify_next = true;
}