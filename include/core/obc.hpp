// include/core/OBC.hpp
#ifndef INCLUDE_CORE_OBC_HPP_
#define INCLUDE_CORE_OBC_HPP_

#include <memory>
#include "mission_state.hpp"

class OBC {
public:
    OBC();
    void run();

private:
    std::shared_ptr<MissionState> state;
};
#endif // INCLUDE_CORE_OBC_HPP_