#include "ticks/tick.hpp"
#include <chrono>

class CVLoiterTick : public Tick
{
    public:
    void init() override;
    explicit CVLoiterTick(std::shared_ptr<MissionState> state);
    std::chrono::milliseconds getWait() const override;
    Tick* tick() override;
};