#include <stdio.h>

int main (int argc, char* argv[]){
    int i;

    //go through each string in argv
    //why I skipping the argv[0]?

    /*Extra Credits*/
    
    int num_states = 4;
    char* states[] = {
        "California", NULL,
        "Washington", "Texas", ""
    };

    argv[argc] = states[0];

    for(i = 1; i < argc; i++, num_states++){
        printf("arg %d: %s\n", i, argv[i]);
        states[num_states] = argv[i];
    }

    //let's make our own array strings
    

    

    int j;
    for(i = 0, j = num_states-1; i < num_states; i++, j--){
        printf("state %d: %s\n", i, states[i]);
        printf("%d\n", j);
    }

    return 0;
}