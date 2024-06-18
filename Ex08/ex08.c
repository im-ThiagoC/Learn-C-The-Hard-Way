#include <stdio.h>

int main (int argc, char* argv[]){
    int i;
    int temp = argc - 1;
    if (!temp) {
        printf("You have no arguments...");

    }   else if (temp == 3 || temp == 5){
            printf("You have 3 or 5 arguments! The last is %s\n", argv[temp]);

    } else if (temp >= 1 && temp < 6) {
        printf("Here's your arguments:\n"); 

        for(i = 1; i <= temp; i++){
            printf("%d - %s\n", i, argv[i]);
        }
    } else {
        printf("You have too many arguments... You suck.\n");
    }

    return 0;
}