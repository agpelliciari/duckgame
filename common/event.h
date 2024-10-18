#ifndef LIB_EVENT_H
#define LIB_EVENT_H

#include <cstdint>
#include <string>

#include "./reward.h"

enum EventType : uint8_t { PICKUP = 0x04, NEW_BOX = 0x05 };

class Event {
private:
    uint8_t attachid;        // cppcheck-suppress unusedStructMember
    EventType eventtype;     // cppcheck-suppress unusedStructMember
    std::string playername;  // cppcheck-suppress unusedStructMember

public:
    // Pickup event
    explicit Event(const std::string& _player, const RewardType reward);

    // New box event
    explicit Event(int boxid);

    // Existe para simplificar. Ya que no se usa la boxid ahora.
    Event();

    const std::string& actor() const;
    uint8_t attachedID() const;
    EventType type() const;

    std::string parseinfo() const;
};
#endif
