/**
 * Tests the Lexer on a file.
 */

#include <time.h>
#include <stdio.h>
#include "../src/lexer/lexer.c"

int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("Usage: <executable> <file> [debug]");
        return - 1;
    }

    clock_t ts = clock();

    char line[128];

    FILE* filePtr = fopen(argv[1], "r");

    if(argc > 2) {
        printf("\nToken Analysis Test (Debugging Mode):\n\n");

        while(fgets(line, 128, filePtr) != NULL) {
            struct LexerResult result = runLexer(line);

            printf("\nFound %d tokens:\n", result.size);        
            for(int i = 0; i < result.size; ++i) {
                printf("Token -> type: %d, raw value: %s\n", result.tokens[i].type, result.tokens[i].value);
            }
        }
    }
    else {
        printf("\nToken Analysis Test:\n\n");

        int count = 0;

        while(fgets(line, 128, filePtr) != NULL) {
            struct LexerResult result = runLexer(line);
            count += result.size;
        }

        printf("Found %d tokens in file!\n", count);
    }

    ts = clock() - ts;
    printf("Finished lexer analysis in %dms!", ts);
}