#ifndef INCLUDE_NETWORK_GCS_MACROS_HPP_
#define INCLUDE_NETWORK_GCS_MACROS_HPP_

#include <memory>

#define BIND_PARAMS(...) std::bind_front(&GCS_HANDLE(__VA_ARGS__), this->state)
#define BIND_HANDLER(Method, uri) server.Method("/" #uri, BIND_PARAMS(Method, uri))

#define GCS_HANDLER_PARAMS std::shared_ptr<MissionState> state, const httplib::Request& request, httplib::Response& response
#define GCS_HANDLE(Method, uri) Method##_##uri
#define DEF_GCS_HANDLE(Method, uri) void GCS_HANDLE(Method, uri) (GCS_HANDLER_PARAMS)

// Macro to convert ODLCObjects enum to string
#define ODLCObjects_ID_TO_STR(detected_obj)                                  \
    ((detected_obj).object() == ODLCObjects::Undefined      ? "Undefined"    \
     : (detected_obj).object() == ODLCObjects::Mannequin    ? "Mannequin"    \
     : (detected_obj).object() == ODLCObjects::Car          ? "Car"          \
     : (detected_obj).object() == ODLCObjects::Motorcycle   ? "Motorcycle"   \
     : (detected_obj).object() == ODLCObjects::Airplane     ? "Airplane"     \
     : (detected_obj).object() == ODLCObjects::Bus          ? "Bus"          \
     : (detected_obj).object() == ODLCObjects::Boat         ? "Boat"         \
     : (detected_obj).object() == ODLCObjects::Stopsign     ? "Stopsign"     \
     : (detected_obj).object() == ODLCObjects::Snowboard    ? "Snowboard"    \
     : (detected_obj).object() == ODLCObjects::Umbrella     ? "Umbrella"     \
     : (detected_obj).object() == ODLCObjects::SoccerBall   ? "SoccerBall"   \
     : (detected_obj).object() == ODLCObjects::Basketball   ? "Basketball"   \
     : (detected_obj).object() == ODLCObjects::Volleyball   ? "Volleyball"   \
     : (detected_obj).object() == ODLCObjects::Football     ? "Football"     \
     : (detected_obj).object() == ODLCObjects::Baseballbat  ? "Baseballbat"  \
     : (detected_obj).object() == ODLCObjects::Mattress     ? "Mattress"     \
     : (detected_obj).object() == ODLCObjects::Tennisracket ? "Tennisracket" \
     : (detected_obj).object() == ODLCObjects::Suitcase     ? "Suitcase"     \
     : (detected_obj).object() == ODLCObjects::Skis         ? "Skis"         \
                                                            : "Unknown")

#endif  // INCLUDE_NETWORK_GCS_MACROS_HPP_