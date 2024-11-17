/*
* Windows compiling changes
*/

#ifndef COMPILER_PLATFORM_WINDOWS_H
#define COMPILER_PLATFORM_WINDOWS_H

char* extrnLoad(char* name);
char* globalDef(char* name);
char* winDecSec(char* name, char* type, char* value);
char* push(char* name);
char* call(char* name);
char* add(char* name, char* value);
char* ret();

#endif