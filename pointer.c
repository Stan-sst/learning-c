
#include <stdio.h>

void asdf(char* key){
    printf("%s\n", key);
}

int main(int argc, char* argv[]){
    char* key = "Happy";
    asdf(key);
    return 0;
}
