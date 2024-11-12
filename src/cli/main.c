/**
 * The main file of the Quickfall CLI.
 * A modern, fast and lightweight programming language.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../lexer/lexer.h"

// Version
#define VERSION "0.1.0"

// CLI Arguments structure
struct Arguments {
    char* command;
    char* inputFile;
    char* outputFile;
    int showHelp;
    int showVersion;
    int error;
};

#define BANNER "\
 ██████  ██    ██ ██  ██████ ██   ██ ███████  █████  ██      ██      \n\
██    ██ ██    ██ ██ ██      ██  ██  ██      ██   ██ ██      ██      \n\
██    ██ ██    ██ ██ ██      █████   █████   ███████ ██      ██      \n\
██ ▄▄ ██ ██    ██ ██ ██      ██  ██  ██      ██   ██ ██      ██      \n\
 ██████   ██████  ██  ██████ ██   ██ ██      ██   ██ ███████ ███████ \n\
    ▀▀                                                                 \n"

/**
 * Parse command line arguments into a structured format
 */
struct Arguments parseArguments(int argc, char* argv[]) {
    struct Arguments args = {
        .command = NULL,
        .inputFile = NULL,
        .outputFile = "a.out",
        .showHelp = 0,
        .showVersion = 0,
        .error = 0
    };

    if (argc < 2) {
        args.showHelp = 1;
        return args;
    }

    // First argument is always the command
    args.command = argv[1];

    // Parse flags and options
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0) {
            if (i + 1 < argc) {
                args.inputFile = argv[++i];
            } else {
                args.error = 1;
            }
        }
        else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
            if (i + 1 < argc) {
                args.outputFile = argv[++i];
            } else {
                args.error = 1;
            }
        }
        else if (args.inputFile == NULL) {
            // If no input file specified yet, treat as input file
            args.inputFile = argv[i];
        }
    }

    return args;
}

/**
 * Shows the CLI help message with modern formatting.
 */
void showHelpMessage() {
    printf("%s\n", BANNER);
    printf("Quickfall v%s - A modern, fast and lightweight programming language\n\n", VERSION);
    
    printf("USAGE:\n");
    printf("  quickfall <command> [options]\n\n");
    
    printf("COMMANDS:\n");
    printf("  run           Run a Quickfall program\n");
    printf("  build         Build a Quickfall program to executable\n");
    printf("  init          Create a new Quickfall project\n");
    printf("  test          Run tests for a Quickfall project\n");
    printf("  help          Show this help message\n");
    printf("  version       Show version information\n\n");
    
    printf("OPTIONS:\n");
    printf("  -f, --file    Specify input file path\n");
    printf("  -o, --output  Specify output file path (for build)\n\n");
    
    printf("EXAMPLES:\n");
    printf("  $ quickfall run example.qf\n");
    printf("  $ quickfall build example.qf -o example\n");
    printf("  $ quickfall init my-project\n");
    printf("  $ quickfall test\n");
}

/**
 * Reads a file into a buffer and returns the buffer and size.
 */
char* readFile(const char* path, int* size) {
    FILE* filePtr = fopen(path, "r");
    if (filePtr == NULL) {
        printf("Error: Could not open file '%s'\n", path);
        exit(1);
    }

    fseek(filePtr, 0, SEEK_END);
    *size = ftell(filePtr);
    fseek(filePtr, 0, SEEK_SET);

    char* bufferPtr = (char*) malloc(size);
    if (bufferPtr == NULL) {
        printf("Error: Memory allocation failed\n");
        fclose(filePtr);
        exit(1);
    }

    fread(bufferPtr, 1, *size, filePtr);
    bufferPtr[*size] = '\0';
    fclose(filePtr);
    return bufferPtr;
}

int main(int argc, char* argv[]) {
    struct Arguments args = parseArguments(argc, argv);

    if (args.error) {
        printf("Error: Invalid argument format\n");
        showHelpMessage();
        return 1;
    }

    if (strcmp(args.command, "help") == 0) {
        showHelpMessage();
        return 0;
    }

    if (strcmp(args.command, "version") == 0) {
        printf("Quickfall version %s\n", VERSION);
        return 0;
    }

    if (strcmp(args.command, "run") == 0) {
        if (!args.inputFile) {
            printf("Error: Missing input file\n");
            return 1;
        }

        int size;
        char* bufferPtr = readFile(args.inputFile, &size);
        struct LexerResult result = runLexer(bufferPtr);

        printf("\nTokens:\n");
        for (int i = 0; i < result.size; i++) {
            printf("  [%d] Type: %d, Value: '%s'\n", 
                   i, result.tokens[i].type, result.tokens[i].value);
        }

        free(bufferPtr);
        return 0;
    }

    if (strcmp(args.command, "build") == 0) {
        if (!args.inputFile) {
            printf("Error: Missing input file\n");
            return 1;
        }
        printf("→ Building '%s' to '%s'...\n", args.inputFile, args.outputFile);
        // TODO: Call compiler
        return 0;
    }

    if (strcmp(args.command, "init") == 0) {
        if (!args.inputFile) {
            printf("Error: Missing project name\n");
            return 1;
        }
        printf("→ Creating new project '%s'...\n", args.inputFile);
        // TODO: Initialize project structure
        return 0;
    }

    if (strcmp(args.command, "test") == 0) {
        printf("→ Running tests...\n");
        // TODO: Run test suite
        return 0;
    }

    printf("Error: Unknown command '%s'\n", args.command);
    showHelpMessage();
    return 1;
}