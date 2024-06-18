#include <stdio.h>

int main (int argc, char* argv[]){
    int i = 0;

    if(argc == 1){
        printf("You only have one argument. You suck.\n");
    } else if (argc == 3 || argc == 5){
        printf("You have 3 or 5 arguments! The last is %s\n", argv[argc-1]);

    } else if (argc > 1 && argc < 6) {
        printf("Here's your arguments:\n"); 

        for(i = 0; i < argc; i++){
            printf("%s\n", argv[i]);
        }
    } else {
        printf("You have too many arguments... You suck.\n");
    }

    return 0;
}