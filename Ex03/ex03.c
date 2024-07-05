#include <stdio.h>

int main (){
    int age = 10;
    int other = 30;
    int height = age = other = 20;

    printf("I am %d years old. \n", age);
    printf("I am %d inches tall.\n", height);
    printf("I am %d inches tall.\n", other);

    return 0;
}