#include <stdio.h> 

int square(int input) {
    int root = 0;
    while (input != root * root) {
        root++;
    }
    return root;
}

int main(){
    printf("%d\n", square(16));
    return 0;
};
