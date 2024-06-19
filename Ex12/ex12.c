#include <stdio.h>

int main (int argc, char* argv[]){
    int areas[] = { 100, '.', 130, 140, 200 };
    char name[] = "Thiago";
    char fullName[] = {
        'T', 'h', 'i', 'a', 'g', 'o',
        ' ', 'M', '.', ' ',
        'C', 'a', 'r', 'v', 'a', 'l', 'h', 'o', '\0'
    };

    //WARNING: On some systems you may have to change the
    //%ld in this code to a %u since it will use unsigned ints 
    printf("The size of an int: %u\n", sizeof(int));

    printf("The size of areas (int[]): %u\n", sizeof(areas));
    printf("The number of ints in areas: %u\n",
        sizeof(areas) / sizeof(int));
    printf("The first area is %d, the 2nd %d.\n", areas[0], areas[1]);

    printf("The size of a char: %u\n", sizeof(char));

    printf("The size of name (char[]): %u\n", sizeof(name));
    printf("The number of chars: %u\n",
        sizeof(name) / sizeof(char));

    printf("The size of fullName (char[]): %u\n", sizeof(fullName));
    printf("The number of chars: %u\n",
        sizeof(fullName) / sizeof(char));
    printf("name = \"%s\"  and fullName = \"%s\" \n", name, fullName);


    return 0;
}