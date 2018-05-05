#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include"hashtable.h"

static int HT_PRIME1 = 307;
static int HT_PRIME2 = 311;
static int BASE_SIZE = 50;

static int is_prime(const int n) {
    if (n < 2) {
        return -1;
    }
    if (n == 2) {
        return 1;
    }
    if (n % 2 == 0) {
        return 0;
    }
    for (int i = 3; i <= floor(sqrt((double) n)); i += 2 ) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

static int next_prime(int n) {
    for (n;;n++) {
        if (is_prime(n) == 1) {
            return n;
        }
    }
}

static ht_node HT_DELETED_ITEM = {NULL, NULL};

static ht_node* init_node(const char* key, const char* value) {
    ht_node* node = malloc(sizeof(ht_node));
    node->key = strdup(key);
    node->value = strdup(value);
    return node;
}

static hash_table* new_hash_table(const int size) { 
    hash_table* ht = malloc(sizeof(hash_table));
    ht->base_size = size;
    ht->size = next_prime(size);
    ht->count = 0;

    ht->nodes = calloc((size_t)ht->size, sizeof(ht_node*));

    return ht;
}

hash_table* init_hash_table(){
    return new_hash_table(BASE_SIZE);
}

static void delete_node(ht_node* node){
    free(node->key);
    free(node->value);
    free(node);
}

void delete_table(hash_table* ht){
    for (int i = 0; i < ht->size; i++) {
        ht_node* node = ht->nodes[i];
        if (node != NULL && node != &HT_DELETED_ITEM) {
            delete_node(node);
        }
    }
    free(ht->nodes);
    free(ht);
}

static int hash(const char* s, const int prime, const int hash_length) {
    int hash = 0;
    const int len_s = strlen(s);
    for (int i = 0; i < len_s; i++) {
        hash += (long)(pow(prime, len_s - (i + 1))) * s[i];
        hash = hash % hash_length;
    }
    return hash;
}

static int ht_hash(const char* s, const int hash_length, const int attempts) {
    int hash1 = hash(s, HT_PRIME1, hash_length);
    int hash2 = hash(s, HT_PRIME2, hash_length);
    return (hash1 + (attempts * (hash2+1))) % hash_length;
}

static void resize_table(hash_table* ht, const int base_size) {
    if (base_size < BASE_SIZE) {
        return;
    }
    hash_table* ht_new = new_hash_table(base_size);

    for (int i = 0; i < ht->size; i++) {
        ht_node* temp_node = ht->nodes[i];
        if (temp_node != NULL && temp_node != &HT_DELETED_ITEM) {
            insert_node(ht_new, temp_node->key, temp_node->value);
        }
    }
    ht->base_size = ht_new->base_size;
    ht->count = ht_new->count;
    
    ht_node** temp_nodes = ht_new->nodes;
    ht_new->nodes = ht->nodes;
    ht->nodes = temp_nodes;

    const int temp_size = ht_new->size;
    ht_new->size = ht->size;
    ht->size = temp_size;

    delete_table(ht_new);
}

static void resize_up(hash_table* ht) {
    resize_table(ht, ht->base_size * 2);
}

static void resize_down(hash_table* ht) {
    resize_table(ht, ht->base_size * 0.5);
}

void insert_node(hash_table* ht, const char* key, const char* value) {
    if (ht->count >= 0.7 * ht->base_size) {
        resize_up(ht);
    }
    ht_node* node = init_node(key, value);
    int index = ht_hash(node->key, ht->size, 0);
    ht_node* curr_node = ht->nodes[index];
    int i = 1;
    while (curr_node != NULL)  {
        if (curr_node != &HT_DELETED_ITEM) {
            if (strcmp(key, curr_node->key) == 0) {
                delete_node(curr_node);
                ht->nodes[index] = node;
                return;
            }
        }
        index = ht_hash(node->key, ht->size, i);
        curr_node = ht->nodes[index];
        i++;
    }
    ht->nodes[index] = node;
    ht->count++;
}

char* search_node(hash_table* ht, const char* key) {
    int i = 0;
    int index = ht_hash(key, ht->size, i);
    ht_node* curr_node = ht->nodes[index];
    while (curr_node != NULL){
        if (curr_node != &HT_DELETED_ITEM) {
            if (strcmp(key, curr_node->key) == 0) {
                return curr_node->value;
            }
        }
        i++;
        index = ht_hash(key, ht->size, i);
        curr_node = ht->nodes[index];
    }
    return NULL;
}

void remove_node(hash_table* ht, const char* key) {
    if (ht->count <= 0.1 * ht->base_size) {
        resize_down(ht);
    }
    int index = ht_hash(key, ht->size, 0);
    ht_node* curr_node = ht->nodes[index];
    int i = 1;
    while (curr_node != NULL) {
        if (curr_node != &HT_DELETED_ITEM) {
            if (strcmp(key, curr_node->key) == 0) {
                delete_node(curr_node);
                ht->nodes[index] = &HT_DELETED_ITEM;
            }
        }
        index = ht_hash(key, ht->size, i);
        curr_node = ht->nodes[index];
        i++;
    }
    ht->count--;
}
