/**
 * The instruction codes for the Quickfall IR.
 */

#ifndef IR_INSTRUCTIONS
#define IR_INSTRUCTIONS

/**
 * The instruction codes of IR.
 */
typedef enum {

    BLOCK_SWAP,
    COND_BLOCK_SWAP,
    LOGICAL_BLOCK_SWAP,

    S_ALLOC,
    PTR_SET,

} IR_INSTRUCTION_CODES;

#endif