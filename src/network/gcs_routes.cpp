#include "network/gcs_routes.hpp"

#include <google/protobuf/util/json_util.h>

#include "core/mission_state.hpp"
#include "nlohmann/json.hpp"
#include "camera/interface.hpp"

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
    std::lock_guard<std::mutex> lock(state->state_mut);
    std::optional<ImageData> image = state->image;
    if(!image.has_value()) {
        response.set_content("No image captured", "text/plain");
        response.status = 501;
    }
    std::string result = cvMatToBase64(image.value().DATA);
    state->has_captured = true;
    response.set_content(result, "text/plain");
    response.status = 200;
}

DEF_GCS_HANDLE(Post, message) {
    DetectedObject detected_proto;
    auto parse_status = google::protobuf::util::JsonStringToMessage(request.body, &detected_proto);
    if (!parse_status.ok()) {
        response.set_content("Invalid JSON payload", "text/plain");
        response.status = 400;
        return;
    }
    const std::string detected_name = ODLCObjects_Name(detected_proto.object());
    std::string response_message;
    std::lock_guard<std::mutex> lock(state->state_mut);
    std::string filename = state->image.value().filename;
    size_t pos = filename.find_last_of("/\\"); 
    filename = filename.substr(pos + 1);

    // gets the filename string
    size_t dot_pos = filename.find_last_of('.');
    if (dot_pos != std::string::npos) {
        filename = filename.substr(0, dot_pos);
    }
    std::cout << "Filename: " << filename << std::endl;
    std::cout << "Detected filename: " << detected_name << std::endl;
    if(detected_name == filename) {
        state->image_state = MissionState::ImageState::VALID;
        response_message = "Selected object matches";
    } else {
        state->image_state = MissionState::ImageState::INVALID;
        response_message = "Selected object does not match";
    }
    response.set_content(response_message, "text/plain");
    response.status = 200;
}