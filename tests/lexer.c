#include "../src/lexer/lexer.c"
#include <stdio.h>
#include <time.h>

int main() {
    clock_t ts = clock();
    struct LexerResult result = runLexer("var function function");
    ts = clock() - ts;

    printf("\n\nLexer took %fs\n", ts / CLOCKS_PER_SEC);

    for(int i = 0; i < result.size + 1; ++i) {
        printf("Token: t:%d raw:%s'\n", result.tokens[i].type, result.tokens[i].value);
    }

    return 0;
}