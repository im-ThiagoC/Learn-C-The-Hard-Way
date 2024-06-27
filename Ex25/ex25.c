#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "dbg.h"

#define MAX_DATA 100

/*Extra Credits*/
//Função para imprimir uma string
int print_string(char **out_string){
    int rc = 0;
    rc = fputs(*out_string, stdout);
    check(rc == 0, "Failed to print string");

    return 0;
    error:
        return 1;
}

// Função para imprimir um caractere
int print_char(char c) {
    int rc = 0;
    rc = putchar(c);
    check(rc == 0, "Failed to print a char");

    return 0;
    error:
        return 1;
}

// Função para converter e imprimir um número inteiro
int print_int(int *num) {
    // Verifica se o número é negativo
    if (*num < 0) {
        print_char('-');
        *num = -*num;
    }

    // Calcula o número de dígitos no número
    int divisor = 1;
    while (*num / divisor >= 10) {
        divisor *= 10;
    }

    // Imprime cada dígito do número
    while (divisor > 0) {
        int digit = *num / divisor;
        //Imprimo primeiro a maior casa, Ex: 987 -> 9 -> 98 -> 987
        print_char(digit + '0');
        *num %= divisor;
        divisor /= 10;
    }

    return 0;
}

int new_printf(const char *fmt, ...){
    int i = 0;
    int rc = 0;

    int *out_int = NULL;
    char *out_char = NULL;
    char **out_string = NULL;

    va_list argp;
    va_start(argp, fmt);

    for(i = 0; fmt[i] != '\0'; i++){
        if(fmt[i] == '%'){
            i++;
            switch (fmt[i])
            {
            case '\0':
                sentinel("Invalid format, you ended with %%.");
                break;
                
            case 'd':
                out_int = va_arg(argp, int *);
                rc = print_int(out_int);
                check(rc == 0, "Failed to print int");
                break;
            
            case 'c':
                out_char = va_arg(argp, char *);
                *out_char = fputc(*out_char, stdout);
                break;
            
            case 's':
                out_string = va_arg(argp, char **);
                rc = print_string(out_string);
                check(rc == 0, "Failed to print string");
                break;
                
            /*case 'f':
                out_float = va_arg(argp, float*);
                rc = read_float(out_float);
                check(rc == 0, "Failed to read float");
                break;*/
                
            
            default:
                sentinel("Invalid format.");
                break;
                
            }
        } else {
            fputc(fmt[i], stdout);
        }
    }
    va_end(argp);
    return 0;

    error:
        va_end(argp);
        return 1;
}

int read_string(char **out_string, int max_buffer){
    *out_string = calloc(1, max_buffer + 1);
    check_mem(*out_string);

    char *result = fgets(*out_string, max_buffer, stdin);
    check(result != NULL, "Input error on result");

    return 0;

    error:
        if(*out_string) free(*out_string);
        *out_string = NULL;
        return -1;
}

int read_int(int *out_int){
    char *input = NULL;

    int rc = read_string(&input, MAX_DATA);
    check(rc == 0, "Failed to read number");

    *out_int = atoi(input);

    free(input);
    return 0;

    error:
        if(input) free(input);
        return -1;
}

int read_scan(const char *fmt, ...){
    int i = 0;
    int rc = 0;
    int *out_int = NULL;
    char *out_char = NULL;
    char **out_string = NULL;
    int max_buffer = 0;

    va_list argp;
    va_start(argp, fmt);

    for(i = 0; fmt[i] != '\0'; i++){
        if(fmt[i] == '%'){
            i++;
            switch (fmt[i])
            {
            case '\0':
                sentinel("Invalid format, you ended with %%.");
                break;
                
            case 'd':
                out_int = va_arg(argp, int *);
                rc = read_int(out_int);
                check(rc == 0, "Failed to read int");
                break;
            
            case 'c':
                out_char = va_arg(argp, char *);
                *out_char = fgetc(stdin);
                break;
            
            case 's':
                max_buffer = va_arg(argp, int);
                out_string = va_arg(argp, char **);
                rc = read_string(out_string, max_buffer);
                check(rc == 0, "Failed to read string");
                break;
                
            /*case 'f':
                out_float = va_arg(argp, float*);
                rc = read_float(out_float);
                check(rc == 0, "Failed to read float");
                break;*/
                
            
            default:
                sentinel("Invalid format.");
                break;
                
            }
        } else {
            fgetc(stdin);
        }

        check(!feof(stdin) && !ferror(stdin), "Input error!");
    }

    va_end(argp);
    return 0;

    error:
        va_end(argp);
        return -1;
}

int main(){
    char *first_name = NULL;
    char initial = ' ';
    char *last_name = NULL;
    int age = 0;

    printf("What's your first name? ");
    int rc = read_scan("%s", MAX_DATA, &first_name);
    check(rc == 0, "Failed to read first name.");

    printf("What's is your initial? ");
    rc = read_scan("%c\n", &initial);
    check(rc == 0, "Failed to read initial.");

    printf("What's your last name? ");
    rc = read_scan("%s", MAX_DATA, &last_name);
    check(rc == 0, "Failed to read last name.");

    printf("How old are you? ");
    rc = read_scan("%d", &age);
    check(rc == 0, "Failed to read age");

    printf("----- RESULTS -----\n");

    //printf("First Name: %s", first_name);
    new_printf("First Name: %s", &first_name);
    new_printf("Initial: '%c'\n", &initial);
    new_printf("Last Name: %s", &last_name);
    new_printf("Age: %d\n", &age);

    free(first_name);
    free(last_name);
    return 0;

    error:
        return -1;
}