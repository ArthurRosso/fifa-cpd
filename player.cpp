#include "player.h"

int max(int a, int b)
{
	return (a > b)? a : b;
}


int height(Player *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

Player* newPlayer(int id, string name, string positions)
{
	Player* player = new Player();
	player->id = id;
	player->name = name;
	player->positions = positions;
	player->rating = 0;
	player->count = 0;
	player->left = NULL;
	player->right = NULL;
	player->height = 1;
	return(player);
}


Player* rightRotate(Player *y)
{
	Player *x = y->left;
	Player *T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	return x;
}

Player *leftRotate(Player *x)
{
	Player *y = x->right;
	Player *T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	return y;
}

int getBalance(Player *N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}

Player* insertPlayer(Player* player, int id, string name, string positions)
{
	if (player == NULL)
		return(newPlayer(id, name, positions));

	if (id < player->id)
		player->left = insertPlayer(player->left, id, name, positions);
	else if (id > player->id)
		player->right = insertPlayer(player->right, id, name, positions);
	else
		return player;

	player->height = 1 + max(height(player->left), height(player->right));

	int balance = getBalance(player);

	if (balance > 1 && id < player->left->id)
		return rightRotate(player);

	if (balance < -1 && id > player->right->id)
		return leftRotate(player);

	if (balance > 1 && id > player->left->id)
	{
		player->left = leftRotate(player->left);
		return rightRotate(player);
	}

	if (balance < -1 && id < player->right->id)
	{
		player->right = rightRotate(player->right);
		return leftRotate(player);
	}

	return player;
}

Player* findPlayerById(Player* player, int id){
	if (player == NULL || player->id == id)
       return player;
    
    if (player->id < id)
       return findPlayerById(player->right, id);
 
    return findPlayerById(player->left, id);
}

void printTree(Player *root)
{
	if(root != NULL)
	{
		cout << "Player id: " << root->id << " Player rating: " << root->rating << " Player rating count: " << root->count << endl;
		printTree(root->left);
		printTree(root->right);
	}
}