/**
 * The Intermediate Representation of Quickfall Code.
 */

#ifndef IR2_H
#define IR2_H

/**
 * An IR instruction.
 */
typedef struct {

    unsigned char* opCode;

    void* params;
    int paramCount;

} IR_INSTRUCTION;

#endif