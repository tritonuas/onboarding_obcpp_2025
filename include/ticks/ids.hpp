#ifndef INCLUDE_TICKS_IDS_HPP_
#define INCLUDE_TICKS_IDS_HPP_

enum class TickID {
    MissionPrep,
    Completion,
};

#define _SET_TICK_ID_MAPPING(id) \
    case TickID::id: return #id

constexpr const char* TICK_ID_TO_STR(TickID id) {
    switch (id) {
        _SET_TICK_ID_MAPPING(MissionPrep);
        _SET_TICK_ID_MAPPING(Completion);
        default: return "Unknown TickID";
    }
}

#endif  // INCLUDE_TICKS_IDS_HPP_