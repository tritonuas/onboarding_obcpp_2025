#include "network/gcs_routes.hpp"

#include <google/protobuf/util/json_util.h>

#include "core/mission_state.hpp"
#include "nlohmann/json.hpp"
#include "utilities/locks.hpp"

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

DEF_GCS_HANDLE(Get, capture) {
    // mutex lock to prevent other threads from accessing the state
    Lock lock(state->state_mut);
    if (not state->image.has_value()) {
        response.set_content("no image found", "text/plain");
        response.status = 501;
        // change state so it doesn't get stuck forever
        state->captureFinished = true;
    } else {
        // convert img data to b64 and add to response
        std::string imgData = cvMatToBase64(state->image.value().DATA);
        
        state->captureFinished = true;
        response.set_content(imgData, "text/plain");
        response.status = 200;
    }
    
}

DEF_GCS_HANDLE(Post, message) {
    Lock lock(state->state_mut);
    DetectedObject detected_proto;
    auto parse_status = google::protobuf::util::JsonStringToMessage(request.body, &detected_proto);
    const std::string detected_name = ODLCObjects_Name(detected_proto.object());
    std::cout << "Received body: " << detected_name << "File name: " << state->image->filename << std::endl;
    if (detected_name == state->image->filename) {
        state->image_state = MissionState::ImageState::VALID;
    } else {
        state->image_state = MissionState::ImageState::INVALID;
    }
    response.set_content("I like Genshin Impact", "text/plain");
    response.status = 200;

}
