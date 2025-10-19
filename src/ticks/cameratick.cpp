#include "ticks/cameratick.hpp"
#include "camera/mock.hpp"
#include "core/mission_state.hpp"
#include "ticks/cvloiter.hpp"

CameraTick::CameraTick(std::shared_ptr<MissionState> state) : Tick::Tick(state, TickID::Camera){
    this->state = state;
    this->camera = std::make_unique<MockCamera>();
}
Tick* CameraTick::tick(){
    auto photo = this->camera->takePicture(std::chrono::seconds(1));
    this->state->image = photo;
    return new CVLoiterTick(state);
}
std::chrono::milliseconds CameraTick::getWait() const {
    return std::chrono::milliseconds(50);
}

void CameraTick::init(){

}
