/**
 * Core utilities for platforming compiling.
 */

#ifndef PLATFORMS_H
#define PLATFORMS_H

struct FunctionResult {
    char output[128];
    int mode; // 1 = _start, 0 = section.
};

#endif