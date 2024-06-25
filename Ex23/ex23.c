#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "dbg.h"

int normal_copy(char *from, char *to, int count){
    int i = 0;

    for(i = 0; i < count; i++){
        to[i] = from [i];
    }

    return i;
}

int duffs_device(char *from, char *to, int count){
    int n = (count + 7) / 8;
    
    switch (count % 8) {    
        case 0:
            do {
                *to++ = *from++;
                case 7:
                *to++ = *from++;
                case 6:
                *to++ = *from++;
                case 5:
                *to++ = *from++;
                case 4:
                *to++ = *from++;
                case 3:
                *to++ = *from++;
                case 2:
                *to++ = *from++;
                case 1:
                *to++ = *from++;
            } while (--n > 0);
    }

    return count;
}

int zeds_device(char *from, char *to, int count){
    int n = (count  + 7) / 8;

    switch (count % 8)
    {       
        case 0:
    again:  *to++ = *from++;
        
        case 7:
            *to++ = *from++;
        case 6:
            *to++ = *from++;
        case 5:
            *to++ = *from++;
        case 4:
            *to++ = *from++;
        case 3:
            *to++ = *from++;
        case 2:
            *to++ = *from++;
        case 1:
            *to++ = *from++;
        if(--n > 0){
            goto again;
        }
    }
    return count;
}

int valid_copy(char *data, int count, char expects){
    int i = 0;
    for(i = 0; i < count; i++){
        if(data[i] != expects){
            log_err("[%d] %c != %c", i, data[i], expects);
            return 0;
        }
    }
    return 1;
}

int main(){
    double        pcFreq;        // Counter frequency (timer resolution)
    __int64       counterStart;  // Timer value
    LARGE_INTEGER li;            // Large interger for timer value
    double        elapsed;       // Elapsed time in seconds
    int           retcode;       // Return cod
    
    // Output a banner
    printf("-------------------------------------------- timeitWin.c -----\n");

    // Get frequency of counter
    retcode = QueryPerformanceFrequency(&li);
    if (retcode == 0)
        printf("*** ERROR - QueryPerformanceFrequency() failed \n");
    pcFreq = li.QuadPart;

    // Start timing (read current counter value)
    QueryPerformanceCounter(&li);
    counterStart = li.QuadPart;

    char from[1000] = { 'a' };
    char to[1000] = { 'c' };
    int rc = 0;

    //set up the from to have some stuff
    memset(from, 'x', 1000);
    //set it to a failure mode
    memset(to, 'y', 1000);
    check(valid_copy(to, 1000, 'y'), "Not initialized right...");

    //use normal copy to
    printf("Normal Copy\n");
    rc = normal_copy(from, to, 1000);
    check(rc == 1000, "Normal copy failed: %d", rc);
    check(valid_copy(to, 1000, 'x'), "Normal copy failed.");
    
    //reset
    memset(to, 'y', 1000);

    //duffs version
    printf("Duff's device copy\n");
    rc = duffs_device(from, to, 1000);
    check(rc = 1000, "Duff's device failed copy");
    check(valid_copy(to, 1000, 'x'), "Duff's device failed copy.");
    
    //reset
    memset(to, 'y', 1000);

    //zedd version
    printf("Zed's device copy\n");
    rc = zeds_device(from, to, 1000);
    check(rc = 1000, "Zed's device failed copy");
    check(valid_copy(to, 1000, 'x'), "Zed's device failed copy.");

    // Stop timing (read current counter value) and determine elapsed time
    QueryPerformanceCounter(&li);
    elapsed = 1000.0 * ((li.QuadPart - counterStart) / pcFreq);

    // Output name and elapsed time
    printf("Its took %f millisec to execute \n", elapsed);
    printf("---------------------------------------------------------------\n");

    return 0;
error:
    return 1;
}
