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

---
| **Testbench & Verification** | [`main.cpp`](./main.cpp), `*.hex` | Authored machine code test suites (`program.hex`, `program_halt.hex`) and automated simulator runner verifying 100% ISA compliance. |
---
## 🧪 Verification & Test Suites Summary
The emulator is validated using two complementary machine-code test suites:
### 1. Primary Functional Benchmark (`program.hex`)
Tests the nominal instruction set end-to-end:
- **Math & Logic:** `ADDI`, `ADD`, `MUL`, `SUB`, `OR`, `DIV`, `AND`, `ORI`, `ANDI`, `REM`.
- **Signed Comparisons:** `SLT` ($5 < 21 \implies 1$), `SLTI` ($2 < 6 \implies 1$).
- **Data Memory:** Memory writeback with `SW R5, 0(R0)` and restoration via `LW R5, 0(R0)`.
- **Control Flow:** Backward loop branching with `BEQ` and forward jumping with `JAL` skipping dummy instructions.
### 2. Edge-Case & Alignment Trap Benchmark (`program_halt.hex`)
Validates hardware boundary rules and exception handling:
- **Division by Zero:** `DIV R2, R1, R0` safely returns `0xFFFF` (`-1`) without crashing.
- **Remainder by Zero:** `REM R3, R1, R0` safely returns dividend operand $a$ (`R1 = 25`).
- **`JAL` Linkage:** `JAL R4, 4` saves sequential return address ($PC + 2 = 8$) into non-zero register `R4`.
- **Strict Alignment Trap:** `SW R1, 1(R6)` attempts to store to unaligned odd address `17`, immediately halting the CPU (`HALTED = true`) and protecting subsequent instructions from executing.
---

## 📄 Documentation
- [`Zeus16 CPU Emulator.pdf`](./Zeus16%20CPU%20Emulator.pdf) .
