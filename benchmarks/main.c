/**
 * Compiling Benchmark of Quickfall.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

LARGE_INTEGER frequency, start, end;
long totalTime;

long timeTaken[5];
char* categories[] = {"File IO (Read)", "Lexer", "Parser (AST)", "Compiling", "File IO (Write)"};


void main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("Usage: <executable> <file> [runs, default = 100]");
        return;
    }

    int runs = 100;

    if(argc > 2) {
        runs = atoi(argv[2]);
    }

    FILE* fptr = fopen(argv[1], "r");

    fseek(fptr, 0, SEEK_END);
    int size = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    char* buff = (char*) malloc(size);
    fread(buff, 1, size, fptr);
    fclose(fptr);

    for(int i = 0; i < runs; ++i) {

    }

}