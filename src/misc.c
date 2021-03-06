#include "misc.h"

#include <stdio.h>
#include <time.h>

#if defined(_WIN32)
#include "win32.h"
int64_t MqttGetCurrentTime()
{
    static volatile long once = 0;
    static LARGE_INTEGER frequency;
    LARGE_INTEGER counter;
    if (InterlockedCompareExchange(&once, 1, 0) == 0)
    {
        QueryPerformanceFrequency(&frequency);
    }
    QueryPerformanceCounter(&counter);
    counter.QuadPart *= 1000;
    counter.QuadPart /= frequency.QuadPart;
    return counter.QuadPart;
}
#else
int64_t MqttGetCurrentTime()
{
    struct timespec t;

    if (clock_gettime(CLOCK_MONOTONIC, &t) == -1)
        return -1;

    return ((int64_t) t.tv_sec * 1000) + (int64_t) t.tv_nsec / 1000 / 1000;
}
#endif

/* https://gist.github.com/ccbrown/9722406 */
void DumpHex(const void* data, size_t size) {
    char ascii[17];
    size_t i, j;
    ascii[16] = '\0';
    for (i = 0; i < size; ++i) {
        printf("%02X ", ((unsigned char*)data)[i]);
        if (((unsigned char*)data)[i] >= ' ' && ((unsigned char*)data)[i] <= '~') {
            ascii[i % 16] = ((unsigned char*)data)[i];
        } else {
            ascii[i % 16] = '.';
        }
        if ((i+1) % 8 == 0 || i+1 == size) {
            printf(" ");
            if ((i+1) % 16 == 0) {
                printf("|  %s \n", ascii);
            } else if (i+1 == size) {
                ascii[(i+1) % 16] = '\0';
                if ((i+1) % 16 <= 8) {
                    printf(" ");
                }
                for (j = (i+1) % 16; j < 16; ++j) {
                    printf("   ");
                }
                printf("|  %s \n", ascii);
            }
        }
    }
}
