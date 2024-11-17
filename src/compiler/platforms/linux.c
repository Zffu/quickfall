/**
 * Linux compiling changes
 */

#include <string.h>
#include "../../parser/ast.h"

void debug_strcat(char* p, char* p1) {
    printf("strcat called! 1st null: %d, 2nd: %d\n", p == NULL, p1 == NULL);

    //strcat(p,p1);
}

/**
 * Handles the decSec assembly thing.
 */
void decSec(char* buffer, char* name, char* type, char* val) {
    strcat(buffer, "\n    ");
    strcat(buffer, name);
    strcat(buffer, " ");
    strcat(buffer, type);
    strcat(buffer, " '");
    strcat(buffer, val);
    strcat(buffer, "', 0");
}

/**
 * Handles the movR assembly thing.
 */
void movR(char* buffer, char* name, char *v) {
    strcat(buffer, "\n    mov ");
    strcat(buffer, name);
    strcat(buffer, ", ");
    strcat(buffer, v);
}

/**
 * Handles the sectG assembly thing.
 */
void sectG(char* buffer, char* name) {
    strcat(buffer, "\n    global ");
    strcat(buffer, name);
}

/**
 * Handles the syscall assembly thing.
 */
void syscall(char* buffer) {
    strcat(buffer, "\n    int 0x80");
}

/**
 * Handles the regXOR assembly thing.
 */
void regXOR(char* buffer, char* name, char* name2) {
    strcat(buffer, "\n    xor ");
    strcat(buffer, name);
    strcat(buffer, ", ");
    strcat(buffer, name2);
}