#include "player.h"
#include "weapon.h"
#include "box"
#include <list>

#ifndef MATCH_STATE_H
#define MATCH_STATE_H



class MatchState {

    private:

        bool play;
        std::list<Player> players;
        std::list<Box> boxes;



    public:

        MatchState();




        ~MatchState();



};



#endif //MATCH_STATE_H
