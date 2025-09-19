#include <gtest/gtest.h>

#include <iostream>

using ::testing::InitGoogleTest;

int main(int argc, char** argv) {
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}