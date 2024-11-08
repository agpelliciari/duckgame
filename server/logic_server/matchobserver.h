#ifndef LIB_MatchObserver_H
#define LIB_MatchObserver_H

#include <vector>

#include "common/dtosgame.h"

typedef unsigned int player_id;

class MatchObserver {
public:
    virtual int playercount() const = 0;
    virtual std::vector<player_id> getPlayers() = 0;
    virtual std::vector<player_id> updateState(const MatchDto& state) = 0;

    virtual ~MatchObserver() {}
};

#endif
