// include/core/MissionState.hpp
#ifndef INCLUDE_CORE_MISSION_STATE_HPP_
#define INCLUDE_CORE_MISSION_STATE_HPP_

#include <chrono>
#include <memory>
#include <mutex>
#include <string>

#include "ticks/tick.hpp"

class MissionState {
 public:
    // Public state variables for ticks to interact with
    bool is_prepared = false;
    int task_progress = 0;
    std::string current_tick_name;

    // Mutex to protect shared data between the main loop and the server thread
    std::mutex state_mut;

    MissionState();
    ~MissionState();

    // The method that runs the current tick and handles transitions
    std::chrono::milliseconds doTick();

    // Method for the OBC to set the very first tick
    void setInitialTick(Tick* first_tick);

    // Method to get current tick ID
    TickID getTickID();

 private:
    Tick* current_tick;
};

#endif  // INCLUDE_CORE_MISSION_STATE_HPP_