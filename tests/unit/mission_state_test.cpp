#include <gtest/gtest.h>
#include <chrono>

#include "core/mission_state.hpp"

// Verifies that a default-constructed MissionState has the expected initial values.
TEST(MissionStateTest, DefaultsAreInitialized) {
    MissionState mission_state;

    // Expect defaults: not prepared, zero progress, and "None" tick name.
    EXPECT_FALSE(mission_state.is_prepared);
    EXPECT_EQ(mission_state.task_progress, 0);
    EXPECT_EQ(mission_state.current_tick_name, "None");
}

// Demonstrates testing a method: when there is no current tick,
// doTick() should return a 1 second wait duration.
TEST(MissionStateTest, DoTickWithoutCurrentTickWaitsOneSecond) {
    MissionState mission_state;

    auto wait_duration = mission_state.doTick();

    EXPECT_EQ(wait_duration, std::chrono::milliseconds(1000));
}
