#ifndef INCLUDE_NETWORK_GCS_ROUTES_HPP_
#define INCLUDE_NETWORK_GCS_ROUTES_HPP_

#include <httplib.h>
#include <memory>
#include "core/mission_state.hpp"
#include "network/gcs_macros.hpp"

DEF_GCS_HANDLE(Get, status);
DEF_GCS_HANDLE(Get, tick);
DEF_GCS_HANDLE(Get, capture);

#endif // INCLUDE_NETWORK_GCS_ROUTES_HPP_