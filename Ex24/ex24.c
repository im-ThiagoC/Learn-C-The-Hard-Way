#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"

#define MAX_DATA 100

typedef enum EyeColor{
    BLUE_EYES, GREEN_EYES, BROWN_EYES,
    BLACK_EYES, OTHER_EYES
} EyeColor;

const char *EYE_COLOR_NAMES[] = {
    "Blue", "Green", "Brown", "Black", "Other"
};

typedef struct Person {
    int age;
    char first_name[MAX_DATA];
    char last_name[MAX_DATA];
    EyeColor eyes;
    float income;
} Person;

void removeSpaces(char *string){
    char *temp = string;

    while (*temp != '\0'){
        if(*temp != ' '){
            *string = *temp;
            string++;
        }

        temp++;
    }

    *string = '\0';
    free(temp);
}

void getNameCharByChar(char *string){
    char c = 'a';
    int i = 0;

    while(c != '\n'){
        scanf("%c", &c);
        string[i] = c;
        i++;

        if(i > MAX_DATA){
            break;
        }
    }
    string[i] = '\0';

}

int main (){
    Person you = {.age = 0};
    int i = 0;
    char *in = NULL;

    printf("What's your first name? ");
    //scanf("%s", you.first_name);
    //in = fgets(you.first_name, MAX_DATA, stdin);
    getNameCharByChar(you.first_name);
    in = you.first_name;
    check(in != NULL, "Failed to read first name...");
    removeSpaces(you.first_name);

    printf("What's your last name? ");
    //scanf("%99[a-zA-Z ]", you.last_name);
    //getchar();
    fgets(you.last_name, MAX_DATA, stdin);
    check(in != NULL, "Failed to read last name");
    removeSpaces(you.last_name);

    printf("How old are you? ");
    char temp[MAX_DATA];
    //fgets(temp, MAX_DATA - 1, stdin);
    scanf("%s", temp);
    getchar();
    you.age = atoi(temp);
    log_info("%d", you.age);
    check(you.age > 0, "You have to enter a number in your age.");

    printf("What color are your eyes:\n");
    for(i = 0; i < OTHER_EYES; i++){
        printf("%d) %s\n", i + 1, EYE_COLOR_NAMES[i]);
    }
    printf("> ");

    int eyes = -1;
    fgets(temp, MAX_DATA - 1, stdin);
    eyes = atoi(temp);
    you.eyes = eyes - 1;
    check(eyes > 0, "You have to enter a number of these options.");
    check(you.eyes <= OTHER_EYES && you.eyes >= 0, "Do it right, that's not an option.");


    printf("How much do you make an hour? ");
    fgets(temp, MAX_DATA - 1, stdin);
    you.income = atof(temp);
    check(you.income > 0, "Enter a floating point number.");

    printf("----- RESULTS -----\n");

    printf("First Name: %s", you.first_name);
    printf("Last Name: %s", you.last_name);
    printf("Age: %d\n", you.age);
    printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
    printf("Income: %f\n", you.income);

    return 0;
    error:
    return -1;
}
