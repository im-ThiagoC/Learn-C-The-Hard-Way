/*Based on code by Andre Reinald then heavily modified by Zed A. Shaw*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <lcthw/radixmap.h>
#include <lcthw/dbg.h>

RadixMap *RadixMap_create(size_t max){

    RadixMap *map = calloc(sizeof(RadixMap), 1);
    check_mem(map);

    map->contents = calloc(sizeof(RMElement), max + 1);
    check_mem(map->contents); 

    map->temp = calloc(sizeof(RMElement), max + 1);
    check_mem(map->temp);

    map->max = max;
    map->end = 0;

    return map;
    error:
        return NULL;
}

void RadixMap_destroy(RadixMap *map){
    if(map){
        free(map->contents);
        free(map->temp);
        free(map);
    }
}

#define ByteOf(x, y) (((uint8_t *)x) [(y)])

static inline void radix_sort(short offset, uint64_t max, uint64_t *source, uint64_t *dest){
    uint64_t count[256] = { 0 };
    uint64_t *cp = NULL;
    uint64_t *sp = NULL;
    uint64_t *end = NULL;
    uint64_t s= 0;
    uint64_t c= 0;

    //count occorences of every byte value
}