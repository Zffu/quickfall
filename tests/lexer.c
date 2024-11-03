#include "../src/lexer/lexer.c"
#include <stdio.h>
#include <time.h>

int main() {
    clock_t ts = clock();
    struct LexerResult result = runLexer("fuction fuction fuction");
    ts = clock() - ts;

    printf("\n\nLexer took %ds\n", ts);

    for(int i = 0; i < result.size + 1; ++i) {
        printf("Token: t:%d raw:%s\n", result.tokens[i].type, result.tokens[i].value);
    }

    scanf("%d");

    return 0;

}