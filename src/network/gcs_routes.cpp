#include "network/gcs_routes.hpp"

#include <google/protobuf/util/json_util.h>

#include "core/mission_state.hpp"
#include "nlohmann/json.hpp"

// This needs to be included to get the definition of our proto message
#include "onboarding.pb.h"
#include "camera/interface.hpp"

DEF_GCS_HANDLE(Get, status)
{
    
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

DEF_GCS_HANDLE(Get, tick)
{
    TickID tickID = state->getTickID();
    std::string tick_state = TICK_ID_TO_STR(tickID);

    response.set_content(tick_state, "text/plain");
    response.status = 200;
}

DEF_GCS_HANDLE(Get, capture)
{
    std::lock_guard<std::mutex> lock(state->state_mut);
    state->capture_called = true;
    auto img = state->image;
    if (img.has_value())
    {

        auto imgdata = cvMatToBase64(img.value().DATA);
        response.status = 200;
        response.set_content(imgdata, "text/plain");
    }
    else
    {
        response.status = 501;
        response.set_content("No Image", "text/plain");
    }
}
DEF_GCS_HANDLE(Post, message)
{
    std::lock_guard<std::mutex> lock(state->state_mut);
    // if (state->getTickID() != TickID::Verify)
    // {
    //     std::cout << "Message called outside of verify tick, skipping" << std::endl;
    //     return;
    // }
    DetectedObject detected;
    auto bodystr = std::string(request.body.data());
    auto status = google::protobuf::util::JsonStringToMessage(bodystr, &detected);
    if (status.ok())
    {
        // check if correct choice
        const google::protobuf::EnumDescriptor *descriptor = ODLCObjects_descriptor();
        std::string human_chosen = descriptor->FindValueByNumber(detected.selected_object())->name();

        auto vision_chose_raw = state->image.value().filename;
        auto vision_chose = vision_chose_raw.substr(vision_chose_raw.find_last_of("/") + 1,  vision_chose_raw.find_first_of(".") - vision_chose_raw.find_last_of("/") -1);
        std::cout << human_chosen<< vision_chose << std::endl;
        bool correct = vision_chose == human_chosen;
        if(correct){
            state->image_state = MissionState::ImageState::VALID;
        }
        else{
            state->image_state = MissionState::ImageState::INVALID;
        }
        response.status = 200;
        response.set_content(correct ? "correct" : "incorrect", "text/plain");
     }
    else
    {
        std::cout << "error parsing" << status.error_message() << std::endl;
    }
}