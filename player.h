#include <iostream>
#include <string>

using namespace std;

class Player
{
    public:
    int id;
    string name;
    float rating;
    int count;
	Player *left;
	Player *right;
	int height;
};

int max(int a, int b);

int height(Player *N);

Player* newPlayer(int id, string name);

Player* rightRotate(Player *y);

Player *leftRotate(Player *x);

int getBalance(Player *N);

Player* insertPlayer(Player* player, int id, string name);

Player* findPlayerById(Player* player, int id);

void printTree(Player *root);