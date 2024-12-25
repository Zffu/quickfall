/**
 * The instruction codes for the Quickfall IR.
 */

#ifndef IR_INSTRUCTIONS
#define IR_INSTRUCTIONS

/**
 * The instruction codes of IR.
 */
typedef enum {

    /**
     * Swaps the current IR block.
     * @param block the new IR block index in the context (function for instance).
     */
    BLOCK_SWAP,

    /**
     * Swaps the current IR block if a condition is met.
     * @param block the new IR block index in the context (function for instance).
     * @param cond the condition to match.
     */
    COND_BLOCK_SWAP,

    /**
     * Swaps the current IR block depending on a condition result.
     * @param trueBlock the new IR block index in the context (function for instance) if the condition is met.
     * @param falseBlock the new IR block index in the context (function for instance) if the condition isn't met.
     * @param cond the condition.
     */
    LOGICAL_BLOCK_SWAP,

    /**
     * Allocates a set amount of bits in the stack.
     * @param ptr the pointer that is going to be allocated.
     * @param size the size of the pointer.
     */
    S_ALLOC,

    /**
     * Sets the value of the pointer's address to the provided element.
     * @param val the new value (an integer for now).
     * @param ptr the pointer containing the target address.
     */
    PTR_SET,

    /**
     * Loads the values of a specific address into a variable.
     * @param var the output variable.
     * @param ptr the pointer containing the target address.
     */
    PTR_LOAD,

    IADD,
    ISUB,
    IMUL,
    IDIV,

    ICMP,
    ICMP_H,
    ICMP_L,

    PRM_PUSH,
    CALL,
    RET

} IR_INSTRUCTION_CODES;

#endif