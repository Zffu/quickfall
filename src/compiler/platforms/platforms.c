/**
 * Core utilities for platforming compiling.
 */

struct FunctionResult {
    char output[128];
    int mode; // 1 = _start, 0 = section.
};