/**
 * The main file of the Quickfall CLI.
 * A modern, fast and lightweight programming language.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../parser/ast.h"
#include "../lexer/lexer.h"
#include "../parser/parser.h"

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


char* getStringCounterpart(enum ASTNodeType type)  {
    char* debug[18] = {"Variable Definition", "Function Definition", "Function Name", "Function Template", "Function Body", "Function Call", "Variable", "Parameters", "Parameter", "Parameter Type", "Parameter Name", "Generic", "Function Invoking Target", "Function Invoking Parameters", "Variable Type", "Variable Meta", "Variable Name", "Variable Value"};
    return debug[type];
}

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
    printf("  r, run           Run a Quickfall program\n");
    printf("  b, build         Build a Quickfall program to executable\n");
    printf("  i, init          Create a new Quickfall project\n");
    printf("  t, test          Run tests for a Quickfall project\n");
    printf("  h, help          Show this help message\n");
    printf("  v, version       Show version information\n\n");
    
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
char* readFile(const char* path) {
    FILE* filePtr = fopen(path, "r");
    if (filePtr == NULL) {
        printf("Error: Could not open file '%s'\n", path);
        exit(1);
    }

    fseek(filePtr, 0, SEEK_END);
    int size = ftell(filePtr);
    fseek(filePtr, 0, SEEK_SET);

    char* bufferPtr = (char*) malloc(size + 1);
    if (bufferPtr == NULL) {
        printf("Error: Memory allocation failed\n");
        fclose(filePtr);
        exit(1);
    }

    fread(bufferPtr, 1, size, filePtr);
    bufferPtr[size] = '\0';
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

    switch(args.command[0]) {
        case 'h':
            showHelpMessage();
            return 0;
        case 'v':
            printf("Quickfall version %s\n", VERSION);
            return 0;

        case 'r':
            if(!args.inputFile) {
                printf("Error: Missing input file!\n");
                return -1;
            }
            
            char* buff = readFile(args.inputFile);
            struct LexerResult result = runLexer(buff);

            struct ASTNode* node = runParser(result);

            if(node == NULL) {
                printf("Error: cannot generate output as the provided AST node is null!");
                return;
            }

            printf("AST Node dump:\n");
            dumpAST(node,0);

            free(buff);
            return 1;
        
        case 'b':
            if(!args.inputFile) {
                printf("Error: Missing input File!");
                return -1;
            }

            printf("→ Creating new project '%s'...\n", args.inputFile);
            return 1;

        case 'i':
            if(!args.inputFile) {
                printf("Error: Missing project name\n");
                return -1;
            }

            printf("→ Creating new project '%s'...\n", args.inputFile);
            return 1;
        
        case 't':
            printf("→ Running tests...\n");
            return 1;
        
        default:
            printf("Error: Unknown command '%s'\n", args.command);
            showHelpMessage();
            return 0;
    }
}

void dumpAST(struct ASTNode* node, int depth) {
    for(int i = 0; i < depth; ++i) {
        printf("  ");
    }

    printf("AST Node of type %s (%d) with value '%s'\n", getStringCounterpart(node->type), node->type, (node->value != "" ? node->value : "None"));
    
    if(node->left != NULL) {
        dumpAST(node->left, depth + 1);
    }

    if(node->right != NULL) {
        dumpAST(node->right, depth + 1);
    }

    if(node->next != NULL) {
        dumpAST(node->next, depth);
    }
}