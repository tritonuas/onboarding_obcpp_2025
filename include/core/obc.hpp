#ifndef INCLUDE_CORE_OBC_HPP_
#define INCLUDE_CORE_OBC_HPP_

#include <memory>
#include "core/mission_state.hpp"
#include "network/gcs.hpp" 

class OBC {
public:
    OBC();
    void run();

private:
    std::shared_ptr<MissionState> state;
    std::unique_ptr<GCSServer> gcs_server;
};
#endif // INCLUDE_CORE_OBC_HPP_