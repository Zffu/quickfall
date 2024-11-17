/*
* Windows compiling changes
*/

#include <string.h>

/**
 * Handles the extrnLoad assembly thing.
 */
void extrnLoad(char* buffer, char* name) {
    strcat(buffer, "\nextern ");
    strcat(buffer, name);
}

/**
 * Handles the globalDef assembly thing.
 */
void globalDef(char* buffer, char* name) {
    strcat(buffer, "\nglobal ");
    strcat(buffer, name);
}

/**
 * Handles the decSec assembly thing.
 */
void winDecSec(char* buffer, char* name, char* type, char* value) {
    strcat(buffer, "\n    ");
    strcat(buffer, name);
    strcat(buffer, "     ");
    strcat(buffer, type);
    strcat(buffer, "  '");
    strcat(buffer, value);
    strcat(buffer, "', 13, 10, 0");
}

/**
 * Handles the push assembly thing.
 */
void push(char* buffer, char* name) {
    strcat(buffer, "\n    push ");
    strcat(buffer, name);
}

/**
 * Handles the call assembly thing.
 */
void call(char* buffer, char* name) {
    strcat(buffer, "\n    call ");
    strcat(buffer, name);
}

/**
 * Handles the add assembly thing.
 */
void add(char* buffer, char* name, char* value) {
    strcat(buffer, "\n    add ");
    strcat(buffer, name);
    strcat(buffer, ", ");
    strcat(buffer, value);
}

/**
 * Handles the ret assembly thing.
 */
void ret(char* buffer) {
    strcat(buffer, "\n    ret");
}