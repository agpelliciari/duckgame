#include "./gamecontext.h"
#include <iostream>

void GameContext::removePlayer(uint8_t pos){
    // Si el primero es mayor el segundo tambien... pero para hacerlo flexible.
    if(first_player > pos){
        first_player--;
    }
    if(second_player > pos){
        second_player--;
    }    
    cantidadjugadores--;
}

void GameContext::addPlayer(uint8_t pos){
    if(first_player > pos){ // La verdad no deberia ser posible
        first_player++;
    }
    if(second_player > pos){ // La verdad no deberia ser posible
        second_player++;
    }
    cantidadjugadores++;
    //players.push_back(id);
}

int GameContext::countPlayers() const{
    return cantidadjugadores;
}


GameContext::GameContext():
            id_lobby(0),
            started(false),
            dualplay(true),
            map(),
            max_player_count(4),
            first_player(0),
            second_player(0),
            cantidadjugadores(0){}
