#include <stdio.h>
#include <string.h>
#include <windows.h>

#define SIZE 1000000

void measure_time(void (*func)(char *, char *, size_t), char *dest, char *src, size_t size, const char *func_name) {
    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    
    func(dest, src, size);
    
    QueryPerformanceCounter(&end);
    double time_taken = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("%s: %f seconds\n", func_name, time_taken);
}

void memcpy_wrapper(char *dest, char *src, size_t size) {
    memcpy(dest, src, size);
}

void memmove_wrapper(char *dest, char *src, size_t size) {
    memmove(dest, src, size);
}

void memset_wrapper(char *dest, char *src, size_t size) {
    memset(dest, *src, size);
}

int main() {
    char src[SIZE], dest[SIZE];
    
    // Inicializando src com dados
    memset(src, 'A', SIZE);

    // Medindo tempo do memcpy
    measure_time(memcpy_wrapper, dest, src, SIZE, "memcpy");

    // Medindo tempo do memmove
    measure_time(memmove_wrapper, dest, src, SIZE, "memmove");

    // Medindo tempo do memset
    measure_time(memset_wrapper, dest, src, SIZE, "memset");

    return 0;
}
