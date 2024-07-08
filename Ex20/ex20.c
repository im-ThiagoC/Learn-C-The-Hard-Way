#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "dbg.h"

//A typedef creates a fake type, in this case for a function pointer
typedef int (*compare_cb) (int a, int b);

//Foward Functions
void die(const char *message);
void testSorting(int *numbers, int count, char sortType, char sortOrder);
int partition(int *numbers, int low, int high);
void swap(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

//Sorting Functions
int *bubbleSorting(int *numbers, int count, compare_cb cmp);
int *quickSortingStart(int *numbers, int count);
void quickSort(int *numbers, int low, int high);

//Orders
int sortedOrder(int a, int b);
int reversedOrder(int a, int b);
int strangeOrder(int a, int b);

int main (int argc, char* argv[]){
    if(argc < 4){
        printf("Supported sortType:\n b = bubbleSort\n q = quickSort\n");
        printf("Supported sortOrder:\n s = sorted\n r = reversed\n t=strange\n");
        die("USAGE: ex18 <sortType> <sortOrder> 4 3 1 5 6");
    }

    int count = argc - 3;
    int i = 0;
    char sortType = argv[1][0];
    char sortOrder = argv[2][0];

    char **inputs = argv + 3;
    
    /*int *numbers = malloc(99999999999999999999 * sizeof(int));
    if(!numbers){
        die("Memory Error in Numbers.");
    }*/
   int *numbers = malloc(count * sizeof(int));
   check(numbers, "Memory Error in Numbers");

    for(i = 0; i < count; i++){
        numbers[i] = atoi(inputs[i]);
    }
    
    testSorting(numbers, count, sortType, sortOrder);

    free(numbers);

    return 0;

    error:

    return 1;
}


void testSorting(int *numbers, int count, char sortType, char sortOrder){
    int i = 0;
    int *sorted;
    compare_cb cmp;

    //Switch for each Order, default is sorted
    switch (sortOrder)
    {
    case 's':
        cmp = sortedOrder;
        break;
    
    case 'r':
        cmp = reversedOrder;
        break;

    case 't':
        cmp = strangeOrder;
        break;
    
    default:
        cmp = sortedOrder;
        break;
    }

    //Switch for each Sort Algoritm, default is Bubble Sorting
    switch (sortType)
    {
    case 'b':
        printf("Bubble Sorting\n");
        sorted = bubbleSorting(numbers, count, cmp);
        break;
    
    case 'q':
        printf("Quick Sorting, only Sorted Order\n");
        sorted = quickSortingStart(numbers, count);
        break;
    
    default:
        printf("Default: Bubble Sorting\n");
        sorted = bubbleSorting(numbers, count, cmp);
        break;
    }

    if(!sorted){
        die("Failed to sort as requested.");
    }

    for(i = 0; i < count; i++){
        printf("%d ", sorted[i]);
    }
    printf("\n");

    free(sorted);
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

int *quickSortingStart(int *numbers, int count){
    int *target = malloc(count * sizeof(int));
    if(!target){
        die("Memory error on Target - QuickSortingStart");
    }

    memcpy(target, numbers, count*sizeof(int));

    quickSort(target, 0, count-1);

    return target;
}

void quickSort(int *target, int low, int high){
    if(low < high){
        int pivot = partition(target, low, high);

        quickSort(target, low, pivot-1);
        quickSort(target, pivot + 1, high);
    }
}

int partition(int *target, int low, int high){
    int pivot = target[high];
    int i = low - 1;

    for(int j = low; j <= high - 1; j++){
        //If the element is lower or equal than pivot
        if(target[j] <= pivot){
            i++;
            swap(&target[i], &target[j]);
        }
    }

    swap(&target[i+1], &target[high]);
    return i + 1;
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