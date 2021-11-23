#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>
#include <cstring>
#include "./csv-parser/parser.hpp"
#include "player.h"
#include "user.h"
#include "trie_player.h"
#include "player_pointer.h"
#include "ht.h"
// #include "tags.h"

using namespace aria::csv;
using namespace std;

#define MAX_POS 15

/* sorts the linked list by changing next pointers (not data) */
void sortPlayerPointer(PlayerPointer** headRef, Player* root);

void FrontBackSplit(PlayerPointer* source, PlayerPointer** frontRef, PlayerPointer** backRef);

PlayerPointer* SortedMerge(PlayerPointer* a, PlayerPointer* b, Player* root);


int main (){
	Player *player_root = NULL;
	User *user_root = NULL;
	Player *player_current = NULL;
	User *user_current = NULL;
    TriePlayer *trie_root = newTriePlayer();
	list<int>* ids = new list<int>;
    PlayerPointer* positions[MAX_POS]={NULL};
	string pos, line, cmd, item;
	bool ishead=true;
	time_t start, ending;
	time(&start);

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

	ifstream t("./data/tags.csv");
    CsvParser tags(t);

	ishead=true;

	ht* hash = ht_create();

    for (auto& row : tags) {
		if(ishead){
			ishead=false;
			continue;
		}
		ht_set(hash, (row[2]).c_str(), stoi(row[1]));
    }
	t.close();

	// for(int i=0; i<MAX_POS; i++){
	// 	PlayerPointer* temp = positions[i];
	// 	PlayerPointer* prev = NULL;

	// 	while(temp != NULL){
	// 		player_current = findPlayerById(player_root, temp->id_player);
	// 		if(player_current->count < 1000){
	// 			if(prev != NULL){
	// 				prev->next=temp->next;
	// 			} else {
	// 				temp=temp->next;
	// 			}
	// 		}
	// 		prev = temp;
	// 		temp = temp->next;
	// 	}
	// }

	// for(int i=0; i<MAX_POS; i++){
	// 	sortPlayerPointer(&positions[i], player_root);
	// }

	time(&ending);

	cout << "Total: " << difftime(ending, start) << " seconds to initialize." << endl;
	

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
				cout.width(10);
				cout << "sofifa_id";
				cout.width(50);
				cout << "name";
				cout.width(20);
				cout << "player_positions";
				cout.width(10);
				cout << "rating";
				cout.width(8);
				cout << "count" << endl;
				for (list<int>::iterator it=ids->begin(); it!=ids->end(); it++){
					player_current = findPlayerById(player_root, *it);
					cout.width(10);
					cout << player_current->id;
					cout.width(50);
					cout << player_current->name;
					cout.width(20);
					cout << player_current->positions;
					cout.width(10);
					cout << (float)(player_current->rating)/(player_current->count);
					cout.width(8);
					cout << player_current->count << endl;
				}
			} else {
				cout << "Nome ou prefixo não encontrado :(" << endl;
			}

		} else if(cmd.compare("user")==0){
			ss >> item;
			user_current = findUserById(user_root, stoi(item));
			if(user_current != NULL){
				sortUser(user_current->id_player, user_current->rating, user_current->rating->size());
				cout.width(10);
				cout << "sofifa_id";
				cout.width(50);
				cout << "name";
				cout.width(20);
				cout << "global_rating";
				cout.width(10);
				cout << "count";
				cout.width(8);
				cout << "rating" << endl;
				for (int i=0; i < min(20, (int)user_current->id_player->size()); i++){
					player_current = findPlayerById(player_root, user_current->id_player->at(i));
					if(player_current != NULL){
						cout.width(10);
						cout << player_current->id;
						cout.width(50);
						cout << player_current->name;
						cout.width(20);
						cout << (float)(player_current->rating)/(player_current->count);
						cout.width(10);
						cout << player_current->count;
						cout.width(8);
						cout << user_current->rating->at(i) << endl;					
					}
				}
			} else {
				cout << "Usuário não encontrado :(" << endl;
			}

		} else if(cmd[0]=='t' && cmd[1]=='o' && cmd[2]=='p'){
			ss >> item;
			cmd.erase(0,3);
			int j = position2Int(item);
			int i=0;
			PlayerPointer* iteratorp=positions[j];
			if(iteratorp != NULL){
				cout.width(10);
				cout << "sofifa_id";
				cout.width(50);
				cout << "name";
				cout.width(20);
				cout << "player_positions";
				cout.width(10);
				cout << "rating";
				cout.width(8);
				cout << "count" << endl;
				while(iteratorp->next != NULL && i<stoi(cmd)){
					player_current = findPlayerById(player_root, iteratorp->id_player);
					if(player_current != NULL){
						cout.width(10);
						cout << player_current->id;
						cout.width(50);
						cout << player_current->name;
						cout.width(20);
						cout << player_current->positions;
						cout.width(10);
						cout << (float)(player_current->rating)/(player_current->count);
						cout.width(8);
						cout << player_current->count << endl;
					}
					iteratorp=iteratorp->next;
					i++;
				}
			} else {
				cout << "Posição " << item << " não encontrada ou nenhum jogador cadastrado nela :(" << endl;
			}

		} else if(cmd.compare("tags")==0){
			ss >> item;
			int k=0;
			struct LinkedList* iteratort = ht_get(hash, item.c_str());
			cout.width(10);
			cout << "sofifa_id";
			cout.width(50);
			cout << "name";
			cout.width(20);
			cout << "player_positions";
			cout.width(10);
			cout << "rating";
			cout.width(8);
			cout << "count" << endl;
			while(iteratort->next != NULL && k<20){
				player_current = findPlayerById(player_root, iteratort->id);
				if(player_current != NULL){
					cout.width(10);
					cout << player_current->id;
					cout.width(50);
					cout << player_current->name;
					cout.width(20);
					cout << player_current->positions;
					cout.width(10);
					cout << (float)(player_current->rating)/(player_current->count);
					cout.width(8);
					cout << player_current->count << endl;
				}
				iteratort=iteratort->next;
				k++;
			}
			
		} else {
			cout << "Query escrita errada ou não implementada ainda :(" << endl;
		}
	}

	

	// printTree(player_root);

	return 0;

}


/* sorts the linked list by changing next pointers (not data) */
void sortPlayerPointer(PlayerPointer** headRef, Player* root){
    PlayerPointer* head = *headRef;
    PlayerPointer* a;
    PlayerPointer* b;
 
    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }
 
    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit(head, &a, &b);
 
    /* Recursively sort the sublists */
    sortPlayerPointer(&a, root);
    sortPlayerPointer(&b, root);
 
    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b, root);
}

/* UTILITY FUNCTIONS */
/* Split the PlayerPointers of the given list into front and back halves,
    and return the two lists using the reference parameters.
    If the length is odd, the extra PlayerPointer should go in the front list.
    Uses the fast/slow pointer strategy. */
void FrontBackSplit(PlayerPointer* source, PlayerPointer** frontRef, PlayerPointer** backRef){
    PlayerPointer* fast;
    PlayerPointer* slow;
    slow = source;
    fast = source->next;
 
    /* Advance 'fast' two PlayerPointers, and advance 'slow' one PlayerPointer */
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
 
    /* 'slow' is before the midpoint in the list, so split it in two
    at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}
 
/* See https:// www.geeksforgeeks.org/?p=3622 for details of this
function */
PlayerPointer* SortedMerge(PlayerPointer* a, PlayerPointer* b, Player* root){
    PlayerPointer* result = NULL;
 
    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);
 
    /* Pick either a or b, and recur */
	Player* ap = findPlayerById(root, a->id_player);
	Player* bp = findPlayerById(root, b->id_player);
    if ((float)ap->rating/ap->count <= (float)bp->rating/bp->count) {
        result = b;
        result->next = SortedMerge(a, b->next, root);
    }
    else {
        result = a;
        result->next = SortedMerge(a->next, b, root);
    }
    return (result);
}