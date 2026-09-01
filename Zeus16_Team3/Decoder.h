#ifndef DECODER_H
#define DECODER_H

#include "Instruction.h"

using namespace std;

// generate control signals, and decode instructions
class Decoder {
public:
    Instruction decode(uint16_t raw) {
        Instruction inst;
        inst.is_branch = false;
        inst.is_jump   = false;

        inst.steering_bit = (raw >> 15) & 0x1;
        inst.opcode       = (raw >> 12) & 0x7;
        inst.rd           = raw & 0x7;
        inst.rs           = (raw >> 3) & 0x7;

        if (inst.steering_bit == 0) {
            inst.rt = (raw >> 6) & 0x7;
            inst.immediate = 0;
        } else {
            inst.rt = 0;

            uint16_t imm6 = (raw >> 6) & 0x3F;

            if (imm6 & 0x20) {
                inst.immediate = imm6 | 0xFFC0;
            } else {
                inst.immediate = imm6;
            }
            if (inst.opcode == 0b110) {
                inst.is_branch = true;
            } else if (inst.opcode == 0b111) {
                inst.is_jump = true;
            }
        }

        if (inst.steering_bit == 0) {
            inst.reg_write  = true;   
            inst.mem_to_reg = false;
            inst.mem_write  = false;
        } else {
            inst.reg_write  = (inst.opcode != 0b101 && inst.opcode != 0b110 && inst.opcode != 0b111);
            inst.mem_to_reg = (inst.opcode == 0b100);
            inst.mem_write  = (inst.opcode == 0b101);
        }

        return inst;
    }
};

#endif // DECODER_H