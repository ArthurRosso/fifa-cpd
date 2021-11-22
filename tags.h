#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include "./csv-parser/parser.hpp"
#include <sstream>

using namespace aria::csv;
using namespace std;

#define CAPACITY 500 // Size of the Hash Table
 
unsigned long hash_function(char* str);

 typedef struct t_tag {
    char* key;
    list<int>* ids;
}t_tag;
 
 typedef struct LinkedList {
    t_tag* item; 
    LinkedList* next;
}LinkedList;
 
typedef struct HashTable {
    // Contains an array of pointers
    // to items
    t_tag** items;
    LinkedList** overflow_buckets;
    int size;
    int count;
}HashTable;
 
static LinkedList* allocate_list ();
static LinkedList* linkedlist_insert(LinkedList* list, t_tag* item);
static t_tag* linkedlist_remove(LinkedList* list);
static void free_linkedlist(LinkedList* list);

static LinkedList** create_overflow_buckets(HashTable* table);
static void free_overflow_buckets(HashTable* table);

t_tag* create_item(char* key, int id);
void free_item(t_tag* item);
HashTable* create_table(int size);
void free_table(HashTable* table);

void handle_collision(HashTable* table, unsigned long index, t_tag* item);

void ht_insert(HashTable* table, char* key, int id);
list<int>* ht_search(HashTable* table, char* key);

void print_search(HashTable* table, char* key);