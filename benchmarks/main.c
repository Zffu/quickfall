/**
 * Compiling Benchmark of Quickfall.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

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

double totalTimeTaken;
double startTime;

struct CategoryStatistics {
	double max;
	double low;
	double total;
};

struct CategoryStatistics* stats;

void startTimer() {
    double time = get_time();
    if(time > 0) startTime = time;
}

void endTimer(int category) {
    double time = (get_time() - startTime);
    totalTimeTaken += time;
    stats[category].total += time;
    if(stats[category].max < time) stats[category].max = time;
    if(stats[category].low > time) stats[category].low = time;
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

    stats = malloc(sizeof(struct CategoryStatistics) * 5);

    for(int i = 0; i < 5; ++i) {
	stats[i].total = 0;
	stats[i].max = 0;
	stats[i].low = 1000000;
    }

    for(int i = 0; i < runs; ++i) {
        startTimer();
        FILE* fptr = fopen(argv[1], "r");

        fseek(fptr, 0, SEEK_END);
        int size = ftell(fptr);
        fseek(fptr, 0, SEEK_SET);

        char* buff = (char*) malloc(size + 1);
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
    printf("Total time taken: %.3f micros, Average time per run: %.3f\n micros\n\n", totalTimeTaken, totalTimeTaken / runs);
    for(int i = 0; i < 5; ++i) {
	printf("Benchmarking Results of %s:\n", categories[i]);
	printf("  Total time duration: %.2fus (%.1f percent over total running time)\n", stats[i].total, (stats[i].total / totalTimeTaken) * 100);
	printf("  Range (Fastest, Lowest): %0.fus  ... %.2fus\n\n", stats[i].low, stats[i].max);
	
    }
}
