#include "ticks/end.hpp"

#include <iostream>

EndTick::EndTick(std::shared_ptr<MissionState> state)
    : Tick(state, TickID::End) {}

void EndTick::init() {

}

std::chrono::milliseconds EndTick::getWait() const {
    return std::chrono::milliseconds(250);
}


Tick* EndTick::tick() {

	return nullptr;
}