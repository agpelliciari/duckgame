#include "./simplereward.h"

#include <string>

#define OFFSET 0x10

static const char* const NAMES[] = {"Bazooka", "Chainsaw", "Death ray", "Shotgun"};
static const uint8_t TIMES[] = {15, 5, 20, 10};


const char* SimpleReward::cname() const { return NAMES[this->type - OFFSET]; }
std::string SimpleReward::name() const { return std::string(cname()); }

uint8_t SimpleReward::rewardtype() const { return (uint8_t)this->type; }

uint8_t SimpleReward::respawntime() const { return TIMES[this->type - OFFSET]; }
