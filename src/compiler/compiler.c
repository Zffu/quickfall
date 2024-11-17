/**
 * The compiler of Quickfall.
 */

#include <string.h>
#include <stdio.h>
#include "../parser/ast.h"
#include "./platforms/platforms.h"
#include "./platforms/linux.h"

struct CompilerOutput {
    char output[2048];
};

struct CompilerOutput compile(struct ASTNode* node) {
    char sections[1024] = {""};
    char startOutput[1024] = {"_start:"};

    while(node->next != NULL) {
        node = node->next;

        if(node->type == AST_FUNCTION_CALL) {
            struct FunctionResult result = handleLinuxLowlevelFunctions(node);

            if(result.mode == 0) strcat(startOutput, result.output);
        }
    }

    struct CompilerOutput o;
    strcat(o.output, sections);
    strcat(o.output, startOutput);

    printf("\n%s", o.output);
    return o;
}