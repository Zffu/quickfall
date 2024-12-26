/**
 * Parsing for variable related ASTs.
 */

#include <stdio.h>

#include "../structs/variables.h"

#include "../ast.h"

#include "../../lexer/lexer.h"

/**
 * Parses a variable declaration.
 * @param result the Lexer result.
 * @param index the index where the parsing needs to start.
 */
AST_VARIABLE_DEC parseVariableDeclaration(LEXER_RESULT result, int index) {
    AST_VARIABLE_DEC var = {0};
    var.astType  = AST_TYPE_VARIABLE_DECLARATION;

    switch(result.tokens[index].type) {
        case TYPE_INT32:
            var.type[0] = 0x01;
            break;
        case VAR:
            var.type[0] = 0x00;
            break;
        default:
            printf("Error: Disallowed token as variable type! Defaulting to untyped variable!\n");
            var.type[0] = 0x00;
            break;
    }

    if(result.tokens[index + 1].type != KEYWORD) {
        printf("Error: Excepted a keyword for variable name!\n");
        return var;
    }

    var.name = result.tokens[index + 1].value;
    

    if(result.tokens[index + 2].type == DECLARE) {
        //todo: add value parsing if the next token is "="
    }

    return var;
}