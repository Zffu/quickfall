/**
 * The main file of the Quickfall CLI.
 * A modern, fast and lightweight programming language.
 * Usage:
 * quickfall build <input> -o <output> - Builds the input files into an output.
 * quickfall help - Shows the help command.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../parser/ast.h"
#include "../lexer/lexer.h"
#include "../parser/parser.h"
#include "../compiler/compiler.h"

// Version
#define VERSION "0.1.0"

