#ifndef LIB_ControlId_H
#define LIB_ControlId_H

#include <cstdint>
#include "server/logic_server/matchobserver.h"

class ControlId {
private:
    uint8_t count;     // cppcheck-suppress unusedStructMember
    player_id ids[2];  // cppcheck-suppress unusedStructMember    
    
public:    
    ControlId(uint8_t _count):count(_count){}
    ControlId():count(0){}
    
    ControlId(player_id first):count(1){
          ids[0] = first;
    }
    ControlId(player_id first,player_id second):count(2){
          ids[0] = first;
          ids[1] = second;
    }
    
    ControlId(const ControlId& other):count(other.count){
         ids[0] = other.ids[0];
         ids[1] = other.ids[1];
    }
    
    bool operator==(const ControlId& other) const {
        return this->ids[0] == other.ids[0] && this->ids[1] == other.ids[1];
    }

    int getcount() const{
        return count;
    }
    
    void setcount(uint8_t count) {
        this->count = count;
    }

    
    player_id get(int ind) const{
        return this->ids[ind];
    }
    
    void set(int ind, player_id id){
        this->ids[ind] = id;
    }    
};
#endif
