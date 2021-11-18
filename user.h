#include <iostream>
#include <string>

using namespace std;

class User
{
    public:
    int id;
    int id_player;
    float rating;
	User* left;
	User* right;
	int height;
};

int max(int a, int b);

int height(User *N);

User* newUser(int id, float rating);

User* rightRotate(User *y);

User *leftRotate(User *x);

int getBalance(User *N);

User* insertUser(User* user, int id, float rating);

User* findUserById(User* user, int id);

void printTree(User *root);