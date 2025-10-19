#ifndef INCLUDE_TICKS_IDS_HPP_
#define INCLUDE_TICKS_IDS_HPP_

enum class TickID {
    MissionPrep,
    Switch,
    Verify,
    End,
    Camera,
    CVLoiter
};

#define _SET_TICK_ID_MAPPING(id) \
    case TickID::id: return #id

constexpr const char* TICK_ID_TO_STR(TickID id) {
    switch (id) {
        _SET_TICK_ID_MAPPING(MissionPrep);
        _SET_TICK_ID_MAPPING(Switch);
        _SET_TICK_ID_MAPPING(Verify);
        _SET_TICK_ID_MAPPING(End);
        _SET_TICK_ID_MAPPING(Camera);
        _SET_TICK_ID_MAPPING(CVLoiter);
        default: return "Unknown TickID";
    }
}

#endif  // INCLUDE_TICKS_IDS_HPP_