#ifndef INCLUDE_NETWORK_GCS_MACROS_HPP_
#define INCLUDE_NETWORK_GCS_MACROS_HPP_

#include <memory>

#define BIND_PARAMS(...) std::bind_front(&GCS_HANDLE(__VA_ARGS__), this->state)
#define BIND_HANDLER(Method, uri) server.Method("/" #uri, BIND_PARAMS(Method, uri))

#define GCS_HANDLER_PARAMS std::shared_ptr<MissionState> state, const httplib::Request& request, httplib::Response& response
#define GCS_HANDLE(Method, uri) Method##_##uri
#define DEF_GCS_HANDLE(Method, uri) void GCS_HANDLE(Method, uri) (GCS_HANDLER_PARAMS)

#endif // INCLUDE_NETWORK_GCS_MACROS_HPP_