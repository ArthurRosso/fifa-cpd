#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "./csv-parser/parser.hpp"
#include "player.h"
#include "triePlayer.h"

using namespace aria::csv;
using namespace std;

int main (){
	Player *player_root = NULL;
	Player *player_current = NULL;
    TriePlayer *trie_root = newTriePlayer();
    list<int>* ids = new list<int>;
    list<int>::iterator it;

	ifstream p("players.csv");
    CsvParser players(p);

    for (auto& row : players) {
		insertTriePlayer(trie_root, stoi(row.at(0)), row.at(1));
		player_root = insertPlayer(player_root, stoi(row.at(0)), row.at(1));
    }

	ifstream r("rating.csv");
    CsvParser ratings(r);

    for (auto& row : ratings) {
		player_current = findPlayerById(player_root, stoi(row.at(1)));
		if(player_current != NULL){
			player_current->rating+=stof(row.at(2));
			player_current->count++;
		}
    }

	findPlayerByName(trie_root, "Fer", ids);
    for (it=ids->begin(); it!=ids->end(); it++){
		player_current = findPlayerById(player_root, *it);
		cout << "Player name: " << player_current->name << endl;
	}

	// printTree(player_root);

}