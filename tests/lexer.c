/**
 * Lexer test for Quickfall.
 */

#include "../src/lexer/lexer.h"
#include "../src/lexer/tokens.h"

/**
 * Runs the lexer test.
 */
int runLexerTest(char* buff) {
	struct LexerResult result = runLexer(buff);

	if(result.size == 0) return -1;

	return 0;
}
