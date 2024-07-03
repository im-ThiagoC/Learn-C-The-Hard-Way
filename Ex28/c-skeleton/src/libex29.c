#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "dbg.h"


int print_a_message(const char *msg)
{
    printf("A STRING: %s\n", msg);

    return 0;
}


int uppercase(const char *msg)
{
    int i = 0;

    check(strlen(msg) - 1 == '\0', "No terminated string");
    for(i = 0; msg[i] != '\0'; i++) {
        printf("%c", toupper(msg[i]));
    }

    printf("\n");

    return 0;
    error:
        return 1;
}

int lowercase(const char *msg)
{   
    int i = 0;
    check(strlen(msg) - 1 == '\0', "No terminated string")
    
    for(i = 0; msg[i] != '\0'; i++) {
        printf("%c", tolower(msg[i]));
    }

    printf("\n");

    return 0;
    error:
        return 1;
}