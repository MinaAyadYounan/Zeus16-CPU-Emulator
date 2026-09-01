# Zeus16-CPU-Emulator
16-bit ultra-embedded Little-Endian Harvard CPU emulator in C++ with full Fetch-Decode-Disassemble-Execute pipeline, M-extension support, and exception traps.
A 16-bit Harvard Architecture RISC CPU emulator and 4-stage pipeline simulator written in C++. 

---
## 🏛️ Architectural Overview
- **Architecture:** Harvard Architecture (Dedicated I-Mem & D-Mem)
- **Word Size:** 16-bit
- **Byte Ordering:** Little-Endian
- **Register File:** 8 General-Purpose Registers (`R0`–`R7`, 16-bit wide) with `R0` hardwired to `0`
- **Memory Alignment:** Strict 16-bit word alignment with hardware trap on misaligned odd addresses
- **Pipeline Stages:** Fetch ➔ Decode ➔ Disassemble ➔ Execute / Writeback
---
## 🚀 Instruction Set Support
- **Base (I) Extension:**
  - *Arithmetic & Logic:* `ADD`, `SUB`, `AND`, `OR`, `SLT`, `ADDI`, `ANDI`, `ORI`, `SLTI`
  - *Memory Movement:* `LW` (Load Word), `SW` (Store Word) with alignment trap checking
  - *Control Flow:* `BEQ` (Branch if Equal), `JAL` (Jump and Link with return address saving)
- **M-Extension (Integer Math):**
  - `MUL` (16-bit signed multiplication)
  - `DIV` (Signed division with `DIV by 0` returning `0xFFFF` / `-1`)
  - `REM` (Signed modulo with `REM by 0` returning operand `a`)
