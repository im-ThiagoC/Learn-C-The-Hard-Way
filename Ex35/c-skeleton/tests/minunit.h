#undef NDEBUG
#ifndef _minunit_h
#define _minunit_h

#include <stdio.h>
#include <stdlib.h>
#include <lcthw/dbg.h>

#define ANSI_COLOR_BLUE "\033[1;34m"
#define ANSI_COLOR_GREEN "\033[32m"
#define ANSI_COLOR_RED "\033[31m"
#define ANSI_COLOR_GREY "\033[90m"
#define ANSI_COLOR_RESET "\033[0;0m"


#define mu_suite_start() char *message = NULL

#define mu_assert(test, message) if (!(test)) {\
    log_err(message); \
    return message;   \
}\

#define mu_run_test(test) debug("\n-----%s", " " #test); \
    message = test(); tests_run++; if (message) return message;

#define RUN_TESTS(name) int main(int argc, char *argv[]) {\
    argc = 1; \
    debug(ANSI_COLOR_BLUE"----- RUNNING: %s"ANSI_COLOR_RESET, argv[0]);\
    printf(ANSI_COLOR_GREY"----\n" ANSI_COLOR_BLUE "RUNNING: %s\n"ANSI_COLOR_RESET, argv[0]);\
    char *result = name();\
    if (result != 0) {\
        printf(ANSI_COLOR_RED "FAILED: %s\n" ANSI_COLOR_RESET, result);\
    }\
    else {\
        printf(ANSI_COLOR_GREEN "ALL TESTS PASSED\n" ANSI_COLOR_RESET);\
    }\
    printf("Tests run: %d\n", tests_run);\
    exit(result != 0);\
}

int tests_run;

#endif