#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

//A typedef creates a fake type, in this case for a function pointer
typedef int (*compare_cb) (int a, int b);

//Foward Functions
void die(const char *message);
void testSorting(int *numbers, int count, compare_cb cmp);
int *bubbleSorting(int *numbers, int count, compare_cb cmp);

//Orders
int sortedOrder(int a, int b);
int reversedOrder(int a, int b);
int strangeOrder(int a, int b);

int main (int argc, char* argv[]){
    if(argc < 2){
        die("USAGE: ex18 4 3 1 5 6");
    }

    int count = argc - 1;
    int i = 0;

    char **inputs = argv + 1;

    int *numbers = malloc(count * sizeof(int));
    if(!numbers){
        die("Memory Error in Numbers.");
    }

    for(i = 0; i < count; i++){
        numbers[i] = atoi(inputs[i]);
    }

    testSorting(numbers, count, sortedOrder);
    testSorting(numbers, count, reversedOrder);
    testSorting(numbers, count, strangeOrder);

    free(numbers);

    return 0;
}

int *bubbleSorting(int *numbers, int count, compare_cb cmp){
    int temp = 0;
    int i = 0;
    int j = 0;
    int *target = malloc(count * sizeof(int));

    if(!target){
        die("Memory error on target - bubbleSorting");
    }

    memcpy(target, numbers, count * sizeof(int));

    for(i = 0; i < count; i++){
        for(j = 0; j < count - 1; j++){
            if(cmp(target[j], target[j+1]) > 0){
                temp = target[j + 1];
                target[j + 1] = target[j];
                target[j] = temp;
            }
        }
    }

    return target;
}

void testSorting(int *numbers, int count, compare_cb cmp){
    int i = 0;
    int *sorted = bubbleSorting(numbers, count, cmp);

    if(!sorted){
        die("Failed to sort as requested.");
    }

    for(i = 0; i < count; i++){
        printf("%d", sorted[i]);
    }
    printf("\n");

    free(sorted);
}

void die(const char *message){
    if(errno){
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

int sortedOrder(int a, int b){
    return a - b;
}

int reversedOrder(int a, int b){
    return b - a;
}

int strangeOrder(int a, int b){
    if(a == 0 || b == 0){
        return 0;
    } else {
        return a % b;
    }
}