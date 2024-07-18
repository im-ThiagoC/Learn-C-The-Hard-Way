#include "minunit.h"
#include <lcthw/darray.h>
#include <lcthw/list.h>
#include <time.h>

static DArray *array = NULL;

static int *val1 = NULL;
static int *val2 = NULL;
static int *val3 = NULL;

char *test_create(){
    array = DArray_create(sizeof(int), 100);
    mu_assert(array != NULL, "DArray_create failed");
    mu_assert(array->contents != NULL, "Contents are wrong in darray");
    mu_assert(array->end == 0, "end isn't at the right spot");
    mu_assert(array->element_size == sizeof(int), "Element size is wrong");
    mu_assert(array->max == 100, "Wrong max length on initial size.");

    return NULL;
}

char *test_destroy(){
    DArray_destroy(array);

    return NULL;
}

char *test_new(){
    val1 = DArray_new(array);
    mu_assert(val1 != NULL, "Failed to make a new element");

    val2 = DArray_new(array);
    mu_assert(val2 != NULL, "Failed to make a new element");

    val3 = DArray_new(array);
    mu_assert(val3 != NULL, "Failed to make a new element");

    return NULL;
}

char *test_set(){

    DArray_set(array, 0, val1);
    DArray_set(array, 1, val2);
    DArray_set(array, 2, val3);

    DArray_push(array, "teste");
    //DArray_print(array);
    return NULL;
}

char *test_get(){
    mu_assert(DArray_get(array, 0) == val1, "Wrong first value.");
    mu_assert(DArray_get(array, 1) == val2, "Wrong second value.");
    //mu_assert(DArray_get(array, 2) == val3, "Wrong third value.");

    return NULL;
}

char *test_remove(){
    int *val_check = DArray_remove(array, 0);

    mu_assert(val_check != NULL, "Should not get NULL");
    mu_assert(*val_check == *val1, "Should get the first value.");
    mu_assert(DArray_get(array, 0) == NULL, "Should be gone.");

    DArray_free(val_check);

    val_check = DArray_remove(array, 1);
    mu_assert(val_check != NULL, "Should not get NULL 2");
    mu_assert(*val_check == *val2, "Should get the second value");
    mu_assert(DArray_get(array, 1) == NULL, "Should be gone.");

    DArray_free(val_check);

    return NULL;
}

char *test_expand_contract(){
    int old_max = array->max;
    DArray_expand(array);
    mu_assert((unsigned int) array->max == old_max + array->expand_rate, "Wrong size after expand.");

    DArray_contract(array);
    mu_assert((unsigned int) array->max == array->expand_rate + 1, "Should stay at the expand_rate at least.");

    DArray_contract(array);
    mu_assert((unsigned int) array->max == array->expand_rate + 1, "Should stay at the expand_rate at least again.");

    return NULL;
}

char *test_push_pop(){
    int i = 0;
    for(i = 0; i < 3; i++){
        int *val = DArray_new(array);
        *val = i;
        DArray_push(array, val);
    }

    //mu_assert(array->max == 1201, "Wrong max size.");

    for(i = 2; i >= 0; i--){
        int *val = DArray_pop(array);
        mu_assert(val != NULL, "Shouldn't get a NULL");
        mu_assert(*val == i, "Wrong value");
    }

    

    return NULL;
}

/*Extra Credits*/
static List *list;

char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";

char *test_create_list() {
    list = List_create();
    mu_assert(list != NULL, "Failed to create list.");

    return NULL;
}

char *test_push_pop_list() {
    List_push(list, test1);
    mu_assert(List_last(list) == test1, "Wrong last value.");

    List_push(list, test2);
    mu_assert(List_last(list) == test2, "Wrong last value.");

    List_push(list, test3);
    mu_assert(List_last(list) == test3, "Wrong last value.");
    mu_assert(List_count(list) == 3, "Wrong count on push.");

    char *val = List_pop(list);
    mu_assert(val == test3, "Wrong value on pop.");

    val = List_pop(list);
    mu_assert(val == test2, "Wrong value on pop.");

    val = List_pop(list);
    mu_assert(val == test1, "Wrong value on pop");
    mu_assert(List_count(list) == 0, "Wrong count after pop");

    return NULL;
}

char *test_destroy_list() {

    List_destroy(list);

    return NULL;
}

clock_t start, end;
double cpu_time_used;

char *all_tests(){

    mu_suite_start();
    
    start = clock();
    mu_run_test(test_create);
    mu_run_test(test_new);
    mu_run_test(test_set);
    mu_run_test(test_get);
    mu_run_test(test_remove);
    mu_run_test(test_expand_contract);
    mu_run_test(test_push_pop);
    mu_run_test(test_destroy);
    end = clock();
    cpu_time_used = ((double) (end) - start) / CLOCKS_PER_SEC;
    printf("Tempo do DArray: %f\n", cpu_time_used);

    start = clock();
    mu_run_test(test_create_list);
    mu_run_test(test_push_pop_list);
    mu_run_test(test_destroy_list);
    
    end = clock();
    cpu_time_used =(double)(end - start) / CLOCKS_PER_SEC;
    printf("Tempo da Lista Encadeada: %f\n", cpu_time_used);

    return NULL;
}

RUN_TESTS(all_tests);