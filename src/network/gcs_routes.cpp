#include "network/gcs_routes.hpp"

#include <google/protobuf/util/json_util.h>

#include "core/mission_state.hpp"
#include "nlohmann/json.hpp"

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
    std::string received_message = request.body;

    DetectedObject detected_proto;
    auto parse_status = google::protobuf::util::JsonStringToMessage(received_message, &detected_proto);
    if (!parse_status.ok()) {
        response.set_content("Invalid JSON for DetectedObject", "text/plain");
        response.status = 400;
        return;
    }

    const std::string detected_name = ODLCObjects_Name(detected_proto.object());

    {
        std::lock_guard<std::mutex> lock(state->image_mut);

        // Compare detected object name to current image filename (stem)
        if (state->image.has_value()) {
            const std::string &filename = state->image->filename;
            state->image_object = detected_name;

            std::cout << "Detected Objecct: " << detected_name << "\n Ground Truth:" << filename << std::endl;
            if (!detected_name.empty() && detected_name == filename) {
                state->image_state = MissionState::ImageState::VALID;
                std::cout << "Message Accepted!" << std::endl;
            } else {
                state->image_state = MissionState::ImageState::INVALID;
                std::cout << "Message Rejected" << std::endl;
            }
        } else {
            state->image_state = MissionState::ImageState::INVALID;
        }
    }

    response.set_content("Message received", "application/json");
    response.status = 200;
}

DEF_GCS_HANDLE(Get, capture) {
    std::lock_guard<std::mutex> lock(state->state_mut);
    std::optional<ImageData> img = state->image;
    std::cout << "img.has_value() = " << img.has_value() << std::endl;
    if (!img.has_value()) {
        std::cout << "No image available" << std::endl;
        response.set_content("No image available", "text/plain");
        response.status = 503;
        return;
    }
    std::string img_b64 = cvMatToBase64(img->DATA);

    state->has_captured = true;
    
    response.set_content(img_b64, "text/plain");
    response.status = 200;
}
