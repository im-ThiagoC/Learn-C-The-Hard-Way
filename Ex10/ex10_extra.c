#include <stdio.h>

int main (int argc, char* argv[]){
    if(argc < 2){
        printf("ERROR: You need a least one argument.\n");
        //abort the program
        return 1;
    }

    int i = 0;

    for(i = 0; argv[1][i] != '\0'; i++){
        char letter = argv[1][i];

        if(i == 0 && (letter >= 'a' && letter <= 'z')){
            printf("%c", letter - 32);
        }
        else if(i != 0 && (letter >= 'A' && letter <= 'Z')){
            printf("%c", letter + 32);
        }
        else if(!((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z'))){
            printf("\n%c is not a letter", letter);
        }
        else {
            printf("%c", letter);
        }
    }
    return 0;
}