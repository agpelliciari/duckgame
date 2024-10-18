#include "./event.h"

#include <sstream>
#include <string>

static const char* MSG_NEWBOX = "A new box has appeared";
static const char* LABEL_PICKUP = " picked up a ";


// A futuro seguro que sera mejor segregar interfaz capaz.
// Pickup event
Event::Event(const std::string& _player, const RewardType reward) {
    this->attachid = (uint8_t)reward;
    this->playername = _player;
    this->eventtype = PICKUP;
}
Event::Event(int boxid) {
    this->eventtype = NEW_BOX;
    // Capaz a futuro se quisiera mandar el id de la box que reaparecio.
    this->attachid = (uint8_t)boxid;
}
Event::Event() {
    this->eventtype = NEW_BOX;
    this->attachid = 0;
}


uint8_t Event::attachedID() const { return this->attachid; }

const std::string& Event::actor() const { return this->playername; }

EventType Event::type() const { return this->eventtype; }

std::string Event::parseinfo() const {
    if (this->eventtype == NEW_BOX) {
        return std::string(MSG_NEWBOX);
    }

    std::stringstream result;
    result << playername;
    result << LABEL_PICKUP << Reward((RewardType)attachid).cname();

    return result.str();
}
