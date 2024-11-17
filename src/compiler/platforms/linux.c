/**
 * Linux compiling changes
 */

#include <string.h>
#include "../../parser/ast.h"
#include "./platforms.h"

/**
 * Handles the secDec assembly thing.
 */
char* secDec(char* sectName) {
    char instruction[32] = {"section ."};
    strcat(instruction, sectName);

    return instruction;
}

/**
 * Handles the decSec assembly thing.
 */
char* decSec(char* name, char* type, char* val) {
    char instruction[32] = {""};
    strcat(instruction, name);
    strcat(instruction, " ");
    strcat(instruction, type);
    strcat(instruction, " '");
    strcat(instruction, val);
    strcat(instruction, "', 0");

    return instruction;
}

/**
 * Handles the secEnd assembly thing.
 */
char* secEnd() {
    return "\n\n";
}

/**
 * Handles the movR assembly thing.
 */
char* movR(char* name, char *v) {
    char instruction[32] = {"\n    mov "};
    strcat(instruction, name);
    strcat(instruction, ", ");
    strcat(instruction, v);

    return instruction;
}

/**
 * Handles the sectG assembly thing.
 */
char* sectG(char* name) {
    char instruction[32] = "\n    global ";
    strcat(instruction, name);
    
    return name;
}

/**
 * Handles the syscall assembly thing.
 */
char* syscall() {
    return "\n    int 0x80";
}

/**
 * Handles the regXOR assembly thing.
 */
char* regXOR(char* name, char* name2) {
    char instruction[32] = {"\n    xor "};
    strcat(instruction, name);
    strcat(instruction, ", ");
    strcat(instruction, name2);
}