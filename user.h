#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class User
{
    public:
    int id;
    vector<int>* id_player;
    vector<float>* rating;
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

// int partitionUser(vector<int>* id, vector<float>* rating, int begin, int end);
// void sortUser(vector<int>* id, vector<float>* rating, int begin, int end);

void heapify(vector<int>* id, vector<float>* rating, int n, int i);
void sortUser(vector<int>* id, vector<float>* rating, int n);

#endif /* USER_H */