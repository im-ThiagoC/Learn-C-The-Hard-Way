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
    
    if(msg[strlen(msg) - 1] != '\0')
        return 1;
    
    for(i = 0; msg[i] != '\0'; i++) {
        printf("%c", toupper(msg[i]));
    }

    printf("\n");

    return 0;
}

int lowercase(const char *msg)
{   
    int i = 0;
    if(msg[strlen(msg) - 1] != '\0')
        return 1;
    
    for(i = 0; msg[i] != '\0'; i++) {
        printf("%c", tolower(msg[i]));
    }

    printf("\n");

    return 0;
}

int fail_on_purpose(const char *msg){
    puts(msg);
    return 1;
}