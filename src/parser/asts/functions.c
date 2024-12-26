/**
 * Parsing for function related ASTs.
 */

#include <stdio.h>
#include <stdlib.h>

#include "../structs/functions.h"

#include "../ast.h"

#include "../../lexer/lexer.h"

/**
 * Parses a function declaration into AST.
 * @param result the Lexer result.
 * @param index the index of the start of the parsing.
 */
AST_FUNCTION_DEC* parseFunctionDeclaration(LEXER_RESULT result, int index) {
    AST_FUNCTION_DEC* func = malloc(sizeof(AST_FUNCTION_DEC));

    func->type = AST_TYPE_FUNCTION_DECLARATION;

    switch(result.tokens[index + 2].type) {
        case PAREN_OPEN:
            if(result.tokens[index + 1].type != KEYWORD) {
                printf("Error: Excepted a keyword as function name!\n");
                return NULL;
            }

            func->funcName = result.tokens[index + 0].value;
            func->returnType = 0x00;
            break;
        case KEYWORD:
            if(result.tokens[index + 1].type != TYPE_INT32) {
                printf("Error: Invalid type as function return type!\n");
                return NULL;
            }

            func->funcName = result.tokens[index + 2].value;
            func->returnType = 0x01;
            break;
        
        default:
            printf("Error: couldn't parse function declaration!\n");
            return NULL;
    }

    func->endingIndex = index + 2;

    return func;
}
