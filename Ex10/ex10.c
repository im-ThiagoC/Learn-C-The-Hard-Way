#include <stdio.h>

int main (int argc, char* argv[]){
    if(argc != 2){
        printf("ERROR: You need one argument.\n");
        //abort the program
        return 1;
    }

    int i = 0;
    for(i = 0; argv[1][i] != '\0'; i++){
        char letter = argv[1][i];

        /*switch (letter)
        {
        case 'a':
        case 'A':
            printf("%d: 'A'\n", i);
            break;
        case 'e':
        case 'E':
            printf("%d: 'E'\n", i);
            break;
        case 'i':
        case 'I':
            printf("%d: 'I'\n", i);
            break;
        case 'o':
        case 'O':
            printf("%d: 'O'\n", i);
            break;
        case 'u':
        case 'U':
            printf("%d: 'U'\n", i);
            break;
        case 'y':
        case 'Y':
            if(i > 2){
                //it's only sometimes Y
                printf("%d: 'Y'\n", i);
            }
            break;  
        
        default:
            printf("%d: %c is not a vowel\n", i, letter);
            break;
        }

        /*Extra Credits*/
        if(letter == 'A' || letter == 'a'){
            printf("%d: 'A'\n", i);
            continue;
        } else if (letter == 'E' || letter == 'e') {
            printf("%d: 'E'\n", i);
            continue;
        } else if (letter == 'I' || letter == 'i') {
            printf("%d: 'I'\n", i);
            continue;
        } else if (letter == 'O' || letter == 'o') {
            printf("%d: 'O'\n", i);
            continue;
        } else if (letter == 'U' || letter == 'u') {
            printf("%d: 'U'\n", i);
            continue;
        } else if ((letter == 'Y' || letter == 'y') && i > 2) {
            printf("%d: 'Y'\n", i);
            continue;
        } else {
            printf("%d: %c is not a vowel\n", i, letter);
        }
    }
    return 0;
}