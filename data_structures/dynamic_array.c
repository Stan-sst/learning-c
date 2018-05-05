
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"dynamic_array.h"

static int DEFAULT_SIZE = 8;

static dy_array* new_array(int base_size) {
    dy_array* da = malloc(sizeof(dy_array));
    da->size = base_size;
    da->count = 0;

    da->arr = calloc((size_t)da->size, sizeof(char*));

    return da;
}

dy_array* init_array() {
    return new_array(DEFAULT_SIZE);
}


void delete_array(dy_array* da) {
    for (int i = 0; i < da->size; i++) {
        free(da->arr[i]);
    }
    free(da->arr);
    free(da);
}


static void resize(dy_array* da, int new_size) {
    dy_array* new_da = new_array(new_size);
        
    for (int i = 0; i < da->size; i++) {
        append(new_da, da->arr[i]);
    }

    int temp_size = new_da->size;
    new_da->size = da->size;
    da->size = temp_size;

    char** temp_arr = new_da->arr;
    new_da->arr = da->arr;
    da->arr = temp_arr;

    delete_array(new_da);
}


static void size_up(dy_array* da) {
    resize(da, da->size * 2);
}


void append(dy_array* da, char* c) {
    if (da->count >= da->size) {
        size_up(da);
    }
    da->arr[da->count] = strdup(c);
    da->count++;
}


char* get(dy_array* da, int index) {
    if (index > da->count) {
        perror("Out of bounds exception");
        return -1;
    }
    return da->arr[index];
}
