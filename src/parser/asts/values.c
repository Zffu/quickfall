/**
 * Parsing for value related ASTs.
 */

#include <stdlib.h>
#include <stdio.h>

#include "../structs/values.h"

#include "../ast.h"

#include "../../lexer/lexer.h"

/**
 * Parses an AST value on the lexer result.
 * @param result the Lexer result.
 * @param index the index of the start of the parsing.
 */
AST_VALUE* parseASTValue(LEXER_RESULT result, int index) {
    AST_VALUE* value = malloc(sizeof(AST_VALUE));
    value->astType = AST_TYPE_VALUE;


    switch(result.tokens[index].type) {
        case NUMBER:
            value->valueType[0] = 0x01; //i32
            break;
        default:
            printf("Error: Couldn't parse token %d as a value!\n", result.tokens[index].type);
            return value;
    }

    value->endingIndex = index;
    value->value = result.tokens[index].value;

    return value;
}


/**
 * Parses an actual expression as value instead of just one token.
 * @param result the Lexer result.
 * @param index the index of the start of the parsing.
 */
void* parseValueGroup(LEXER_RESULT result, int index) {
    switch(result.tokens[index].type) {
        case NUMBER:
            if(result.tokens[index + 1].type == MATH_OP) {
                //todo: parse math op.
            }
            
            return parseASTValue(result, index);
            break;
        default:
            printf("Error: couldn't parse value token group!\n");
            return NULL;
    }
}