#include <stdio.h>

int main (int argc, char* argv[]){
    int numbers[4] = { 0 };
    char name[7] = { 'a' };

    /*Extra Credit*/
    int hack[8] = {1, 2, 3, 4, 97, 98, 99, 100};
    printf("%d %d %d %d\n%c %c %c %c\n", 
        hack[0], hack[1], hack[2], hack[3],
        hack[4], hack[5], hack[6], hack[7]);

    //first, print them out raw
    printf("numbers: %d %d %d %d\n",
        numbers[0], numbers[1], numbers[2], numbers[3]);

    printf("name each: %c %c %c %c %c %c\n",
        name[0], name[1], name[2], name[3], name[4], name[5]);

    printf("name: %s\n", name);

    //set up the numbers
    numbers[0] = 1;
    numbers[1] = 2;
    numbers[2] = 3;
    numbers[3] = 4;

    /*Extra Credit*/
    numbers[0] = 'a';
    numbers[1] = 'b';
    numbers[2] = 'c';
    

    //set up the name
    name[0] = 't';
    name[1] = 'h';
    name[2] = 'i';
    name[3] = 'a';
    name[4] = 'g';
    name[5] = 'o';
    name[6] = '\0';

    /*Extra Credit*/
    name[0] = 3;
    name[1] = 4;
    name[2] = 5;
    name[3] = 6;

    //them print them out initialized
    printf("numbers: %d %d %d %d\n",
        numbers[0], numbers[1], numbers[2], numbers[3]);
    
    printf("name each: %c %c %c %c %c %c\n",
        name[0], name[1], name[2], name[3], name[4], name[5]);
    
    //print the name like a string
    printf("name: %s\n", name);

    //another way to use name
    char* another = "Thiago";
    printf("another: %s\n", another);

    printf("another each: %c %c %c %c %c %c",
        another[0], another[1], another[2], another[3], another[4], another[5]);
        
    return 0;
}