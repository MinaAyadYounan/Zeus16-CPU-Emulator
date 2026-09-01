#ifndef DATA_MEMORY_H
#define DATA_MEMORY_H

#include <cstdint>
#include <iostream>
#include <set>
#include <iomanip>

using namespace std;

class DataMemory {
private:
        uint8_t data[65536];
        set<uint16_t> active_address ; 

public:
    DataMemory() {
        memory_init();
    }

    // Memory initialization
    void memory_init() {
        for(int i = 0 ; i < sizeof(data);i++) {
            data[i] = 0 ;
        }
    }

    uint16_t read16(uint16_t addr, bool& is_halted) {
        //  misalignment: print alignment trap error, set is_halted = true
        //  Return Little-Endian 16-bit value from data memory.
        uint16_t value ;
        if(addr % 2 == 0 ) {
            is_halted = false ;
            value = static_cast<uint16_t>(data[addr]) ; 
            value = value | (static_cast<uint16_t>(data[addr + 1])) << 8 ; 
            return value ;
        }
        else {
            is_halted = true ;
            cout << "memory address misalignment" ;
            return 0 ; 
        }

    }

    void write16(uint16_t addr, uint16_t val, bool& is_halted) {
        
        // misallignemnt : print alignment trap error, set is_halted = true, and return.
        // Write Little-Endian 16-bit value into data memory.

        if(addr % 2 == 0 ) {
            is_halted    = false ;
            data[addr]   = static_cast<uint8_t>(val & 0x00FF);
            data[addr+1] = static_cast<uint8_t>((val & 0xFF00) >> 8);
            active_address.insert(addr) ; 

        }
        else {
            is_halted = true ;
            cout << "data memory address misalignment" << endl;
        }
    }
     void write_mem_content_byte(){
        cout << "address  | data " << endl ; 
        for(uint16_t addr : active_address) {
            cout << "0x" << hex <<setw(2) << setfill('0') << addr     <<"   |0x" << data[addr]<<endl ;    
            cout << "0x" << hex <<setw(2) << setfill('0') << addr + 1 <<"   |0x" << data[addr + 1] <<endl ;    
        }
        
    } 
    void write_mem_content_word(){
        uint16_t word_val ;
        cout << "address  | data " << endl ; 
        
        for(uint16_t addr : active_address) {
            word_val = static_cast<uint16_t>( data[addr]) ; 
            word_val = word_val | (static_cast<uint16_t>( data[addr + 1])) << 8 ; 
                cout << "0x"<< hex << setw(4) << setfill('0') << addr <<"   | 0x" << word_val <<endl ;    

            }

        } 
};

#endif // DATA_MEMORY_H
