#ifndef INCLUDE_TICKS_CAMERA_TICK_HPP_
#define INCLUDE_TICKS_CAMERA_TICK_HPP_

#include <chrono>
#include "ticks/tick.hpp"
#include "camera/mock.hpp"

class CameraTick : public Tick {
    public:
        explicit CameraTick(std::shared_ptr<MissionState> state);

        void init() override;

        std::chrono::milliseconds getWait() const override;

        Tick* tick() override;

    private:

        MockCamera camera; // TODO: where should this realistically be?

};

#endif
