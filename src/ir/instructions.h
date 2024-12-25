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
    PTR_LOAD,

    IADD,
    ISUB,
    IMUL,
    IDIV,

    ICMP,
    ICMP_H,
    ICMP_L,

    PRM_PUSH,
    CALL

} IR_INSTRUCTION_CODES;

#endif