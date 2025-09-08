// include/core/MissionState.hpp
#ifndef INCLUDE_CORE_MISSION_STATE_HPP_
#define INCLUDE_CORE_MISSION_STATE_HPP_

#include <memory>
#include <chrono>
#include "ticks/tick.hpp"

class MissionState {
public:
    // Public state variables for ticks to interact with
    bool is_prepared = false;
    int task_progress = 0;

    MissionState();
    ~MissionState();

    // The method that runs the current tick and handles transitions
    std::chrono::milliseconds doTick();

    // Method for the OBC to set the very first tick
    void setInitialTick(Tick* first_tick);

private:
    Tick* current_tick;
};

#endif // INCLUDE_CORE_MISSION_STATE_HPP_