// include/ticks/Tick.hpp
#ifndef INCLUDE_TICKS_TICK_HPP_
#define INCLUDE_TICKS_TICK_HPP_

#include <chrono>
#include <memory>

class MissionState; 

class Tick {
public:
    // The constructor takes the shared state object
    explicit Tick(std::shared_ptr<MissionState> state);
    virtual ~Tick() = default;

    // Called once when the state is transitioned to
    virtual void init() {}

    // The main logic loop for the tick
    virtual Tick* tick() = 0;

    // Controls how often tick() is called
    virtual std::chrono::milliseconds getWait() const = 0;

protected:
    std::shared_ptr<MissionState> state;
};

#endif // INCLUDE_TICKS_TICK_HPP_