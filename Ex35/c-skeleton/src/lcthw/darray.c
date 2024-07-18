#include <lcthw/darray.h>
#include <assert.h>

DArray *DArray_create(size_t element_size, size_t initial_max){
    DArray *array = malloc(sizeof(DArray));
    check_mem(array);
    array->max = initial_max;
    check(array->max > 0, "You must set an initial_max > 0.");

    array->contents = calloc(initial_max, sizeof(void *));
    check_mem(array->contents);

    array->end = 0;
    array->element_size = element_size;
    array->expand_rate = DEFAULT_EXPAND_RATE;

    return array;

    error:
        DArray_destroy(array);
        return NULL;
}

void DArray_clear(DArray *array){
    check(array != NULL, "Invalid array to clear.");
    int i = 0;

    if(array->element_size > 0){
        for(i = 0; i < array->max; i++){
            if(array->contents[i] != NULL){
                free(array->contents[i]);
            }
        }
    }

    error:
        return;
}

static inline int DArray_resize(DArray *array, size_t newsize){
    check(array != NULL, "Invalid array to resize.");
    array->max = newsize;
    check(array->max > 0, "The newsize must be > 0.");

    void *contents = realloc(array->contents, array->max * sizeof(void *));

    //check contents and assume realloc doesn't harm the original on error
    check_mem(contents);

    array->contents = contents;

    return 0;
    error:
        return -1;
}

int DArray_expand(DArray *array){
    check(array != NULL, "Invalid array to expand.");
    size_t old_max = array->max;
    check(DArray_resize(array, array->max + array->expand_rate) == 0, "Failed to expand array to new size: %d", array->max + (int)array->expand_rate);

    memset(array->contents + old_max, 0, array->expand_rate + 1);
    return 0;

    error:
        return -1;
}

int DArray_contract(DArray *array){
    check(array != NULL, "Invalid array to contract.");
    int new_size = array->end < (int)array->expand_rate ? (int)array->expand_rate : array->end;

    return DArray_resize(array, new_size + 1);
    error:
        return -1;
}

void DArray_destroy(DArray *array){
    check(array != NULL, "Invalid array to destroy.");
    if(array){
        if(array->contents){
            free(array->contents);
        }
        free(array);
    }

    error:
        return;
}

void DArray_clean_destroy(DArray *array){
    DArray_clear(array);
    DArray_destroy(array);
}

int DArray_push(DArray *array, void *value){
    check(array != NULL, "Invalid array to push.");
    check(value != NULL, "Value can't be NULL");

    array->contents[array->end] = value;
    array->end++;

    if(DArray_end(array) >= DArray_max(array)){
        return DArray_expand(array);
    } else {
        return 0;
    }

    error:
        return -1;
}

void *DArray_pop(DArray *array){
    check(array != NULL, "Invalid array to pop.");
    check(array->end - 1 >= 0, "Attempt to pop empty array.");

    void *value = DArray_remove(array, array->end - 1);
    array->end--;

    if(DArray_end(array) > (int)array->expand_rate && DArray_end(array) % array->expand_rate) {
        DArray_contract(array);
    }

    return value;
    error:
        return NULL;
}

void DArray_print(DArray *array){
    check(array != NULL, "Invalid array to print");
    
    int i = 0;
    int size = array->end;

    for(i = 0; i < size; i++){
        printf("Element %d: %s\n", i, (char *)DArray_get(array, i));
    }

    error:
        return;
}