#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <cstdint>

using namespace std;

// Decoded instruction used between Decoder, Disassembler, and CPU Execution
struct Instruction {
    bool steering_bit;  // Bit 15: 0 for Register, 1 for I & J
    uint8_t opcode;     // Bits [14:12] (3 bits)
    uint8_t rd;         // Bits [2:0] (Destination)
    uint8_t rs;         // Bits [5:3] (Source 1)
    
    // Depending on the instruction type, only ONE of these is valid:
    uint8_t rt;         // Used for R-type (Bits [8:6])
    int16_t immediate;  // Used for I/J-type (Bits [11:6] Offset6, sign-extended)

    // Control Signals:
    bool reg_write;   // Does this instruction write to R[rd]?
    bool mem_to_reg;  // Is the writeback value coming from Data Memory (Lw)?
    bool mem_write;   // Does this instruction write to Data Memory (Sw)?
    bool is_branch;   // Is this a BEQ instruction?
    bool is_jump;     // Is this a JAL instruction?
};

#endif // INSTRUCTION_H
