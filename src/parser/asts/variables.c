/**
 * Parsing for variable related ASTs.
 */

#include <stdlib.h>
#include <stdio.h>

#include "../structs/variables.h"
#include "./values.h"

#include "../ast.h"

#include "../../lexer/lexer.h"

/**
 * Parses a variable declaration.
 * @param result the Lexer result.
 * @param index the index where the parsing needs to start.
 */
AST_VARIABLE_DEC* parseVariableDeclaration(LEXER_RESULT result, int index) {
    AST_VARIABLE_DEC* var = malloc(sizeof(AST_VARIABLE_DEC));
    var->astType  = AST_TYPE_VARIABLE_DECLARATION;

    switch(result.tokens[index].type) {
        case TYPE_INT32:
            var->type[0] = 0x01;
            break;
        case VAR:
            var->type[0] = 0x00;
            break;
        default:
            printf("Error: Disallowed token as variable type!\n");
            return NULL;
    }

    if(result.tokens[index + 1].type != KEYWORD) {
        printf("Error: Excepted a keyword for variable name!\n");
        return NULL;
    }

    var->name = result.tokens[index + 1].value;
    

    if(result.tokens[index + 2].type == DECLARE) {
        void* value = parseValueGroup(result, index + 3);

        if(value == NULL) {
            printf("Error: Couldn't parse variable value group!\n");
            return NULL;
        }

        var->value = value;
    }

    return var;
}


/**
 * Parses a variable modification.
 * @param result the Lexer result.
 * @param index the index where the parsing needs to start.
 */
AST_VARIABLE_MOD* parseVariableModification(LEXER_RESULT result, int index) {
    AST_VARIABLE_MOD* mod = malloc(sizeof(AST_VARIABLE_MOD));
    mod->type = AST_TYPE_VARIABLE_MODIFICATION;

    mod->name = result.tokens[index].value;

    void* value = parseValueGroup(result, index + 2);

    if(value == NULL) {
        printf("Error: Couldn't parse variable value group in redefinition!\n");
        return NULL;
    }

    mod->value = value;
    
    return mod;
}