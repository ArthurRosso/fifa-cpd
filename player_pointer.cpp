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
    if(name.compare("ST")==0){
        return 0;
    } 
    if(name.compare("LW")==0){
        return 1;
    } 
    if(name.compare("CF")==0){
        return 2;
    } 
    if(name.compare("RW")==0){
        return 3;
    } 
    if(name.compare("CAM")==0){
        return 4;
    } 
    if(name.compare("LM")==0){
        return 5;
    } 
    if(name.compare("CM")==0){
        return 6;
    } 
    if(name.compare("RM")==0){
        return 7;
    } 
    if(name.compare("LWB")==0){
        return 8;
    } 
    if(name.compare("CDM")==0){
        return 9;
    } 
    if(name.compare("RWB")==0){
        return 10;
    } 
    if(name.compare("LB")==0){
        return 11;
    } 
    if(name.compare("CB")==0){
        return 12;
    } 
    if(name.compare("RB")==0){
        return 13;
    } 
    if(name.compare("GK")==0){
        return 14;
    } 
    
    cout << "Posição não mapeada" << endl;
    return -1;
}

string int2Position (int i){
    string positions[] = { "ST", "LW", "CF", "RW", "CAM", "LM", "CM", "RM", "LWB", "CDM", "RWB", "LB", "CB", "RB", "GK" };

    return positions[i];
}