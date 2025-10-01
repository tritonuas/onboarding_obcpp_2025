#ifndef INCLUDE_TICKS_CAMERA_TICK_HPP_
#define INCLUDE_TICKS_CAMERA_TICK_HPP_

#include <chrono>
#include "ticks/tick.hpp"
#include "camera/mock.hpp"

/* 
 * CameraTick: this is the tick that is responsible for executing the camera functionality
 */
class CameraTick : public Tick {
    public:

        // Constructor that passes the shared state to the base Tick class.
        explicit CameraTick(std::shared_ptr<MissionState> state);

        // Called once when this tick becomes the active state.
        void init() override;

        // The core logic that is executed repeatedly.
        Tick* tick() override;

    private:

        MockCamera camera;

};

#endif
