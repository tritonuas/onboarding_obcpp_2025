#include "network/gcs_routes.hpp"

#include <google/protobuf/util/json_util.h>

#include <string.h>
#include <stdio.h>
#include <iostream>

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

DEF_GCS_HANDLE(Get, capture) {
    std::lock_guard<std::mutex> lock(state->state_mut);
    std::optional<ImageData> image = state->image;
    std::cout << image.has_value() << std::endl;
    if (!image.has_value()) {
        response.set_content("No Image Found.", "text/plain");
        response.status = 501;
    }
    else {
        std::string output = cvMatToBase64(image.value().DATA);
        state->has_captured = true;
        response.set_content(output, "text/plain");
        response.status = 200;
    }
}

DEF_GCS_HANDLE(Post, message) {
    std::optional<ImageData> image = state->image;
    std::string received_message = request.body;
    DetectedObject detected_proto;
    auto parse_status = google::protobuf::util::JsonStringToMessage(received_message, &detected_proto);
    //std::cout << " DOING SHIT " << std::endl;
    const std::string detected_name = ODLCObjects_Name(detected_proto.objects());
    if (!image.has_value()) {
        response.set_content("No Image Found.", "text/plain");
        response.status = 501;
    }
    std::cout << image.value().filename << " " << detected_name << std::endl;
    if (image.value().filename.find(detected_name) != std::string::npos) {
        
        state->image_state == MissionState::ImageState::VALID;
        response.set_content("Ding Ding Ding!", "text/plain");
        response.status = 200;
    }
    else {
        state->image_state == MissionState::ImageState::INVALID;
        response.set_content("Wrong, Dipshit.", "text/plain");
        response.status = 200;
    }

}