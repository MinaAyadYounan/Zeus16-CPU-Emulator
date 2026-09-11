#ifndef CPU_H
#define CPU_H

#include "InstructionMemory.h"
#include "DataMemory.h"
#include "Instruction.h"
#include "Decoder.h"
#include "Disassembler.h"
#include "ALU.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;


    // CPU & Pipeline Controller (Harvard Architecture)
 
class CPU {
private:
    uint16_t R[8];
    uint16_t PC;
    bool is_halted;
    bool unknown_isa;
    vector<string> assembly_log;
    vector<uint16_t> pc_log;

    InstructionMemory inst_mem;
    DataMemory data_mem;
    Decoder decoder;
    Disassembler disassembler;
    ALU alu;
    

public:

    CPU(const string& hex_filename = "") : inst_mem(hex_filename) {
        reset();
    }

    void reset() {
        for (int i = 0; i < 8; ++i) R[i] = 0;
        PC = 0;
        is_halted = false;
        unknown_isa = false;
        assembly_log.clear();
        pc_log.clear();
        data_mem.memory_init();
    }

    bool halted() const { return is_halted; }
    bool get_unknown_isa() const { return unknown_isa; }
    uint16_t get_reg(uint8_t idx) {
        if (idx == 0) return 0;
        if (idx < 8) return R[idx];
        return 0;
    }

    void set_reg(uint8_t idx, uint16_t val) {
        if (idx == 0) return;
        if (idx < 8) R[idx] = val;
    }

    void step() {
        if (is_halted) {
            cout << "[CPU] CPU is halted due to trap. Step aborted." << endl;
            return;
        }

        // --- 1. Fetch ---
        uint16_t fetch_pc = PC;
        uint16_t raw_inst = inst_mem.read16(PC, is_halted);
        if (is_halted) return;

        // --- 2. Decode ---
        Instruction inst = decoder.decode(raw_inst);
        uint8_t r_reserved = (raw_inst >> 9) & 0x7;
        if (inst.steering_bit == 0 && r_reserved != 0) {
            cout << "unknown isa" << endl;
            unknown_isa = true;
            is_halted = true;
            return;
        }
        // --- 3. Disassemble ---
        string asm_text = disassembler.disassemble(inst);
        assembly_log.push_back(asm_text);
        pc_log.push_back(fetch_pc);

        // --- 4. Execute ---
        uint16_t next_pc = static_cast<uint16_t>(PC + 2); // sequential default

        if (inst.steering_bit == 0) {
            // R-type: ADD, SUB, AND, OR, SLT, MUL, DIV, REM
            uint16_t a = get_reg(inst.rs);
            uint16_t b = get_reg(inst.rt);
            uint16_t result = alu.execute_r(inst.opcode, a, b);
            if (inst.reg_write) {
                set_reg(inst.rd, result);
            }
        } else {
            switch (inst.opcode) {
                case 0b000: // ADDI
                case 0b001: // ANDI
                case 0b010: // ORI
                case 0b011: { // SLTI
                    uint16_t a = get_reg(inst.rs);
                    uint16_t result = alu.execute_i(inst.opcode, a, inst.immediate);
                    if (inst.reg_write) {
                        set_reg(inst.rd, result);
                    }
                    break;
                }
                case 0b100: { // LW: rd = Mem[rs + imm]
                    uint16_t addr = static_cast<uint16_t>(get_reg(inst.rs) + inst.immediate);
                    uint16_t val = data_mem.read16(addr, is_halted);
                    if (is_halted) return;
                    if (inst.reg_write) {
                        set_reg(inst.rd, val);
                    }
                    break;
                }
                case 0b101: { // SW: Mem[rs + imm] = rd
                    uint16_t addr = static_cast<uint16_t>(get_reg(inst.rs) + inst.immediate);
                    data_mem.write16(addr, get_reg(inst.rd), is_halted);
                    if (is_halted) return;
                    break;
                }
                case 0b110: { // BEQ: if (rd == rs) PC = PC + imm
                    if (get_reg(inst.rd) == get_reg(inst.rs)) {
                        next_pc = static_cast<uint16_t>(PC + inst.immediate);
                    }
                    break;
                }
                case 0b111: { // JAL: PC = PC + imm (unconditional, no link write)
                    next_pc = static_cast<uint16_t>(PC + inst.immediate);
                    set_reg(inst.rd, PC + 2);
                    
                    break;
                }
                default:
                    cout << "unknown isa" << endl;
                    unknown_isa = true;
                    is_halted = true;
                    return;

            }
        }

        PC = next_pc;
    }

    void dump_assembly_log() {
        cout << "----- Disassembled Program  -----" << endl;
        for (size_t i = 0; i < assembly_log.size(); ++i) {
            cout << "0x" << hex << setw(4) << setfill('0') << pc_log[i]
                 << dec << ":  " << assembly_log[i] << endl;
        }
    }

    void dump_registers() {
        cout << "------ CPU Registers ------" << endl;
        for (int i = 0; i < 8; ++i) {
            cout << "R" << i << " = 0x" << hex << setw(4) << setfill('0') << R[i]
                 << dec << " (" << R[i] << ")" << endl;
        }
        cout << "PC = 0x" << hex << setw(4) << setfill('0') << PC << dec << endl;
        cout << "HALTED = " << (is_halted ? "true" : "false") << endl;
    }
    void dump_instruction_memory() {
    cout << "----- Instruction Memory -----" << endl;
    inst_mem.write_mem_content_word();
    }
    void dump_data_memory() {
        cout << "----- Data Memory -----" << endl;
        data_mem.write_mem_content_word();
    }
};

#endif // CPU_H
