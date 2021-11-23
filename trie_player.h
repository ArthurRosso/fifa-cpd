#ifndef TRIE_PLAYER_H
#define TRIE_PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cctype>

using namespace std;
 
const int ALPHABET_SIZE = 28;
 
// trie node
class TriePlayer
{
    public:
    TriePlayer *children[ALPHABET_SIZE];
    int id_player;
};

TriePlayer* newTriePlayer(void);

void insertTriePlayer(TriePlayer *root, int id, string name);

void findPlayerByNameRec(TriePlayer *subtrie, list<int>* ids);

void findPlayerByName(TriePlayer *root, string preffix, list<int>* ids);

#endif /* TRIE_PLAYER_H */