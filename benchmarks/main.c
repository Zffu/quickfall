/**
 * Compiling Benchmark of Quickfall.
 */

#include <stdio.h>
#include <stdlib.h>

void main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("Usage: <executable> <file> [runs, default = 100]");
        return;
    }

    FILE* fptr = fopen(argv[1], "r");

    fseek(fptr, 0, SEEK_END);
    int size = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    char* buff = (char*) malloc(size);
    fread(buff, 1, size, fptr);
    
}