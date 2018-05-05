#ifndef HASH_TABLE_H
#define HASH_TABLE_H

typedef struct ht_node{
    char* key;
    char* value;
} ht_node;

typedef struct hash_table {
    int size;
    int base_size;
    int count;
    ht_node** nodes;
} hash_table;

hash_table* init_hash_table();

void delete_table(hash_table* ht);

void insert_node(hash_table* ht, const char* key, const char* value);

char* search_node(hash_table* ht, const char* key);

void remove_node(hash_table* ht, const char* key);

#endif
