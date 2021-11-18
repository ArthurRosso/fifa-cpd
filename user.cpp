#include "user.h"

int max(int a, int b)
{
	return (a > b)? a : b;
}

int height(User *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

User* newUser(int id, int id_player, float rating)
{
	User* user = new User();
	user->id = id;
	user->id_player = id_player;
	user->rating = rating;
	user->left = NULL;
	user->right = NULL;
	user->height = 1;
	return(user);
}


User* rightRotate(User *y)
{
	User *x = y->left;
	User *T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	return x;
}

User* leftRotate(User* x)
{
	User* y = x->right;
	User* T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	return y;
}

int getBalance(User *N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}

User* insertUser(User* user, int id, int id_player, float rating)
{
	if (user == NULL)
		return(newUser(id, id_player, rating));

	if (id < user->id)
		user->left = insertUser(user->left, id, id_player, rating);
	else if (id > user->id)
		user->right = insertUser(user->right, id, id_player, rating);
	else
		return user;

	user->height = 1 + max(height(user->left), height(user->right));

	int balance = getBalance(user);

	if (balance > 1 && id < user->left->id)
		return rightRotate(user);

	if (balance < -1 && id > user->right->id)
		return leftRotate(user);

	if (balance > 1 && id > user->left->id)
	{
		user->left = leftRotate(user->left);
		return rightRotate(user);
	}

	if (balance < -1 && id < user->right->id)
	{
		user->right = rightRotate(user->right);
		return leftRotate(user);
	}

	return user;
}

User* findUserById(User* user, int id){
	if (user == NULL || user->id == id)
       return user;
    
    if (user->id < id)
       return findUserById(user->right, id);
 
    return findUserById(user->left, id);
}