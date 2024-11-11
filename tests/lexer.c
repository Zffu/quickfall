/**
 * Tests the Lexer on a file.
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "../src/lexer/lexer.c"
#include <windows.h>

int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("Usage: <executable> <file> [debug]");
        return - 1;
    }

    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    FILE* filePtr = fopen(argv[1], "r");

    fseek(filePtr, 0, SEEK_END);
    int size = ftell(filePtr);
    fseek(filePtr, 0, SEEK_SET);

    char* bufferPtr = (char*) malloc(size * sizeof(char));

    fread(bufferPtr, 1, size, filePtr);

    struct LexerResult result = runLexer(bufferPtr);

    QueryPerformanceCounter(&end);

    float timeTaken = (end.QuadPart - start.QuadPart) * 1000000000.0 / frequency.QuadPart;
    int charPerSecond = 1000000000 / (timeTaken / (size + 1));

    printf("Finished lexer analysis in %.0f microseconds!\n", timeTaken / 1000);
    printf("Approximative Characters per second: %d", charPerSecond);

    free(bufferPtr);
}