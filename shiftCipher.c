#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct _shift_cipher {
    int key;
    char* message;
} shift_cipher;

shift_cipher* init_shift_cipher(int key, char* message) {
    shift_cipher* sc = malloc(sizeof(shift_cipher));
    sc->key = key;
    sc->message = strdup(message);
    return sc;
}

char* shift(shift_cipher* sc) {
    char* buffer = malloc((strlen(sc->message)) * sizeof(char));
    for (int i = 0; i < strlen(sc->message); i++) {
        int ascii = ((int)sc->message[i] + sc->key) % (int)'z';
        if (ascii < (int)'a') {
            buffer[i] = (char)(ascii + (int)'a');
        } else {
            buffer[i] = (char)(ascii);
        }
    }
    return buffer;
}

void delete_shift_cipher(shift_cipher* sc) {
    free(sc->message);
    free(sc);
}


int main() {
    shift_cipher* sc = init_shift_cipher(2, "hello");
    printf("%s\n", sc->message);
    
    char* buffer = shift(sc);
    printf("%s\n",buffer);

    delete_shift_cipher(sc);
    free(buffer);
    return 0;
}
