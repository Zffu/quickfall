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
// Timing Utilities
//
#ifdef WIN32

#include <windows.h>
double get_time()
{
    LARGE_INTEGER t, f;
    QueryPerformanceCounter(&t);
    QueryPerformanceFrequency(&f);
    return ((double)t.QuadPart/(double)f.QuadPart) * 1000000;
}

#else

#include <sys/time.h>
#include <sys/resource.h>

double get_time()
{
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec*1e-6;
}

#endif

char** categories;

double* timeTaken;

double startTime;

double totalTimeTaken;

void startTimer() {
    double time = get_time();
    if(time > 0) startTime = time;
}

void endTimer(int category) {
    double time = (get_time() - startTime);
    if(time > 0) {
	totalTimeTaken += time;
	timeTaken[category] += time;
    }
}

/**
 * Starts the monitoring
 */

void main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("Usage: <executable> <file> [runs, default = 100]");
        return;
    }

    int runs = 100;

    if(argc > 2) {
        runs = atoi(argv[2]);
    }

    char* c[5] = {"File IO (Open)", "Lexer", "Parser", "Compiler", "File IO (Close)"};
    categories = c;

    timeTaken = malloc(sizeof(long) * 5);

    for(int i = 0; i < runs; ++i) {
        startTimer();
        FILE* fptr = fopen(argv[1], "r");

        fseek(fptr, 0, SEEK_END);
        int size = ftell(fptr);
        fseek(fptr, 0, SEEK_SET);

        char* buff = (char*) malloc(size);
        fread(buff, 1, size, fptr);
	buff[size] = '\0';
        fclose(fptr);

        endTimer(0);
        startTimer();

        struct LexerResult result = runLexer(buff);

        endTimer(1);

        startTimer();

        struct ASTNode* node = runParser(result);
	
        endTimer(2);
        startTimer();

        char* compiled = compile(node, "win");

        endTimer(3);
		
        startTimer();
	
        fptr = fopen("output.txt", "w");
	fprintf(fptr, compiled);

        endTimer(4);
    }

    printf("========= Benchmarking Results =========\n");
    printf("Total time taken: %f, Average time per run: %f\n", totalTimeTaken, totalTimeTaken / runs);
    for(int i = 0; i < 5; ++i) {
        if(timeTaken[i] > 0) {
		printf("%s: total: %f microseconds, avg: %f microseconds (%f percent of overall)\n", categories[i], timeTaken[i], timeTaken[i] / runs, (timeTaken[i] / totalTimeTaken) * 100);
	}
	else {
		printf("Category %s didn't show in the benchmarking, results are possibly impacted!\n", categories[i]);
	}
    }
}
