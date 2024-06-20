#include <stdio.h>

int arrays (){
    //first, arrays
    int ages[] = {23, 43, 12, 89, 2};
    char names[5][7] = {
        'T', 'h', 'i', 'a', 'g', 'o', '\0',
        'M', 'a', 'r', 'i', 'a', '\0', '\0',
        'T', 'h', 'i', 'a', 'g', 'o', '\0',
        'T', 'h', 'i', 'a', 'g', 'o', '\0',
        'T', 'h', 'i', 'a', 'g', 'o', '\0'
    };

    //safety get the size of ages
    int count = sizeof(ages) / sizeof(int);
    int i;

    for(i = 0; i < count; i++){
        printf("%s has %d years alive.\n", names[i], ages[i]);
    }

    return 0;
}

int pointers(){
    int ages[] = {23, 43, 12, 89, 2};
    int *age_pointer = &ages[0];
    char *names[] = {
        "Alan", "Turing",
        "Marry", "John", "Lisa"
    };
    char **name_pointer = &names[0];
    

    int i = 0;
    int count = sizeof(ages) / sizeof(int);

    for(i = 0; i < count; i++){
        printf("%s has %d years alive.\n", name_pointer[i], age_pointer[i]);
        printf("The address of name is %p and for the age is %p\n", &name_pointer[i], &age_pointer[i]);
    }

    

    return 0;
}

int main (){
    pointers();

    return 0;
}