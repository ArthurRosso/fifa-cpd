// C++ implementation of search and insert
// operations on Trie
#include <bits/stdc++.h>

#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;
 
const int ALPHABET_SIZE = 26;
 
// trie node
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
 
    // player id
    int player;
};
 
// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode =  new TrieNode;
 
    pNode->player = 0;
 
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;
 
    return pNode;
}
 
// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
void insert(struct TrieNode *root, string key, int id)
{
    struct TrieNode *subtrie = root;
 
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!subtrie->children[index])
            subtrie->children[index] = getNode();
 
        subtrie = subtrie->children[index];
    }
 
    // mark last node as leaf
    subtrie->player = id;
}

// A recursive function to search a pattern in subtree rooted with this node
void search_rec(struct TrieNode *subtrie, list<int>* ids)
{
    int i;
    if(subtrie){
        for(i=0; i<ALPHABET_SIZE; i++){
            search_rec(subtrie->children[i], ids);
        }
        if(subtrie->player != 0){
            ids->push_back(subtrie->player);
        }
    }

}
 
// A function to search a pattern in subtree rooted with this node
void search(struct TrieNode *root, string preffix, list<int>* ids)
{
    int i;
    struct TrieNode *subtrie = root;
    
    // cout << "ok";
    for (i = 0; i < preffix.length(); i++)
    {
        int index = preffix[i] - 'a';
        if (!subtrie->children[index])
            return;
 
        subtrie = subtrie->children[index];
    }
    
    search_rec(subtrie, ids);
}
 
// Driver
int main()
{ 
    struct TrieNode *root = getNode();
    list<int>* ids = new list<int>;
    list<int>* idse = new list<int>;
    list<int>::iterator it;
 
    // Construct trie
    insert(root, "fernando", 37);
    insert(root, "ferran", 28);
    insert(root, "fulano", 49);
 
    search(root, "fer", ids);
    for (it=ids->begin(); it!=ids->end(); it++)
        cout << "Player id: " << *it << endl;

    cout << endl;

    search(root, "agnaldo", idse);
    for (it=idse->begin(); it!=idse->end(); it++)
        cout << "Player id: " << *it << endl;

    return 0;
}