#include <lcthw/darray_algos.h>
#include <stdlib.h>

void swapDArray(void **contents, int i, int j){
    check(contents != NULL, "Content can't be null");
    // printf("TROCANDO: %s por %s\n", (char *)contents[i], (char *)contents[j]);
    void *temp = NULL;

    
    temp = contents[i];
    contents[i] = contents[j];
    contents[j] = temp;

    int k = 0;
    for(k = 0; k < 5; k++){
        // printf("ELEMENTO %d: %s\n", k, (char *)contents[k]);
    }

    // printf("\n");
    error:
        return;
}

void heapify(void **contents, int count, int i, DArray_compare cmp){
    check(contents != NULL, "Contents can't be NULL");
    // printf("INICIANDO HEAPIFY: count: %d i: %d \n", count, i);
    int k = 0;
    for(k = 0; k < 5; k++){
        // printf("ELEMENTO %d: %s\n", k, (char *)contents[k]);
    }

    // printf("\n");

    //Inicia com o maior nó
    int largest = i;

    //Compare the node with your children
    //Left
    //iteration1 = 3
    int left = 2 * i + 1;

    //Right
    //iteration1 = 4
    int right = 2 * i + 2;

    //If left child is larger than root
    // printf("Contents %d: %s\n", largest, (char *)contents[largest]);
    // printf("Contents %d: %s\n", left, (char *)contents[left]);
    if(left < count && cmp(&contents[left], &contents[largest]) > 0){
        largest = left;
    }

    // printf("Contents %d: %s\n", largest, (char *)contents[largest]);
    // printf("Contents %d: %s\n\n", right, (char *)contents[right]);
    if(right < count && cmp(&contents[right], &contents[largest]) > 0){
        largest = right;
    }
    // printf("Maior: %d %s\n", largest, (char *)contents[largest]);
    //If largest is not root
    if(largest != i){
        swapDArray(contents, i, largest);

        //Recursively heapify the affected sub-tree
        heapify(contents, count, largest, cmp); 
    }
    error:
        return;
}

int heapsort(void **contents, int count, DArray_compare cmp){
    check(contents != NULL, "Contents can't be NULL");

    int i = 0;
    
    //Build heap (rearrange array)
    for(i = count / 2 - 1; i >= 0; i--){
        heapify(contents, count, i, cmp);
    }

    //One by one extract an element from heap
    for(i = count - 1; i > 0; i--){
        //Move the current root to end
        swapDArray(contents, 0, i);

        //call max heapify on the reduced heap
        heapify(contents, i, 0, cmp);
    }
    return 0;

    error:
        return -1;
}



int mergesort(void *contents, int count, size_t __size, DArray_compare cmp){


    return 0;
}

int DArray_qsort(DArray *array, DArray_compare cmp){
    qsort(array->contents, DArray_count(array), sizeof(void *), cmp);

    return 0;
}

int DArray_heapsort(DArray *array, DArray_compare cmp){
    heapsort(array->contents, DArray_count(array), cmp);

    return 0;
}

int DArray_mergesort(DArray *array, DArray_compare cmp){
    qsort(array->contents, DArray_count(array), sizeof(void *), cmp);

    return 0;
}