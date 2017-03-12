
#include <stdio.h>

void asdf(int num){
    printf("%s\n", num % 2 == 0 ? "true" : "false");
}

int main(int argc, char* argv[]){
    int num = 5;
    asdf(num);
    return 0;
}
