//Advanced Data Types and Flow Control
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <stdint.h>

int main (){
    int integer = 1;
    double doublefloat = 27.3;
    float floating = 3.33;
    char character = 'T';
    register char *string = "Thiago";
    //void something
    const enum colors{
        red, green, blue
    };

    printf("CHAR_BIT    :   %d\n", CHAR_BIT);
    printf("CHAR_MAX    :   %d\n", CHAR_MAX);
    printf("CHAR_MIN    :   %d\n", CHAR_MIN);
    printf("INT_MAX     :   %d\n", INT_MAX);
    printf("INT_MIN     :   %d\n", INT_MIN);
    printf("LONG_MAX    :   %ld\n", (long) LONG_MAX);
    printf("LONG_MIN    :   %ld\n", (long) LONG_MIN);
    printf("SCHAR_MAX   :   %d\n", SCHAR_MAX);
    printf("SCHAR_MIN   :   %d\n", SCHAR_MIN);
    printf("SHRT_MAX    :   %d\n", SHRT_MAX);
    printf("SHRT_MIN    :   %d\n", SHRT_MIN);
    printf("UCHAR_MAX   :   %d\n", UCHAR_MAX);
    printf("UINT_MAX    :   %u\n", (unsigned int) UINT_MAX);
    printf("ULONG_MAX   :   %lu\n", (unsigned long) ULONG_MAX);
    printf("USHRT_MAX   :   %d\n", (unsigned short) USHRT_MAX);
    
    //<float.h>
    printf("Storage size for float : %zu \n", sizeof(float));
    printf("FLT_MAX     :   %g\n", (float) FLT_MAX);
    printf("FLT_MIN     :   %g\n", (float) FLT_MIN);
    printf("-FLT_MAX    :   %g\n", (float) -FLT_MAX);
    printf("-FLT_MIN    :   %g\n", (float) -FLT_MIN);
    printf("DBL_MAX     :   %g\n", (double) DBL_MAX);
    printf("DBL_MIN     :   %g\n", (double) DBL_MIN);
    printf("-DBL_MAX     :  %g\n", (double) -DBL_MAX);
    printf("Precision value: %d\n", FLT_DIG );

    //<stdint.h>
    printf("int8_t: %d\n", sizeof(int8_t));
    printf("uint8_t: %d\n", sizeof(uint8_t));
    printf("int16_t: %d\n", sizeof(int16_t));
    printf("uint16_t: %d\n", sizeof(uint16_t));
    printf("int32_t: %d\n", sizeof(int32_t));
    printf("uint32_t: %d\n", sizeof(uint32_t));
    printf("int64_t: %d\n", sizeof(int64_t));
    printf("uint64_t: %d\n", sizeof(uint64_t));
    //Extra Credits
    printf("int_least16_t: %d\n", sizeof(int_least16_t));
    printf("uint_least32_t: %d\n", sizeof(uint_least32_t));
    printf("INT_LEAST8_MAX: %d\n", sizeof(INT_LEAST8_MAX));
    printf("INT_LEAST8_MIN: %d\n", sizeof(INT_LEAST8_MIN));
    printf("UINT_LEAST64_MAX: %d\n", sizeof(UINT_LEAST64_MAX));
    printf("int_fast16_t: %d\n", sizeof(int_fast16_t));
    printf("uint_fast16_t: %d\n", sizeof(uint_fast16_t));   
    printf("INT_FAST8_MAX: %d\n", sizeof(INT_FAST8_MAX));
    printf("UINT_FAST64_MAX: %d\n", sizeof(UINT_FAST64_MAX));
    printf("intptr_t: %d\n", sizeof(intptr_t));
    printf("uintptr_t: %d\n", sizeof(uintptr_t));
    printf("INTPTR_MAX: %d\n", sizeof(INTPTR_MAX));
    printf("INTPTR_MIN: %d\n", sizeof(INTPTR_MIN));
    printf("UINTPTR_MAX: %d\n", sizeof(UINTPTR_MAX));
    printf("intmax_t: %d\n", sizeof(intmax_t));
    printf("uintmax_t: %d\n", sizeof(uintmax_t));
    printf("INTMAX_MAX: %d\n", sizeof(INTMAX_MAX));
    printf("INTMAX_MIN: %d\n", sizeof(INTMAX_MIN));
    printf("UINTMAX_MAX: %d\n", sizeof(UINTMAX_MAX));
    printf("PTRDIFF_MIN: %d\n", sizeof(PTRDIFF_MIN));
    printf("PTRDIFF_MAX: %d\n", sizeof(PTRDIFF_MAX));
    printf("SIZE_MAX: %d\n", sizeof(INT_FAST8_MIN));


    return 0;
}