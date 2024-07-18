#include "minunit.h"
#include <lcthw/darray_algos.h>
#include <time.h>

int testcmp(char *a, char *b){
    return strcmp(a, b);
}

DArray *create_words(){
    DArray *result = DArray_create(0, 5);
    char *words[] = {"Thiago", "abcabc", "a", "Z", "1234"};
    int i = 0;

    for(i = 0; i < 5; i++){
        DArray_push(result, words[i]);
    }

    return result;
}

int is_sorted(DArray *array){
    int i = 0;

    for(i = 0; i < DArray_count(array) - 1; i++){
        if(strcmp(DArray_get(array, i), DArray_get(array, i + 1)) > 0){
            return 0;
        }
    }
    
    return 1;
}

char *run_sort_test(int (*func) (DArray *, DArray_compare), const char *name){
    DArray *words = create_words();
    mu_assert(!is_sorted(words), "Words should start not sorted.");

    debug("---Testing %s sorting algorithm", name);
    int rc = func(words, (DArray_compare) testcmp);

    DArray_print(words);

    mu_assert(rc == 0, "Sort failed");
    mu_assert(is_sorted(words), "Didn't sort it");

    DArray_destroy(words);
    return NULL;
}

char *test_qsort(){
    return run_sort_test(DArray_qsort, "qsort");
}

char *test_heapsort(){
    return run_sort_test(DArray_heapsort, "heapsort");
}

char *test_merge_sort(){
    return run_sort_test(DArray_mergesort, "mergesort");
}

clock_t start, end;
double cpu_time_used;


char *all_tests(){
    
    mu_suite_start();

    start = clock();
    mu_run_test(test_qsort);
    end = clock();
    cpu_time_used = ((double) (end) - start) / CLOCKS_PER_SEC;
    printf(ANSI_COLOR_GREEN"Tempo do Quick Sort no DArray: %f\n\n"ANSI_COLOR_RESET, cpu_time_used);

    start = clock();
    mu_run_test(test_heapsort);
    end = clock();
    cpu_time_used = ((double) (end) - start) / CLOCKS_PER_SEC;
    printf(ANSI_COLOR_GREEN"Tempo do Heap Sort no DArray: %f\n\n"ANSI_COLOR_RESET, cpu_time_used);

    start = clock();
    mu_run_test(test_merge_sort);
    end = clock();
    cpu_time_used = ((double) (end) - start) / CLOCKS_PER_SEC;
    printf(ANSI_COLOR_GREEN"Tempo do Merge Sort no DArray: %f\n\n"ANSI_COLOR_RESET, cpu_time_used);

    return NULL;
}

RUN_TESTS(all_tests);