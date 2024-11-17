/**
 * Linux compiling changes
 */

#ifndef COMPILER_PLATFORM_LINUX_H
#define COMPILER_PLATFORM_LINUX_H

#include <string.h>
#include "../../parser/ast.h"
#include "./platforms.h"

char* decSec(char* name, char* type, char* val);
char* secEnd();
char* movR(char* name, char* v);
char* sectG(char* val);
char* syscall();
char* regXOR(char* name1, char* name2);

#endif