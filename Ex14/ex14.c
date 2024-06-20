#include <stdio.h>
#include <ctype.h>
/*Extra Credits*/
#include <string.h>

//foward declarations
//int can_print_it(char ch);
void print_letters(char arg[], int strlen);

void print_arguments(int argc, char* argv[]){
    int i;

    for(i = 1; i < argc; i++){
        print_letters(argv[i], strlen(argv[i]));
    }
}

void print_letters(char arg[], int strlen){
    int i;

    for(i = 0; i < strlen; i++){
        char ch = arg[i];

        //if(can_print_it(ch)) {
            printf("'%c' == %d ", ch, ch);
        //}
    }

    printf("\n");
}

/*Extra Credits*/
/*int can_print_it(char ch){
    return isalpha(ch) || isblank(ch);
}*/


int main (int argc, char* argv[]){
    print_arguments(argc, argv);

    return 0;
}

