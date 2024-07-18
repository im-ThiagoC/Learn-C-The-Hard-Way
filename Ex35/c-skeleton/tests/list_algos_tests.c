#include "minunit.h"
#include <lcthw/list_algos.h>
#include <assert.h>
#include <string.h>
#include <time.h>

char *values[] = { "XXXX", "1234","xjvef", "abcd", "NDSS", "new1", "XXXX", "wow", "xD", "121123"};
clock_t start, end;
double cpu_time_used;

#define NUM_VALUES 10

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
            debug("%s %s %d", (char *)cur->value, (char *)cur->next->value, strcmp(cur->value, cur->next->value));
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

    /*printf("\nBUBBLE SORT:\n");
    List_print(words);*/

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
    mu_assert(is_sorted(res2), "Res should be sort if already Merge sort");

    /*printf("\nMERGE SORT:\n");
    List_print(res2);*/

    List_destroy(res2);
    List_destroy(res);

    List_destroy(words);

    return NULL;
}

char *test_bottom_up_merge_sort(){
    List *words = create_words();

    //should work on a list that need sorting
    List *res = List_bottom_up_merge_sort(words, (List_compare) strcmp);
    mu_assert(is_sorted(res), "Words are not sorted after Bottom Up Merge sort.");

    //should work on already sorted list
    List *res2 = List_bottom_up_merge_sort(res, (List_compare) strcmp); 
    mu_assert(is_sorted(res2), "Res should be sort if already Bottom Up Merge sort");

    /*printf("\nBOTTOM UP MERGE SORT\n");
    List_print(res2);*/

    List_destroy(words);

    return NULL;
}

char *test_inserted_sort(){
    List *words = create_words();

    List *res = List_inserted_sort(words, (List_compare) strcmp);
    mu_assert(is_sorted(res), "Words are not sorted after Inserted Sort.");

    //should work on already sorted list
    List *res2 = List_inserted_sort(res, (List_compare) strcmp); 
    // List_print(res2);
    mu_assert(is_sorted(res2), "Res should be sort if already Inserted Sort");

    /*printf("\nINSERTED SORT:\n");
    List_print(res2);*/

    List_destroy(res2);
    List_destroy(res);

    List_destroy(words);

    return NULL;
}



char *all_tests(){
    mu_suite_start();

    start = clock();
    mu_run_test(test_bottom_up_merge_sort);
    end = clock();
    cpu_time_used = ((double) (end) - start) / CLOCKS_PER_SEC;
    printf("Tempo do Bottom Up Merge Sort: %f\n", cpu_time_used);

    start = clock();
    mu_run_test(test_bubble_sort);
    end = clock();
    cpu_time_used = ((double) (end) - start) / CLOCKS_PER_SEC;
    printf("Tempo do Bubble Sort: %f\n", cpu_time_used);

    start = clock();
    mu_run_test(test_merge_sort);
    end = clock();
    cpu_time_used = ((double) (end) - start) / CLOCKS_PER_SEC;
    printf("Tempo do Merge Sort: %f\n", cpu_time_used);

    start = clock();
    mu_run_test(test_inserted_sort);
    end = clock();
    cpu_time_used = ((double) (end) - start) / CLOCKS_PER_SEC;
    printf("Tempo do Inserted Sort: %f\n", cpu_time_used);

    


    return NULL;
}

RUN_TESTS(all_tests);
