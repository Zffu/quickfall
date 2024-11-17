/*
* Windows compiling changes
*/

#ifndef COMPILER_PLATFORM_WINDOWS_H
#define COMPILER_PLATFORM_WINDOWS_H

void extrnLoad(char* buffer, char* name);
void globalDef(char* buffer, char* name);
void winDecSec(char* buffer, char* name, char* type, char* value);
void push(char* buffer, char* name);
void call(char* buffer, char* name);
void add(char* buffer, char* name, char* value);
void ret(char* buffer);

#endif