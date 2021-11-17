#include "triePlayer.h"

TriePlayer* newTriePlayer(void)
{
    TriePlayer* tplayer =  new TriePlayer();
 
    tplayer->id_player = 0;
 
    for (int i = 0; i < ALPHABET_SIZE; i++)
        tplayer->children[i] = NULL;
 
    return tplayer;
}

void insertTriePlayer(TriePlayer *root, int id, string name)
{
 
    for (int i = 0; i < name.length(); i++)
    {
        int index = tolower(name[i]) - 'a';
        if (!root->children[index])
            root->children[index] = newTriePlayer();
 
        root = root->children[index];
    }
 
    root->id_player = id;
}

void findPlayerByNameRec(TriePlayer *subtrie, list<int>* ids)
{
    int i;
    if(subtrie){
        for(i=0; i<ALPHABET_SIZE; i++){
            findPlayerByNameRec(subtrie->children[i], ids);
        }
        if(subtrie->id_player != 0){
            ids->push_back(subtrie->id_player);
        }
    }

}


void findPlayerByName(TriePlayer *root, string preffix, list<int>* ids)
{
    int i;
    TriePlayer *subtrie = root;
    
    for (i = 0; i < preffix.length(); i++)
    {
        int index = tolower(preffix[i]) - 'a';
        if (!subtrie->children[index])
            return;
 
        subtrie = subtrie->children[index];
    }
    
    findPlayerByNameRec(subtrie, ids);
}