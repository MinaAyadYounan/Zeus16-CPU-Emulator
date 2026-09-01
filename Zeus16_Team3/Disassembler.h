#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include "Instruction.h"
#include <string>

using namespace std;

class Disassembler {
public:
    string disassemble(const Instruction& inst) {
        string assembly_inst = "";

        if (inst.steering_bit == 0) {
            
            switch (inst.opcode) {
                case 0: 
                    assembly_inst = "ADD R" + to_string(inst.rd) + ", R" + to_string(inst.rs) + ", R" + to_string(inst.rt); 
                    break;
                case 1: 
                    assembly_inst = "SUB R" + to_string(inst.rd) + ", R" + to_string(inst.rs) + ", R" + to_string(inst.rt); 
                    break;
                case 2: 
                    assembly_inst = "AND R" + to_string(inst.rd) + ", R" + to_string(inst.rs) + ", R" + to_string(inst.rt); 
                    break;
                case 3: 
                    assembly_inst = "OR R" + to_string(inst.rd) + ", R" + to_string(inst.rs) + ", R" + to_string(inst.rt); 
                    break;
                case 4: 
                    assembly_inst = "SLT R" + to_string(inst.rd) + ", R" + to_string(inst.rs) + ", R" + to_string(inst.rt); 
                    break;
                case 5: 
                    assembly_inst = "MUL R" + to_string(inst.rd) + ", R" + to_string(inst.rs) + ", R" + to_string(inst.rt); 
                    break;
                case 6: 
                    assembly_inst = "DIV R" + to_string(inst.rd) + ", R" + to_string(inst.rs) + ", R" + to_string(inst.rt); 
                    break;
                case 7: 
                    assembly_inst = "REM R" + to_string(inst.rd) + ", R" + to_string(inst.rs) + ", R" + to_string(inst.rt); 
                    break;
                default: 
                    assembly_inst = "UNKNOWN_R_INSTRUCTION"; 
                    break;
            }

        } else {
            
            switch (inst.opcode) {
                case 0: 
                    assembly_inst = "ADDI R" + to_string(inst.rd) + ", R" + to_string(inst.rs) + ", " + to_string(inst.immediate); 
                    break;
                case 1: 
                    assembly_inst = "ANDI R" + to_string(inst.rd) + ", R" + to_string(inst.rs) + ", " + to_string(inst.immediate); 
                    break;
                case 2: 
                    assembly_inst = "ORI R" + to_string(inst.rd) + ", R" + to_string(inst.rs) + ", " + to_string(inst.immediate); 
                    break;
                case 3: 
                    assembly_inst = "SLTI R" + to_string(inst.rd) + ", R" + to_string(inst.rs) + ", " + to_string(inst.immediate); 
                    break;
                case 4: 
                    assembly_inst = "LW R" + to_string(inst.rd) + ", " + to_string(inst.immediate) + "(R" + to_string(inst.rs) + ")"; 
                    break;
                case 5: 
                    assembly_inst = "SW R" + to_string(inst.rd) + ", " + to_string(inst.immediate) + "(R" + to_string(inst.rs) + ")"; 
                    break;
                case 6: 
                    assembly_inst = "BEQ R" + to_string(inst.rs) + ", R" + to_string(inst.rd) + ", " + to_string(inst.immediate); 
                    break;
                case 7: 
                    assembly_inst = "JAL R" + to_string(inst.rd) + ", " + to_string(inst.immediate); 
                    break;
                default: 
                    assembly_inst = "UNKNOWN_I_INSTRUCTION"; 
                    break;
            }
        }

        return assembly_inst;
    }
};

#endif