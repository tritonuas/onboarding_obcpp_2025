#include "ticks/end.hpp"

#include <iostream>

EndTick::EndTick(std::shared_ptr<MissionState> state)
    : Tick(state, TickID::End) {}

void EndTick::init() {

}


Tick* EndTick::tick() {

	return nullptr;
}