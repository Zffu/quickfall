/**
 * The compiler of Quickfall.
 */

#include <string.h>
#include <stdio.h>
#include "../parser/ast.h"

#include "./platforms/linux.h"
#include "./platforms/windowsx86-64.h"

enum Platform {
    WINDOWS,
    LINUX
};

enum Platform platformFromString(char* platform) {
    if(strcmp(platform, "win")) return WINDOWS;
    else LINUX;
}

struct CompilerOutput compile(struct ASTNode* node, char* platform) {
    enum Platform p = platformFromString(platform);

    struct CompilerOutput o;

    switch(p) {
        case WINDOWS:
            return win64compile(node);
        default:
            printf("Error: This platform is currently not supported! \n");
            return o;
    }

    printf("\n%s", o.output);
    return o;
}