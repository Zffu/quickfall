/**
 * Parsing for value related ASTs.
 */

#include <stdio.h>

#include "../structs/values.h"

#include "../../lexer/lexer.h"

/**
 * Parses an AST value on the lexer result.
 * @param result the Lexer result.
 * @param index the index of the start of the parsing.
 */
AST_VALUE parseValue(LEXER_RESULT result, int index) {
    AST_VALUE value = {0};

    switch(result.tokens[index].type) {
        case NUMBER:
            value.valueType = 0x01; //i32
            break;
        default:
            printf("Error: Couldn't parse token %d as a value!\n", result.tokens[index].type);
            return value;
    }

    value.value = result.tokens[index].value;

    return value;
}