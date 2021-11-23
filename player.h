#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

using namespace std;

class Player
{
    public:
    int id;
    string name;
    string positions;
    float rating;
    int count;
	Player *left;
	Player *right;
	int height;
};

int max(int a, int b);

int height(Player *N);

Player* newPlayer(int id, string name, string positions);

Player* rightRotate(Player *y);

Player *leftRotate(Player *x);

int getBalance(Player *N);

Player* insertPlayer(Player* player, int id, string name, string positions);

Player* findPlayerById(Player* player, int id);

void printTree(Player *root);

#endif /* PLAYER_H */