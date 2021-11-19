#include "player_pointer.h"

PlayerPointer* insertPlayerPointer(PlayerPointer* root, int id){
    if(root == NULL){
        root = new PlayerPointer();
        root->id_player=id;
    } else {
        PlayerPointer* i=root;

        while(i->next != NULL){
            i=i->next;
        }
        i->next = new PlayerPointer();
        i->next->id_player=id;
    }
    return root;
}

int position2Int (string name){
    if(name.compare("ST")){
        return 0;
    } 
    if(name.compare("LW")){
        return 1;
    } 
    if(name.compare("CF")){
        return 2;
    } 
    if(name.compare("RW")){
        return 3;
    } 
    if(name.compare("CAM")){
        return 4;
    } 
    if(name.compare("LM")){
        return 5;
    } 
    if(name.compare("CM")){
        return 6;
    } 
    if(name.compare("RM")){
        return 7;
    } 
    if(name.compare("LWB")){
        return 8;
    } 
    if(name.compare("CDM")){
        return 9;
    } 
    if(name.compare("RWB")){
        return 10;
    } 
    if(name.compare("LB")){
        return 11;
    } 
    if(name.compare("CB")){
        return 12;
    } 
    if(name.compare("RB")){
        return 13;
    } 
    if(name.compare("GK")){
        return 14;
    } 
    
    cout << "Posição não mapeada" << endl;
    return -1;
}

string int2Position (int i){
    string positions[] = { "ST", "LW", "CF", "RW", "CAM", "LM", "CM", "RM", "LWB", "CDM", "RWB", "LB", "CB", "RB", "GK" };

    return positions[i];
}