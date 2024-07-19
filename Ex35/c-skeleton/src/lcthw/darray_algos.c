#include <lcthw/darray_algos.h>
#include <stdlib.h>
#include <stdint.h>

void printArray(void **contents, int count){
    printf("Printando Array:\n");
    if(count == 0)
       return;
    int i = 0;
    for(i = 0; i < count; i++){
        printf("Element %d: %s\n", i, (char *)contents[i]);
    }
}

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

int merge(void **contents, int init, int middle, int end, DArray_compare cmp){
    check(contents != NULL, "Contents can't be null in merge");

    int init1 = init;
    int init2 = middle + 1;

    int aux = 0;
    int len = end - init + 1;

    // printf("test\n");
    // printf("init1 = %d\ninit2 = %d\nmiddle = %d\n end = %d\n aux = %d\nlen = %d\n",init1, init2, middle, end, aux, len);
    void **tempArray = (void **)malloc(len * sizeof(void *));
    while(init1 <= middle && init2 <= end){
        // printf("entrou aqui\n");
        // printf("COMPARANDO %s COM %s para\n init1 = %d\ninit2 = %d\nmiddle = %d\n end = %d\n aux = %d\nRESULTADO: %d\n  ",(char *)contents[init1], (char*)contents[init2], init1, init2, middle, end, aux, (cmp(&contents[init1], &contents[init2])));
        if(cmp(&contents[init1], &contents[init2]) < 0){
            // printf("INSERINDO %s\n", (char *)contents[init1]);
            tempArray[aux] = contents[init1];
            init1++;
        } else {
            // printf("INSERINDO %s\n", (char *)contents[init2]);
            tempArray[aux] = contents[init2];
            init2++;
        }
        aux++;
    }
    // printf("Saiu do primeiro while\n");

    // printArray(tempArray, aux);

    //Se sobrar elementos na primeira parte
    while(init1 <= middle){
        // printf("INSERINDO %s\n", (char *)contents[init1]);
        tempArray[aux] = contents[init1];
        aux++;
        init1++;
    }

    //Se sobrar elementos na segunda parte
    while(init2 <= end){
        // printf("INSERINDO %s\n", (char *)contents[init2]);
        tempArray[aux] = contents[init2];
        aux++;
        init2++;
    }

    //Salva os elementos no vetor principal
    for(aux = init; aux <= end; aux++){
        contents[aux] = tempArray[aux-init];
    }
    // printf("SALVANDO:\n");
    // printArray(contents, end);

    free(tempArray);
    return 0;
    error:
        return -1;
}

int mergesort(void **contents, int init, int count, DArray_compare cmp){
    check(contents != NULL, "Contents can't be null in mergesort");
    // printf("new\n");
    //If contents have one element
    if(count == 1)
        return 0;

    if(init < count){
        int middle = (count + init) / 2;
        // printf("Entrando em mais um loop\n");
        mergesort(contents, init, middle, cmp);
        // printf("new2\n");
        mergesort(contents, middle+1, count, cmp);
        // printf("new3\n");
        merge(contents, init, middle, count, cmp);
        // printf("new4\n");
    }

    // printf("PRINTANDO ARRAY:\n");
    // printArray(contents, count);
    // printf("saindo\n");
    return 0;
    error:
        return -1;
}

int DArray_qsort(DArray *array, DArray_compare cmp){
    qsort(array->contents, DArray_count(array), sizeof(void *), cmp);

    return 0;
}

int DArray_heapsort(DArray *array, DArray_compare cmp){
    int rc = heapsort(array->contents, DArray_count(array), cmp);
    check(rc == 0, "Error in heap sort.");

    return 0;
    error:
        return -1;
}

int DArray_mergesort(DArray *array, DArray_compare cmp){
    int rc = mergesort(array->contents, 0, DArray_count(array)-1, cmp);
    check(rc == 0, "Error in merge sort.");

    return 0;
    error:
        return -1;
}

int DArray_sort_add(DArray *array, void *value, DArray_compare cmp){
    check(array != NULL, "Array cant be null in sort_add");
    check(value != NULL, "value cant be null in sort_add");
    DArray_push(array, value);

    int rc = heapsort(array->contents, DArray_count(array), cmp);
    check(rc == 0, "Erro in heapsort - sort_add");

    return 0;
    error:
        return -1;
}

int DArray_find(DArray *array, void *to_find, DArray_compare cmp){
    int low = 0;
    int high = array->end - 1;

    void **data = array->contents;

    while(low <= high){
        int middle = low + (high - low) / 2;
        void *key = data[middle];
        if(cmp(&to_find, &key) < 0){
            high = middle - 1;
        } else if(cmp(&to_find, &key) > 0){
            low = middle + 1;
        } else {
            return 0;
        }
    }

    return 1;
}