#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "../src/lexer/lexer.c"
#include <windows.h>

LARGE_INTEGER frequency, start, end;

long long charsPerSecond = 0;
long highestCharsPerSecond = 0;
long lowestCharsPerSecond = 2147483647;

void performBenchmarkEntryTest(char fileName[]) {
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    FILE* filePtr = fopen(fileName, "r");

    fseek(filePtr, 0, SEEK_END);
    int size = ftell(filePtr);
    fseek(filePtr, 0, SEEK_SET);

    char* bufferPtr = (char*) malloc(size * sizeof(char));

    fread(bufferPtr, 1, size, filePtr);

    struct LexerResult result = runLexer(bufferPtr);

    QueryPerformanceCounter(&end);

    float timeTaken = (end.QuadPart - start.QuadPart) * 1000000000.0 / frequency.QuadPart;
    long chars = 1000000000 / (timeTaken / (size + 1));

    charsPerSecond += chars;

    if(chars >= highestCharsPerSecond) {
        highestCharsPerSecond = chars;
    }
    else if(chars <= lowestCharsPerSecond) {
        lowestCharsPerSecond = chars;
    }

}

void main(int argc, char* argv[]) {
    if(argc < 3) {
        printf("Usage <executable> <file> <runs>");
        return -1;
    }

    for(int i = 0; i < atoi(argv[2]); ++i) {
        performBenchmarkEntryTest(argv[1]);
    }

    printf("\nTest Results:\n");
    printf("Total Chars: %d\n", charsPerSecond);
    printf("Highest Chars per second: %d\n", highestCharsPerSecond);
    printf("Average Chars per second: %d\n", charsPerSecond / atoi(argv[2]));
    printf("Lowest Chars per second: %d\n", lowestCharsPerSecond);
}