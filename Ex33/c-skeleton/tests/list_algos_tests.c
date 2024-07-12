#include "minunit.h"
#include <lcthw/list_algos.h>
#include <assert.h>
#include <string.h>
#include <time.h>

char *values[] = { "XXXX", "1234", "abcd", "xjvef", "NDSS"};
clock_t start, end;
double cpu_time_used;

#define NUM_VALUES 5

List *create_words(){
    int i = 0;
    List *words = List_create();

    for(i = 0; i < NUM_VALUES; i++){
        List_push(words, values[i]);
    }

    return words;
}

int is_sorted(List *words){
    /*printf("PRINTANDO LISTA:\n");
    List_print(words);*/
    LIST_FOREACH(words, first, next, cur){
        if(cur->next && strcmp(cur->value, cur->next->value) > 0) {
            debug("%s %s", (char *)cur->value, (char *)cur->next->value);
            return 0;
        }
    }
    return 1;
}

char *test_bubble_sort(){
    List *words = create_words();


    //should work on a list that need sorting
    int rc = List_bubble_sort(words, (List_compare) strcmp);
    mu_assert(rc == 0, "Bubble sort failed");
    mu_assert(is_sorted(words), "Words are not sorted after bubble sort.");

    //should work on already sorted list
    rc = List_bubble_sort(words, (List_compare) strcmp);
    mu_assert(rc == 0, "Bubble sort of already sorted failed.");
    mu_assert(is_sorted(words), "Words should be sort if already bubble sort");

    List_destroy(words);

    return NULL;
}

char *test_merge_sort(){
    List *words = create_words();


    //should work on a list that need sorting
    List *res = List_merge_sort(words, (List_compare) strcmp);
    mu_assert(is_sorted(res), "Words are not sorted after Merge sort.");

    //should work on already sorted list
    List *res2 = List_merge_sort(res, (List_compare) strcmp); 
    mu_assert(is_sorted(res), "Res should be sort if already Merge sort");

    List_destroy(res2);
    List_destroy(res);

    List_destroy(words);

    return NULL;
}



char *all_tests(){
    mu_suite_start();

    start = clock();
    mu_run_test(test_bubble_sort);
    end = clock();
    cpu_time_used = ((double) (end));
    printf("%f\n", cpu_time_used);

    start = clock();
    mu_run_test(test_merge_sort);
    end = clock();
    cpu_time_used = ((double) (end));

    printf("%f\n", cpu_time_used);

    return NULL;
}

RUN_TESTS(all_tests);
