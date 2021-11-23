#include "user.h"

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
    user->id_player = new vector<int>;
	user->id_player->push_back(id_player);
    if(id_player==0){
        exit(-1);
    }
    user->rating = new vector<float>;
	user->rating->push_back(rating);
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

	if (id < user->id){
		user->left = insertUser(user->left, id, id_player, rating);
	} else if (id > user->id){
		user->right = insertUser(user->right, id, id_player, rating);
	} else if (id == user->id){
        if(id_player==0){
            exit(-1);
        }
        user->id_player->push_back(id_player);
        user->rating->push_back(rating);
        return user;
    }

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

// // Partitioner: Median
// // Partitioning: Lomuto
// int partitionUser(vector<int>* id, vector<float>* rating, int begin, int end){
//     int middle = (begin + end)/2;
//     int a = (*rating)[begin];
//     int b = (*rating)[middle];
//     int c = (*rating)[end];
//     int median; //índice da mediana
//     if (a < b) {
//         if (b < c) {
//             //a < b && b < c
//             median = middle;
//         } else {
//             if (a < c) {
//                 //a < c && c <= b
//                 median = end;
//             } else {
//                 //c <= a && a < b
//                 median = begin;
//             }
//         }
//     } else {
//         if (c < b) {
//             //c < b && b <= a
//             median = middle;
//         } else {
//             if (c < a) {
//                 //b <= c && c < a
//                 median = end;
//             } else {
//                 //b <= a && a <= c
//                 median = begin;
//             }
//         }
//     }
//     swap((*rating)[begin], (*rating)[median]);
//     swap((*id)[begin], (*id)[median]);

//     int x = (*rating)[begin];
//     int i = begin;
//     int j;

//     for(j=begin+1; j<=end; j++){
//         if((*rating)[j] <= x){
//             i++;
//             swap((*rating)[i], (*rating)[j]);
//             swap((*id)[i], (*id)[j]);
//         }
//     }
//     swap((*rating)[i], (*rating)[begin]);
//     swap((*id)[i], (*id)[begin]);
//     return i;
// }

// void sortUser(vector<int>* id, vector<float>* rating, int begin, int end){
//     if (begin < end){
//         int part = partitionUser(id, rating, begin, end);
//         sortUser(id, rating, begin, part-1);
//         sortUser(id, rating, part+1, end);
//     }
// }

void heapify(vector<int>* id, vector<float>* rating, int n, int i){
    int smallest = i; // Initialize smallest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2
  
    // If left child is smaller than root
    if (l < n && (*rating)[l] < (*rating)[smallest])
        smallest = l;
  
    // If right child is smaller than smallest so far
    if (r < n && (*rating)[r] < (*rating)[smallest]){
        smallest = r;
    }
  
    // If smallest is not root
    if (smallest != i) {
        swap((*rating)[i], (*rating)[smallest]);
        swap((*id)[i], (*id)[smallest]);
  
        // Recursively heapify the affected sub-tree
        heapify(id, rating, n, smallest);
    }
}

void sortUser(vector<int>* id, vector<float>* rating, int n){
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--){
        heapify(id, rating, n, i);
    }
  
    // One by one extract an element from heap
    for (int i = n - 1; i >= 0; i--) {
        // Move current root to end
        swap((*rating)[0], (*rating)[i]);
        swap((*id)[0], (*id)[i]);
  
        // call max heapify on the reduced heap
        heapify(id, rating, i, 0);
    }
}