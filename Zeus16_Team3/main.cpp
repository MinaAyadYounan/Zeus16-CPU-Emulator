#include "CPU.h"
#include <iostream>

using namespace std;

void run(const string& name ,const string& filename) {
    cout << "===========================================" << endl;
    cout << "  " << name << " (" << filename << ")" << endl;
    cout << "===========================================" << endl;

    CPU cpu(filename);
    cout << "Running program..." << endl;

    const int MAX_STEPS = 25;
    int steps = 0;
    while (!cpu.halted() && steps < MAX_STEPS) {
        cpu.step();
        steps++;
    }

    cout << endl;
    cpu.dump_assembly_log();

    cout << endl;
    cpu.dump_registers();

    cout << endl;
    cpu.dump_instruction_memory();

    cout << endl;
    cpu.dump_data_memory();

    cout << endl;
}

int main() {
    run("CPU Instance 1: Normal Execution", "program.hex");
    run("CPU Instance 2: Halt on Misalignment Trap", "program_halt.hex");
    return 0;
}
