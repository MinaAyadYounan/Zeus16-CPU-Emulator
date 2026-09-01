#ifndef INSTRUCTION_MEMORY_H
#define INSTRUCTION_MEMORY_H

#include <cstdint>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;


class InstructionMemory {

private:
        uint8_t inst_mem[65536];
        int inst_mem_length ; 
public:


    
    InstructionMemory(const string& filename) {
        memory_init();
        load_hex_file(filename, 0);
    }

    // Memory initialization
    void memory_init() {
                for(int i = 0 ; i < sizeof(inst_mem);i++) {
                    inst_mem[i] = 0 ;
                }


    }


    uint16_t read16(uint16_t addr, bool& is_halted) {
        //  misalignment: print alignment trap error, set is_halted = true
        //  Return Little-Endian 16-bit value from data memory.
        uint16_t value ;
        if(addr % 2 == 0 ) {
            is_halted = false ;
            value = static_cast<uint16_t>(inst_mem[addr]) ; 
            value = value | (static_cast<uint16_t>(inst_mem[addr + 1])) << 8 ; 
            return value ;
        }
        else {
            is_halted = true ;
            cout << "instruction memory address misalignment" << endl;
            return 0 ; 
        }

    }

    bool load_hex_file(const string& filename, uint16_t start_addr = 0) {
        ifstream prog_hex(filename) ; 
        uint16_t value; 
        int i = 0 ; 
        if (!prog_hex.is_open() || prog_hex.peek() == ifstream::traits_type::eof()) {
        cerr << "Error: Program file is missing or empty!" << endl;
        exit(1);
                }
        while(prog_hex >> hex >> value){
                inst_mem[i + start_addr]     = static_cast<uint8_t>(value & 0x00FF);            
                inst_mem[i + 1 + start_addr] = static_cast<uint8_t>((value & 0xFF00) >> 8);
                i+=2; 
        } 
        inst_mem_length = i ;
        prog_hex.close();
        return true ;   
    }
    void write_mem_content_byte(){
        cout << "address  | instruction " << endl ; 
        
        for(uint16_t i = 0 ; i <= inst_mem_length ; i++) {
            cout << "0x"<< hex << setw(2) << setfill('0') << i <<"   |0x" << inst_mem[i] <<endl ;    
        }
        
    } 
    void write_mem_content_word(){
        uint16_t word_val ;
        cout << "address  | instruction " << endl ; 
        for(uint16_t i = 0 ; i < inst_mem_length ; i+=2) {
            word_val = static_cast<uint16_t>(inst_mem[i]) ; 
            word_val = word_val | (static_cast<uint16_t>(inst_mem[i + 1])) << 8 ; 
            cout << "0x"<<hex <<setw(2) << setfill('0') << i <<"     | 0x" << word_val <<endl ;    
        }

    } 
};

#endif // INSTRUCTION_MEMORY_H
