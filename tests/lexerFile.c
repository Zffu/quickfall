/**
 * Tests the Lexer on a file.
 */

#include <time.h>
#include <stdio.h>
#include "../src/lexer/lexer.c"

int main(int argc, char* argv[]) {
    if(argc < 3) {
        printf("Usage: <executable> <file> <buffSize>");
        return - 1;
    }

    clock_t ts = clock();

    char line[1024];

    FILE* filePtr = fopen(argv[1], "r");

    printf("\nToken Analysis Test (Per Line):\n\n");

    while(fgets(line, 1024, filePtr) != NULL) {
        struct LexerResult result = runLexer(line);

        printf("\nFound %d tokens:\n", result.size);        
        for(int i = 0; i < result.size; ++i) {
            printf("Token -> type: %d, raw value: %s\n", result.tokens[i].type, result.tokens[i].value);
        }
    }

    ts = clock() - ts;
    printf("Finished lexer analysis in %dms!", ts);
}