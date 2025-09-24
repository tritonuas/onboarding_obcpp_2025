// include/ticks/Tick.hpp
#ifndef INCLUDE_TICKS_TICK_HPP_
#define INCLUDE_TICKS_TICK_HPP_

#include <chrono>
#include <memory>
#include "ticks/ids.hpp"

class MissionState; 

class Tick {
public:
    // The constructor takes the shared state object
    Tick(std::shared_ptr<MissionState> state, TickID id);
    virtual ~Tick() = default;

    // Called once when the state is transitioned to
    virtual void init() {}

    // The main logic loop for the tick
    virtual Tick* tick() = 0;

    // Controls how often tick() is called
    virtual std::chrono::milliseconds getWait() const = 0;

    constexpr TickID getID() const { return this->id; }
    constexpr const char* getName() const { return TICK_ID_TO_STR(this->id); }
protected:
    std::shared_ptr<MissionState> state;
    TickID id;
};

#endif // INCLUDE_TICKS_TICK_HPP_