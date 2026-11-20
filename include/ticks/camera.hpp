#ifndef INCLUDE_TICKS_CAMERA_TICK_HPP_
#define INCLUDE_TICKS_CAMERA_TICK_HPP_

#include "ticks/tick.hpp"
#include "camera/mock.hpp"
#include "core/mission_state.hpp"
#include <chrono>

class CameraTick : public Tick {
public:
    /**
     * This is the constructor for the tick. All it does is pass through the mission
     * state.
     *
     * The following syntax uses an initializer list to call the parent constructor.
     * If you are unfamiliar with this syntax, you can read more about it
     * here: https://www.cppreference.com/w/cpp/language/initializer_list.html
     */
    CameraTick(std::shared_ptr<MissionState> state);

    /**
     * This is the initialization function for the tick. It is called once when the
     * tick is first started.
     */
    void init();

    /**
     * This is the main function for the tick. It is called periodically based on
     * how long getWait() returns (the quantization of tick time is dependent on the 
     * tick).
     *
     * At the end of the tick, return the next tick to transition to. If the tick
     * should stay the same, return nullptr
     */
    Tick* tick();

    /**
     * This function returns how long the tick should wait before calling tick() 
     * again.
     */
    std::chrono::milliseconds getWait() const;
private:
    MockCamera* camera;
    std::shared_ptr<MissionState> state;
};

#endif