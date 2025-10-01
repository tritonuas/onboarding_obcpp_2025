#include "network/gcs_routes.hpp"

#include <google/protobuf/util/json_util.h>

#include "core/mission_state.hpp"

// This needs to be included to get the definition of our proto message
#include "onboarding.pb.h"

DEF_GCS_HANDLE(Get, status) {
    // Create an instance of our Protobuf message
    OBCStatus status_proto;

    {
        // Lock the mutex to safely read from the shared MissionState
        std::lock_guard<std::mutex> lock(state->state_mut);
        status_proto.set_current_tick_name(state->current_tick_name);
        status_proto.set_is_connected(state->is_prepared);
        status_proto.set_mission_progress_percent(state->task_progress);
    }

    // Convert the Protobuf message to a JSON string
    std::string json_output;
    google::protobuf::util::MessageToJsonString(status_proto, &json_output);

    // Set the HTTP response
    response.set_content(json_output, "application/json");
    response.status = 200;
}

DEF_GCS_HANDLE(Get, tick) {
    TickID tickID = state->getTickID();
    std::string tick_state = TICK_ID_TO_STR(tickID);

    response.set_content(tick_state, "text/plain");
    response.status = 200;
}
DEF_GCS_HANDLE(Post, message) {
    DetectedObject detected_object;
    google::protobuf::util::JsonStringToMessage(request.body, &detected_object);

    {
        std::lock_guard<std::mutex> lock(state->state_mut);
        state->last_detected_object = ODLCObjects_ID_TO_STR(detected_object);
    }

    response.set_content("{\"status\": \"received\"}", "application/json");
    response.status = 200;
}
