#include "ticks/tick.hpp"
#include "core/mission_state.hpp" 

Tick::Tick(std::shared_ptr<MissionState> state, TickID id) {
    this->state = state;
    this->id = id;
}