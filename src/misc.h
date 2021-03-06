#ifndef MISC_H
#define MISC_H

#include "config.h"

#include <stdint.h>
#include <stdlib.h>

/*
    Returns the current time as milliseconds. The return value can only be
    compared to another return value of the function.
*/
int64_t MqttGetCurrentTime();

/*
    Simple hexdump to stdout.
*/
void DumpHex(const void* data, size_t size);

#endif
