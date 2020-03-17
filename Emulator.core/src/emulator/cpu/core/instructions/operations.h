#ifndef __EMULATOR_CPU_CORE_INSTRUCTIONS_OPERATIONS__
#define __EMULATOR_CPU_CORE_INSTRUCTIONS_OPERATIONS__
#include "../CPU.h"

// Instruction: Add with Carry In
// Function:    A = A + M + C
// Flags Out:   C, V, N, Z
uint8_t cpu_instruction_operation_adc(CPU* cpu);

// Instruction: Subtraction with Borrow In
// Function:    A = A - M - (1 - C)
// Flags Out:   C, V, N, Z
uint8_t cpu_instruction_operation_sbc(CPU* cpu);

// Instruction: Bitwise Logic AND
// Function:    A = A & M
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_and(CPU* cpu);

// Instruction: Arithmetic Shift Left
// Function:    A = C <- (A << 1) <- 0
// Flags Out:   N, Z, C
uint8_t cpu_instruction_operation_asl(CPU* cpu);

// Instruction: Branch if Carry Clear
// Function:    if(C == 0) pc = address 
uint8_t cpu_instruction_operation_bcc(CPU* cpu);

// Instruction: Branch if Carry Set
// Function:    if(C == 1) pc = address
uint8_t cpu_instruction_operation_bcs(CPU* cpu);

// Instruction: Branch if Equal
// Function:    if(Z == 1) pc = address
uint8_t cpu_instruction_operation_beq(CPU* cpu);

// Instruction: Test Bits in Memory with Accumulator
// Function:    A AND M, M7 -> N, M6 -> V
uint8_t cpu_instruction_operation_bit(CPU* cpu);

// Instruction: Branch if Negative
// Function:    if(N == 1) pc = address
uint8_t cpu_instruction_operation_bmi(CPU* cpu);

// Instruction: Branch if Not Equal
// Function:    if(Z == 0) pc = addres
uint8_t cpu_instruction_operation_bne(CPU* cpu);

// Instruction: Branch if Positive
// Function:    if(N == 0) pc = address
uint8_t cpu_instruction_operation_bpl(CPU* cpu);

// Instruction: Break
// Function:    Program Sourced Interrupt
uint8_t cpu_instruction_operation_brk(CPU* cpu);

// Instruction: Branch if Overflow Clear
// Function:    if(V == 0) pc = address
uint8_t cpu_instruction_operation_bvc(CPU* cpu);

// Instruction: Branch if Overflow Set
// Function:    if(V == 1) pc = address
uint8_t cpu_instruction_operation_bvs(CPU* cpu);

// Instruction: Clear Carry Flag
// Function:    C = 0
uint8_t cpu_instruction_operation_clc(CPU* cpu);

// Instruction: Clear Decimal Flag
// Function:    D = 0
uint8_t cpu_instruction_operation_cld(CPU* cpu);

// Instruction: Disable Interrupts / Clear Interrupt Flag
// Function:    I = 0
uint8_t cpu_instruction_operation_cli(CPU* cpu);

// Instruction: Clear Overflow Flag
// Function:    V = 0
uint8_t cpu_instruction_operation_clv(CPU* cpu);

// Instruction: Compare Accumulator
// Function:    C <- A >= M      Z <- (A - M) == 0
// Flags Out:   N, C, Z
uint8_t cpu_instruction_operation_cmp(CPU* cpu);

// Instruction: Compare X Register
// Function:    C <- X >= M      Z <- (X - M) == 0
// Flags Out:   N, C, Z
uint8_t cpu_instruction_operation_cpx(CPU* cpu);

// Instruction: Compare Y Register
// Function:    C <- Y >= M      Z <- (Y - M) == 0
// Flags Out:   N, C, Z
uint8_t cpu_instruction_operation_cpy(CPU* cpu);

// Instruction: Decrement Value at Memory Location
// Function:    M = M - 1
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_dec(CPU* cpu);

// Instruction: Decrement X Register
// Function:    X = X - 1
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_dex(CPU* cpu);

// Instruction: Decrement Y Register
// Function:    Y = Y - 1
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_dey(CPU* cpu);

// Instruction: Bitwise Logic XOR
// Function:    A = A xor M
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_eor(CPU* cpu);

// Instruction: Increment Value at Memory Location
// Function:    M = M + 1
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_inc(CPU* cpu);

// Instruction: Increment X Register
// Function:    X = X + 1
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_inx(CPU* cpu);

// Instruction: Increment Y Register
// Function:    Y = Y + 1
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_iny(CPU* cpu);

// Instruction: Jump To Location
// Function:    pc = address
uint8_t cpu_instruction_operation_jmp(CPU* cpu);

// Instruction: Jump To Sub-Routine
// Function:    Push current pc to stack, pc = address
uint8_t cpu_instruction_operation_jsr(CPU* cpu);

// Instruction: Load The Accumulator
// Function:    A = M
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_lda(CPU* cpu);

// Instruction: Load The X Register
// Function:    X = M
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_ldx(CPU* cpu);

// Instruction: Load The Y Register
// Function:    Y = M
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_ldy(CPU* cpu);

// Instruction: Shift One Bit Right (Memory or Accumulator)
// Function:    0 -> [76543210] -> C
uint8_t cpu_instruction_operation_lsr(CPU* cpu);

// Instruction: No Operation
uint8_t cpu_instruction_operation_nop(CPU* cpu);

// Instruction: Bitwise Logic OR
// Function:    A = A | M
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_ora(CPU* cpu);

// Instruction: Push Accumulator to Stack
// Function:    A -> stack
uint8_t cpu_instruction_operation_pha(CPU* cpu);

// Instruction: Push Status Register to Stack
// Function:    status -> stack
// Note:        Break flag is set to 1 before push
uint8_t cpu_instruction_operation_php(CPU* cpu);

// Instruction: Pop Accumulator off Stack
// Function:    A <- stack
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_pla(CPU* cpu);

// Instruction: Pop Status Register off Stack
// Function:    Status <- stack
uint8_t cpu_instruction_operation_plp(CPU* cpu);

// Instruction: Rotate One Bit Left (Memory or Accumulator)
// C <- [76543210] <- C
uint8_t cpu_instruction_operation_rol(CPU* cpu);

// Instruction: Rotate One Bit Right (Memory or Accumulator)
// C -> [76543210] -> C
uint8_t cpu_instruction_operation_ror(CPU* cpu);

// Instruction: Return from Interrupt
// Function:    pull SR, pull PC
uint8_t cpu_instruction_operation_rti(CPU* cpu);

// Instruction: Return from Subroutine
// Function:    pull PC, PC+1 -> PC
uint8_t cpu_instruction_operation_rts(CPU* cpu);

// Instruction: Set Carry Flag
// Function:    C = 1
uint8_t cpu_instruction_operation_sec(CPU* cpu);

// Instruction: Set Decimal Flag
// Function:    D = 1
uint8_t cpu_instruction_operation_sed(CPU* cpu);

// Instruction: Set Interrupt Flag / Enable Interrupts
// Function:    I = 1
uint8_t cpu_instruction_operation_sei(CPU* cpu);

// Instruction: Store Accumulator at Address
// Function:    M = A
uint8_t cpu_instruction_operation_sta(CPU* cpu);

// Instruction: Store X Register at Address
// Function:    M = X
uint8_t cpu_instruction_operation_stx(CPU* cpu);

// Instruction: Store Y Register at Address
// Function:    M = Y
uint8_t cpu_instruction_operation_sty(CPU* cpu);

// Instruction: Transfer Accumulator to X Register
// Function:    X = A
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_tax(CPU* cpu);

// Instruction: Transfer Accumulator to Y Register
// Function:    Y = A
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_tay(CPU* cpu);

// Instruction: Transfer Stack Pointer to X Register
// Function:    X = stack pointer
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_tsx(CPU* cpu);

// Instruction: Transfer X Register to Accumulator
// Function:    A = X
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_txa(CPU* cpu);

// Instruction: Transfer X Register to Stack Pointer
// Function:    stack pointer = X
uint8_t cpu_instruction_operation_txs(CPU* cpu);

// Instruction: Transfer Y Register to Accumulator
// Function:    A = Y
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_tya(CPU* cpu);

// This function captures illegal opcodes
uint8_t cpu_instruction_operation_xxx(CPU* cpu);

#endif