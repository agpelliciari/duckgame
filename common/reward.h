#ifndef LIB_REWARD_H
#define LIB_REWARD_H

#include <cstdint>
#include <string>

enum RewardType { BAZOOKA = 0x10, CHAINSAW = 0x11, DEATHRAY = 0x12, SHOTGUN = 0x13 };

class Reward {
private:
    RewardType type;

public:
    explicit Reward(RewardType _type): type(_type) {}

    const char* cname() const;
    std::string name() const;
    uint8_t rewardtype() const;
    uint8_t respawntime() const;
};

#endif
