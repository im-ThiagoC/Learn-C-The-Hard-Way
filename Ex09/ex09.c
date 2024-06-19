#include <stdio.h>

int main (int argc, char* argv[]){
    int i = 0;

    //go through each string in argv
    //why am I skipping the arg[0]?

    for(i = 1; i < argc; i++){
        printf("arg %d: %s\n", i, argv[i]);
    }

    //let's make our own array of strings
    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas"
    };

    int num_states = 4;

    for(i = 0; i < num_states; i++){
        printf("state %d: %s\n", i, states[i]);
    }

    /*Extra Credit*/
    i = 25;
    while(i >= 0){
        printf("%d ", i);
        i--;
    }

    do {
        i++;
        printf("\ntest\n");
        i--;
    } while (i > 0);
    
    int j;
    for(i = 0, j = 20; i < 10; i++, j--){
        printf("%d ", i);
        printf("%d ", j);
    }

    return 0;
}