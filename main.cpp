#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include<algorithm>
#include "./csv-parser/parser.hpp"
#include "player.h"
#include "user.h"
#include "triePlayer.h"
#include "player_pointer.h"

using namespace aria::csv;
using namespace std;

int main (){
	Player *player_root = NULL;
	User *user_root = NULL;
	Player *player_current = NULL;
    TriePlayer *trie_root = NULL;
    list<int>* ids = new list<int>;
    list<int>::iterator it;
    PlayerPointer* positions[15]={NULL};
	string pos;
	

	ifstream p("players.csv");
    CsvParser players(p);

    for (auto& row : players) {
		trie_root = insertTriePlayer(trie_root, stoi(row[0]), row[1]);
		player_root = insertPlayer(player_root, stoi(row[0]), row[1], row[2]);
		stringstream ss(row[2]);
		while(ss>>pos){
			pos.erase(remove(pos.begin(), pos.end(), ','), pos.end());
        	// cout << pos << endl; // ST, LW, CF, RW, CAM, LM, CM, RM, LWB, CDM, RWB, LB, CB, RB, GK
			int i = position2Int(pos);
			positions[i]=insertPlayerPointer(positions[i], stoi(row[0]));	
    	}
		exit(0);
    }

	ifstream r("rating.csv");
    CsvParser ratings(r);

    for (auto& row : ratings) {
		user_root = insertUser(user_root, stoi(row[0]), stoi(row[1]), stof(row[2]));
		player_current = findPlayerById(player_root, stoi(row.at(1)));
		if(player_current != NULL){
			player_current->rating+=stof(row.at(2));
			player_current->count++;
		}
    }

	// findPlayerByName(trie_root, "Fer", ids);
    // for (it=ids->begin(); it!=ids->end(); it++){
	// 	player_current = findPlayerById(player_root, *it);
	// 	cout << "Player name: " << player_current->name << endl;
	// }

	// printTree(player_root);

	return 0;

}