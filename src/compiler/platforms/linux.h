/**
 * Linux compiling changes
 */

#ifndef COMPILER_PLATFORM_LINUX_H
#define COMPILER_PLATFORM_LINUX_H

#include <string.h>
#include "../../parser/ast.h"

void decSec(char* buffer, char* name, char* type, char* val);
void movR(char* buffer, char* name, char* v);
void sectG(char* buffer, char* val);
void syscall(char* buffer);
void regXOR(char* buffer, char* name1, char* name2);

#endif