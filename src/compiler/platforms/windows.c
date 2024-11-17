/*
* Windows compiling changes
*/

#include <string.h>

/**
 * Handles the extrnLoad assembly thing.
 */
char* extrnLoad(char* name) {
    char instruction[32] = {"\nextern "};
    strcat(instruction, name);

    return instruction;
}

/**
 * Handles the globalDef assembly thing.
 */
char* globalDef(char* name) {
    char instruction[32] = {"\nglobal "};
    strcat(instruction, name);

    return instruction;
}

/**
 * Handles the decSec assembly thing.
 */
char* winDecSec(char* name, char* type, char* value) {
    char instructions[32] = {"\n"};
    strcat(instructions, name);
    strcat(instructions, ": ");
    strcat(instructions, type);
    strcat(instructions, " '");
    strcat(instructions, value);
    strcat(instructions, "', 10,0");

    return instructions;
}

/**
 * Handles the push assembly thing.
 */
char* push(char* name) {
    char instruction[32] = {"\n    push "};
    strcat(instruction, name);

    return instruction;
}

/**
 * Handles the call assembly thing.
 */
char* call(char* name) {
    char instruction[32] = {"\n    call "};
    strcat(instruction, name);

    return instruction;
}

/**
 * Handles the add assembly thing.
 */
char* add(char* name, char* value) {
    char instruction[32] = {"\n    add "};
    strcat(instruction, name);
    strcat(instruction, ", ");
    strcat(instruction, value);

    return instruction;
}

/**
 * Handles the ret assembly thing.
 */
char* ret() {
    return "\n    ret";
}