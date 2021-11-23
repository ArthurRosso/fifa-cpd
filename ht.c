// Simple hash table implemented in C.

#include "ht.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Hash table entry (slot may be filled or empty).
typedef struct {
    const char* key;  // key is NULL if this slot is empty
    LinkedList* value;
} ht_entry;

// Hash table structure: create with ht_create, free with ht_destroy.
struct ht {
    ht_entry* entries;  // hash slots
    size_t capacity;    // size of _entries array
    size_t length;      // number of ids in hash table
};

#define INITIAL_CAPACITY 16  // must not be zero

ht* ht_create() {
    // Allocate space for hash table struct.
    ht* table = (ht*)malloc(sizeof(ht));
    if (table == NULL) {
        return NULL;
    }
    table->length = 0;
    table->capacity = INITIAL_CAPACITY;

    // Allocate (zero'd) space for entry buckets.
    table->entries = (ht_entry*)calloc(table->capacity, sizeof(ht_entry));
    if (table->entries == NULL) {
        free(table); // error, free table before we return!
        return NULL;
    }
    return table;
}

void ht_destroy(ht* table) {
    // First free allocated keys.
    for (size_t i = 0; i < table->capacity; i++) {
        if (table->entries[i].key != NULL) {
            free((void*)table->entries[i].key);
        }
    }

    // Then free entries array and table itself.
    free(table->entries);
    free(table);
}

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

// Return 64-bit FNV-1a hash for key (NUL-terminated). See description:
// https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
static uint64_t hash_key(const char* key) {
    uint64_t hash = FNV_OFFSET;
    for (const char* p = key; *p; p++) {
        hash ^= (uint64_t)(unsigned char)(*p);
        hash *= FNV_PRIME;
    }
    return hash;
}

LinkedList* ht_get(ht* table, const char* key) {
    // AND hash with capacity-1 to ensure it's within entries array.
    uint64_t hash = hash_key(key);
    size_t index = (size_t)(hash & (uint64_t)(table->capacity - 1));

    // Loop till we find an empty entry.
    while (table->entries[index].key != NULL) {
        if (strcmp(key, table->entries[index].key) == 0) {
            // Found key, return value.
            return table->entries[index].value;
        }
        // Key wasn't in this slot, move to next (linear probing).
        index++;
        if (index >= table->capacity) {
            // At end of entries array, wrap around.
            index = 0;
        }
    }
    return NULL;
}

// Internal function to set an entry (without expanding table).
static const char* ht_set_entry(ht_entry* entries, size_t capacity, const char* key, LinkedList* value, size_t* plength) {
    // AND hash with capacity-1 to ensure it's within entries array.
    uint64_t hash = hash_key(key);
    size_t index = (size_t)(hash & (uint64_t)(capacity - 1));


    // Loop till we find an empty entry.
    while (entries[index].key != NULL) {
        if (strcmp(key, entries[index].key) == 0) {
            // Found key (it already exists), add value to head of linked list
            entries[index].value=value;
            return entries[index].key;
        }
        // Key wasn't in this slot, move to next (linear probing).
        index++;
        if (index >= capacity) {
            // At end of entries array, wrap around.
            index = 0;
        }
    }

    // Didn't find key, allocate+copy if needed, then insert it.
    if (plength != NULL) {
        key = strdup(key);
        if (key == NULL) {
            return NULL;
        }
        (*plength)++;
    }
    entries[index].key = (char*)key;
    entries[index].value=value;
    return key;
}

// Expand hash table to twice its current size. Return true on success,
// false if out of memory.
static bool ht_expand(ht* table) {
    // Allocate new entries array.
    size_t new_capacity = table->capacity * 2;
    if (new_capacity < table->capacity) {
        return false;  // overflow (capacity would be too big)
    }
    ht_entry* new_entries = (ht_entry*)calloc(new_capacity, sizeof(ht_entry));
    if (new_entries == NULL) {
        return false;
    }

    // Iterate entries, move all non-empty ones to new table's entries.
    for (size_t i = 0; i < table->capacity; i++) {
        ht_entry entry = table->entries[i];
        if (entry.key != NULL) {
            ht_set_entry(new_entries, new_capacity, entry.key, entry.value, NULL);
        }
    }

    // Free old entries array and update this table's details.
    free(table->entries);
    table->entries = new_entries;
    table->capacity = new_capacity;
    return true;
}

const char* ht_set(ht* table, const char* key, LinkedList* value) {

    // If length will exceed half of current capacity, expand it.
    if (table->length >= table->capacity / 2) {
        if (!ht_expand(table)) {
            return NULL;
        }
    }
    
    // Set entry and update length.
    return ht_set_entry(table->entries, table->capacity, key, value, &table->length);
}

size_t ht_length(ht* table) {
    return table->length;
}

hti ht_iterator(ht* table) {
    hti it;
    it._table = table;
    it._index = 0;
    return it;
}

bool ht_next(hti* it) {
    // Loop till we've hit end of entries array.
    ht* table = it->_table;
    while (it->_index < table->capacity) {
        size_t i = it->_index;
        it->_index++;
        if (table->entries[i].key != NULL) {
            // Found next non-empty id, update iterator key and value.
            ht_entry entry = table->entries[i];
            it->key = entry.key;
            it->value = entry.value;
            return true;
        }
    }
    return false;
}


// Returns the last LinkedList of the list
struct LinkedList* getTail(struct LinkedList* cur)
{
    while (cur != NULL && cur->next != NULL)
        cur = cur->next;
    return cur;
}
 
// Partitions the list taking the last element as the pivot
struct LinkedList* partitionPlayerTag(struct LinkedList* head, struct LinkedList* end,
                       struct LinkedList** newHead,
                       struct LinkedList** newEnd)
{
    struct LinkedList* pivot = end;
    struct LinkedList *prev = NULL, *cur = head, *tail = pivot;
 
    // During partition, both the head and end of the list
    // might change which is updated in the newHead and
    // newEnd variables
    while (cur != pivot) {
        if (cur->id < pivot->id) {
            // First LinkedList that has a value less than the
            // pivot - becomes the new head
            if ((*newHead) == NULL)
                (*newHead) = cur;
 
            prev = cur;
            cur = cur->next;
        }
        else // If cur LinkedList is greater than pivot
        {
            // Move cur LinkedList to next of tail, and change
            // tail
            if (prev)
                prev->next = cur->next;
            struct LinkedList* tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }
 
    // If the pivot data is the smallest element in the
    // current list, pivot becomes the head
    if ((*newHead) == NULL)
        (*newHead) = pivot;
 
    // Update newEnd to the current last LinkedList
    (*newEnd) = tail;
 
    // Return the pivot LinkedList
    return pivot;
}
 
// here the sorting happens exclusive of the end LinkedList
struct LinkedList* sortPlayerTagRec(struct LinkedList* head,
                            struct LinkedList* end)
{
    // base condition
    if (!head || head == end)
        return head;
 
    LinkedList *newHead = NULL, *newEnd = NULL;
 
    // Partition the list, newHead and newEnd will be
    // updated by the partition function
    struct LinkedList* pivot = partitionPlayerTag(head, end, &newHead, &newEnd);
 
    // If pivot is the smallest element - no need to recur
    // for the left part.
    if (newHead != pivot) {
        // Set the LinkedList before the pivot LinkedList as NULL
        struct LinkedList* tmp = newHead;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = NULL;
 
        // Recur for the list before pivot
        newHead = sortPlayerTagRec(newHead, tmp);
 
        // Change next of last LinkedList of the left half to
        // pivot
        tmp = getTail(newHead);
        tmp->next = pivot;
    }
 
    // Recur for the list after the pivot element
    pivot->next = sortPlayerTagRec(pivot->next, newEnd);
 
    return newHead;
}
 
// The main function for quick sort. This is a wrapper over
// recursive function quickSortRecur()
void sortPlayerTag(struct LinkedList** headRef)
{
    (*headRef) = sortPlayerTagRec(*headRef, getTail(*headRef));
    return;
}

struct LinkedList* sortedIntersect(struct LinkedList* a, struct LinkedList* b){/* base case */
    if (a == NULL || b == NULL)
        return NULL;
 
    /* If both lists are non-empty */
 
    /* advance the smaller list and call recursively */
    if (a->id < b->id)
        return sortedIntersect(a->next, b);
 
    if (a->id > b->id)
        return sortedIntersect(a, b->next);
 
    // Below lines are executed only
    // when a->id == b->id
    struct LinkedList* temp = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    temp->id = a->id;
 
    /* advance both lists and call recursively */
    temp->next = sortedIntersect(a->next, b->next);
    return temp;
}
 