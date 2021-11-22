#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>
#include "./csv-parser/parser.hpp"
#include "player.h"
#include "user.h"
#include "triePlayer.h"
#include "player_pointer.h"
#include "tags.h"

using namespace aria::csv;
using namespace std;

int main (){
	Player *player_root = NULL;
	User *user_root = NULL;
	Player *player_current = NULL;
	User *user_current = NULL;
    TriePlayer *trie_root = newTriePlayer();
	list<int>* ids = new list<int>;
    PlayerPointer* positions[15]={NULL};
	string pos, line, cmd, item;
	bool ishead=true;
	

	ifstream p("./data/players.csv");
    CsvParser players(p);

    for (auto& row : players) {
		if(ishead){
			ishead=false;
			continue;
		}
		insertTriePlayer(trie_root, stoi(row[0]), row[1]);
		player_root = insertPlayer(player_root, stoi(row[0]), row[1], row[2]);
		stringstream ss(row[2]);
		while(ss>>pos){
			pos.erase(remove(pos.begin(), pos.end(), ','), pos.end());
        	// cout << pos << endl; // ST, LW, CF, RW, CAM, LM, CM, RM, LWB, CDM, RWB, LB, CB, RB, GK
			int i = position2Int(pos);
			positions[i]=insertPlayerPointer(positions[i], stoi(row[0]));	
    	}
    }
	p.close();

	ifstream r("./data/minirating.csv");
    CsvParser ratings(r);

	ishead=true;

    for (auto& row : ratings) {
		if(ishead){
			ishead=false;
			continue;
		}
		user_root = insertUser(user_root, stoi(row[0]), stoi(row[1]), stof(row[2]));
		player_current = findPlayerById(player_root, stoi(row.at(1)));
		if(player_current != NULL){
			player_current->rating+=stof(row.at(2));
			player_current->count++;
		}
    }
	r.close();

	while(true){

        cout << "\n$> ";

        getline(cin, line);
        stringstream ss(line);
        ss >> cmd;

        if(cmd.compare("player")==0){
			ss >> item;
			ids->clear();

			findPlayerByName(trie_root, item, ids);
			if(!ids->empty()){
				cout << "sofifa_id" << " " << " name "<< "  " <<" player_positions "<< " " <<" rating "<< " " <<" count" << endl;
				for (list<int>::iterator it=ids->begin(); it!=ids->end(); it++){
					player_current = findPlayerById(player_root, *it);
					cout << player_current->id << "  " << player_current->name << "  " << player_current->positions << " " << player_current->rating << " " << player_current->count << endl; // print player
				}
			} else {
				cout << "Nome ou prefixo não encontrado :(" << endl;
			}

		} else if(cmd.compare("user")==0){
			ss >> item;
			ids->clear();

			user_current = findUserById(user_root, stoi(item));
			if(user_current != NULL){
				sortUser(user_current->id_player, user_current->rating, 0, user_current->rating->size());
				cout << "sofifa_id" << " " << " name "<< "  " <<" global_rating "<< " " <<" count "<< " " <<" rating" << endl;
				for (int i=0; i < min(20, (int)user_current->id_player->size()); i++){
					cout << user_current->id_player->at(i) << endl;
					player_current = findPlayerById(player_root, user_current->id_player->at(i));
					if(player_current != NULL){
						cout << player_current->id << "  " << player_current->name << "  " << player_current->rating << " " << player_current->count << " " << user_current->rating->at(i) << endl; // print player
					}
				}
			} else {
				cout << "Usuário não encontrado :(" << endl;
			}
		} else if(cmd[0]=='t' && cmd[1]=='o' && cmd[2]=='p'){
			ss >> item;
			cmd.erase(0,3);
			// cout << stoi(cmd) << " " << item << endl;
			int j = position2Int(item);
			int i=0;
			cout << "sofifa_id" << " " << " name "<< "  " <<" global_rating "<< " " <<" count "<< " " <<" rating" << endl;
			while(positions[j]->next != NULL && i<stoi(cmd)){
				player_current = findPlayerById(player_root, positions[j]->id_player);
				if(player_current != NULL && player_current->count > 1){
					cout << player_current->id << "  " << player_current->name << "  " << player_current->rating << " " << player_current->count << " " << user_current->rating->at(i) << endl; // print player
				}
				i++;
			}

		} else if(cmd.compare("tags")==0){
			cout << "Nenhuma tag encontrada :(" << endl;
			
		} else {
			cout << "Query escrita errada ou não implementada ainda :(" << endl;
		}
	}

	

	// printTree(player_root);

	return 0;

}