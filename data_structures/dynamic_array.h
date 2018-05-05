#ifndef DYNAMIC_ARRAY_H

#define DYNAMIC_ARRAY_H

typedef struct dy_array {
    int count;
    int size;
    char** arr;
} dy_array;

dy_array* init_array();

void delete_array(dy_array* da);

void append(dy_array* da, char* c);

char* get(dy_array* da, int index);

#endif
