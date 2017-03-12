#include <stdio.h>

struct average{
    int num;
    float sum;
};

typedef struct average ave;

void average_init(ave* ave){
    ave->num = 0.0;
    ave->sum = 0.0;
}

int sumsum(int elements, ave* ave){
    int n;
    for (int i = 0; i < elements; i++){
        scanf("%d",&n);
        ave->num += n;
    }
    ave->sum = (float)ave->num/elements; 
}
            

int main(int argc, char* argv[]){
    //Creating struct
    int a;
    ave ave;
    average_init(&ave);

    //User input elements
    printf("Enter amount of elements: \n");
    scanf("%d",&a);

    //Run average method
    sumsum(a, &ave);

    //output
    printf("The sum is: %d \nThe average is %.2f\n",ave.num, ave.sum);
    return 0;
}
