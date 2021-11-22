#include "tags.h"

#define CAPACITY 500 // Size of the Hash Table
  
unsigned long hash_function(char* str) {
    unsigned long i = 0;
    for (int j=0; str[j]; j++)
        i += str[j];
    return i % CAPACITY;
}
 
 
static LinkedList* allocate_list () {
    // Allocates memory for a Linkedlist pointer
    LinkedList* list = (LinkedList*) malloc (sizeof(LinkedList));
    return list;
}
 
static LinkedList* linkedlist_insert(LinkedList* list, t_tag* item) {
    // Inserts the item onto the Linked List
    if (!list) {
        LinkedList* head = allocate_list();
        head->item = item;
        head->next = NULL;
        list = head;
        return list;
    } 
     
    else if (list->next == NULL) {
        LinkedList* node = allocate_list();
        node->item = item;
        node->next = NULL;
        list->next = node;
        return list;
    }
 
    LinkedList* temp = list;
    while (temp->next->next) {
        temp = temp->next;
    }
     
    LinkedList* node = allocate_list();
    node->item = item;
    node->next = NULL;
    temp->next = node;
     
    return list;
}
 
static t_tag* linkedlist_remove(LinkedList* list) {
    // Removes the head from the linked list
    // and returns the item of the popped element
    if (!list)
        return NULL;
    if (!list->next)
        return NULL;
    LinkedList* node = list->next;
    LinkedList* temp = list;
    temp->next = NULL;
    list = node;
    t_tag* it = NULL;
    memcpy(temp->item, it, sizeof(t_tag));
    free(temp->item->key);
    free(temp->item->ids);
    free(temp->item);
    free(temp);
    return it;
}
 
static void free_linkedlist(LinkedList* list) {
    LinkedList* temp = list;
    while (list) {
        temp = list;
        list = list->next;
        free(temp->item->key);
        free(temp->item->ids);
        free(temp->item);
        free(temp);
    }
}
 
static LinkedList** create_overflow_buckets(HashTable* table) {
    // Create the overflow buckets; an array of linkedlists
    LinkedList** buckets = (LinkedList**) calloc (table->size, sizeof(LinkedList*));
    for (int i=0; i<table->size; i++)
        buckets[i] = NULL;
    return buckets;
}
 
static void free_overflow_buckets(HashTable* table) {
    // Free all the overflow bucket lists
    LinkedList** buckets = table->overflow_buckets;
    for (int i=0; i<table->size; i++)
        free_linkedlist(buckets[i]);
    free(buckets);
}
 
 
t_tag* create_item(char* key, int id) {
    // Creates a pointer to a new hash table item
    t_tag* item = (t_tag*) malloc (sizeof(t_tag));
    item->key = (char*) malloc (strlen(key) + 1);
    item->ids = new list<int>;
    item->ids->push_back(id);     
    strcpy(item->key, key);
 
    return item;
}
 
HashTable* create_table(int size) {
    // Creates a new HashTable
    HashTable* table = (HashTable*) malloc (sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (t_tag**) calloc (table->size, sizeof(t_tag*));
    for (int i=0; i<table->size; i++)
        table->items[i] = NULL;
    table->overflow_buckets = create_overflow_buckets(table);
 
    return table;
}
 
void free_item(t_tag* item) {
    // Frees an item
    free(item->key);
    free(item->ids);
    free(item);
}
 
void free_table(HashTable* table) {
    // Frees the table
    for (int i=0; i<table->size; i++) {
        t_tag* item = table->items[i];
        if (item != NULL)
            free_item(item);
    }
 
    free_overflow_buckets(table);
    free(table->items);
    free(table);
}
 
void handle_collision(HashTable* table, unsigned long index, t_tag* item) {
    LinkedList* head = table->overflow_buckets[index];
 
    if (head == NULL) {
        // We need to create the list
        head = allocate_list();
        head->item = item;
        table->overflow_buckets[index] = head;
        return;
    }
    else {
        // Insert to the list
        table->overflow_buckets[index] = linkedlist_insert(head, item);
        return;
    }
 }
 
void ht_insert(HashTable* table, char* key, int id) {
    // Create the item
    t_tag* item = create_item(key, id);
 
    // Compute the index
    unsigned long index = hash_function(key);
 
    t_tag* current_item = table->items[index];
     
    if (current_item == NULL) {
        // Key does not exist.
        if (table->count == table->size) {
            // Hash Table Full
            printf("Insert Error: Hash Table is full\n");
            // Remove the create item
            free_item(item);
            return;
        }
         
        // Insert directly
        table->items[index] = item; 
        table->count++;
    }
 
    else {
            // Scenario 1: We only need to update value
            if (strcmp(current_item->key, key) == 0) {
                for (auto& s_id : *current_item->ids) {
                    if(s_id == id)
                        return;
                }
                table->items[index]->ids->push_back(id);
                return;
            }
     
            else {
                // Scenario 2: Collision
                handle_collision(table, index, item);
                return;
        }
    }
}
 
list<int>* ht_search(HashTable* table, char* key) {
    // Searches the key in the hashtable
    // and returns NULL if it doesn't exist
    int index = hash_function(key);
    t_tag* item = table->items[index];
    LinkedList* head = table->overflow_buckets[index];
 
    // Ensure that we move to items which are not NULL
    while (item != NULL) {
        if (strcmp(item->key, key) == 0)
            return item->ids;
        if (head == NULL)
            return NULL;
        item = head->item;
        head = head->next;
    }
    return NULL;
}

void print_search(HashTable* table, char* key) {
    list<int> *ids;
    ids = ht_search(table, key);
    if (ids->empty() == 1) {
        printf("%s does not exist\n", key);
        return;
    }
    else {
        for (auto& id : *ids) {
            cout << id << "\t" ;
        }
    }
}

// int main(){
//     HashTable* ht = create_table(CAPACITY);
//     ifstream p("tags.csv");
//     CsvParser players(p);
//     for (auto& row : players) {
//         ht_insert(ht, (char*)row[2].c_str(), stoi(row[1]));
//     }
//     print_search(ht, "Acrobat");


//     return 0;

// }