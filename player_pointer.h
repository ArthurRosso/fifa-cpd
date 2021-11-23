#ifndef PLAYER_POINTER_H
#define PLAYER_POINTER_H

#include <iostream>
#include <string>
#include "player.h"

using namespace std;

// enum PosNames { ST, LW, CF, RW, CAM, LM, CM, RM, LWB, CDM, RWB, LB, CB, RB, GK };
 
class PlayerPointer{
public:
    int id_player;
    PlayerPointer* next;
};

PlayerPointer* insertPlayerPointer(PlayerPointer* root, int id);

int position2Int (string name);

string int2Position (int i);

#endif /* PLAYER_POINTER_H */