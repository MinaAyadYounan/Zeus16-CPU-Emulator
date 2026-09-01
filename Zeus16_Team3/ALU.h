#ifndef ALU_H
#define ALU_H

#include <cstdint>

class ALU {
public:
    // Execute R-Type instructions (Register-Register operations)
    uint16_t execute_r(uint8_t opcode, uint16_t a, uint16_t b) {
        int16_t sa = static_cast<int16_t>(a);
        int16_t sb = static_cast<int16_t>(b);

        switch (opcode) {
            case 0b000: return static_cast<uint16_t>(sa + sb);       // ADD
            case 0b001: return static_cast<uint16_t>(sa - sb);       // SUB
            case 0b010: return a & b;                                // AND
            case 0b011: return a | b;                                // OR
            case 0b100: return (sa < sb) ? 1 : 0;                    // SLT (Signed Less Than)
            
            // M-Extension (Multiplication/Division)
            case 0b101: return static_cast<uint16_t>(sa * sb);       // MUL (Lower 16 bits)
            case 0b110: {                                            // DIV
                if (sb == 0) return 0xFFFF;                          // Division by zero = -1 (all 1s)
                return static_cast<uint16_t>(sa / sb);
            }
            case 0b111: {                                            // REM
                if (sb == 0) return a;                               // Remainder by zero = dividend
                return static_cast<uint16_t>(sa % sb);
            }
            default: return 0;
        }
    }

    // Execute I-Type instructions (Register-Immediate operations)
    uint16_t execute_i(uint8_t opcode, uint16_t a, int16_t imm) {
        int16_t sa = static_cast<int16_t>(a);

        switch (opcode) {
            case 0b000: return static_cast<uint16_t>(sa + imm);      // ADDI
            case 0b001: return a & static_cast<uint16_t>(imm);       // ANDI
            case 0b010: return a | static_cast<uint16_t>(imm);       // ORI
            case 0b011: return (sa < imm) ? 1 : 0;                   // SLTI
            default: return 0;
        }
    }
};

#endif // ALU_H