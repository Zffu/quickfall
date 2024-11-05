/**
 * The main file of the Quickfall CLI.
 */

#include <stdio.h>

int main(int argc, char* argv[]) {
    if(argc < 2) {
        showHelpMessage();
        return -1;
    }
}

/**
 * Shows the CLI help message.
 */
void showHelpMessage() {
    printf("Quickfall commands:\n   quickfall -v - Shows the version information of your Quickfall distribution.\n   quickfall -l <file> - Runs a Quickfall lexer check on the provided file.");
}