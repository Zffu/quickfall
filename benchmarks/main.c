/**
 * Compiling Benchmark of Quickfall.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#include "../src/lexer/lexer.h"
#include "../src/parser/parser.h"
#include "../src/parser/ast.h"
#include "../src/compiler/compiler.h"

//
//
// Timing Utilities
//
//

float totalTimeTaken;
float* timeTaken;

LARGE_INTEGER frequency, start, end;

int categoriesSize;
char** categories;

/**
 * Sets the categories for the Quickfall Benchmarking Context.
 */
void setCategories(int amount, char* categories[]) {
    categories = categories;
    timeTaken = malloc(amount * sizeof(float));
    categoriesSize = amount;
}

/**
 * Starts the monitoring
 */
void startMonitoring() {
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
}

/**
 * Stops monitoring the current benchmark context.
 */
void stopMonitoring(int category) {
    QueryPerformanceCounter(&end);
    float taken = (end.QuadPart - start.QuadPart) * 1000000.0 / frequency.QuadPart;

    totalTimeTaken += taken;
    timeTaken[category] += taken;
}


void main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("Usage: <executable> <file> [runs, default = 100]");
        return;
    }

    int runs = 100;

    if(argc > 2) {
        runs = atoi(argv[2]);
    }

    char* categories[] = {"File IO (Open)", "Lexer", "Parser", "Compiler", "File IO (Close)"};
    setCategories(5, categories);

    for(int i = 0; i < runs; ++i) {
        startMonitoring();
        FILE* fptr = fopen(argv[1], "r");

        fseek(fptr, 0, SEEK_END);
        int size = ftell(fptr);
        fseek(fptr, 0, SEEK_SET);

        char* buff = (char*) malloc(size);
        fread(buff, 1, size, fptr);
        fclose(fptr);

        stopMonitoring(0);
        startMonitoring();

        struct LexerResult result = runLexer(buff);

        stopMonitoring(1);

        startMonitoring();

        struct ASTNode* node = runParser(result);

        stopMonitoring(2);
        startMonitoring();

        struct CompilerOutput compiled = compile(node, "win");

        stopMonitoring(3);

        char* output = argv[2];
        strcat(output, ".build");

        startMonitoring();

        fptr = fopen(output, "w");
        fprintf(fptr, compiled.output);

        stopMonitoring(4);
    }

    printf("========= Benchmarking Results =========\n");
    
    for(int i = 0; i < 5; ++i) {
        float taken = timeTaken[i] / runs;
        printf("%s: %fμs (%d%)\n", categories[i], taken, ((totalTimeTaken / runs) / taken) * 100);
    }
}