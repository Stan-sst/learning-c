
#include <stdio.h>

int main(int argc, char* argv[]){
    for (int i=1; i<11; i++ ){
        for(int x=1; x <= i; x++ ){
            printf ("%s", "*");
        }
        printf("\n");
    }
    return 0;
};
