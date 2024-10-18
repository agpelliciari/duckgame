#include "./reward.h"

#include <string>

#define OFFSET 0x10

static const char* const NAMES[] = {"Bazooka", "Chainsaw", "Death ray", "Shotgun"};
static const uint8_t TIMES[] = {15, 5, 20, 10};


const char* Reward::cname() const { return NAMES[this->type - OFFSET]; }
std::string Reward::name() const { return std::string(cname()); }

uint8_t Reward::rewardtype() const { return (uint8_t)this->type; }

uint8_t Reward::respawntime() const { return TIMES[this->type - OFFSET]; }
