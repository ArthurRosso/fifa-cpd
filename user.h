#include <iostream>
#include <string>
#include <list>

using namespace std;

class User
{
    public:
    int id;
    list<int>* id_player;
    list<float>* rating;
	User* left;
	User* right;
	int height;
};

int height(User *N);

User* newUser(int id, int id_player, float rating);

User* rightRotate(User *y);

User *leftRotate(User *x);

int getBalance(User *N);

User* insertUser(User* user, int id, int id_player, float rating);

User* findUserById(User* user, int id);