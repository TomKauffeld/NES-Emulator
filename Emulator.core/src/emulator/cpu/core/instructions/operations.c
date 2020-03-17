#include "operations.h"
#include "addressing.h"
#include "cpu_instructions.h"
#include "../settings.h"

// helper function
// fetches the value from the bus into the alu
void fetch(CPU* cpu)
{
	if (!(lookup[cpu->opt_code].addr_mode == &cpu_instruction_addressing_imp))
		cpu->alu = cpu_bus_read(cpu, cpu->addr_abs);
}

// Instruction: Add with Carry In
// Function:    A = A + M + C
// Flags Out:   C, V, N, Z
uint8_t cpu_instruction_operation_adc(CPU* cpu)
{
	fetch(cpu);
	cpu->temp = (uint16_t)cpu->registery->a + (uint16_t)cpu->alu;
	if (cpu_status_get(cpu, FLAG_C) == TRUE)
		cpu->temp += 1;
	cpu_status_set(cpu, FLAG_C, cpu->temp > 255);
	cpu_status_set(cpu, FLAG_Z, (cpu->temp & 0x00ff) == 0);
	cpu_status_set(cpu, FLAG_V, (~((uint16_t)cpu->registery->a ^ (uint16_t)cpu->alu) & ((uint16_t)cpu->registery->a ^ (uint16_t)cpu->temp)) & 0x0080);
	cpu_status_set(cpu, FLAG_N, cpu->temp & 0x80);
	cpu->registery->a = cpu->temp & 0x00ff;
	return 1;
}

// Instruction: Subtraction with Borrow In
// Function:    A = A - M - (1 - C)
// Flags Out:   C, V, N, Z
uint8_t cpu_instruction_operation_sbc(CPU* cpu)
{
	fetch(cpu);
	uint16_t value = ((uint16_t)cpu->alu) ^ 0x00ff;
	cpu->temp = (uint16_t)cpu->registery->a + (uint16_t)value;
	if (cpu_status_get(cpu, FLAG_C) == TRUE)
		cpu->temp += 1;
	cpu_status_set(cpu, FLAG_C, cpu->temp & 0xff00);
	cpu_status_set(cpu, FLAG_Z, (cpu->temp & 0x00ff) == 0);
	cpu_status_set(cpu, FLAG_V, (cpu->temp ^ (uint16_t)cpu->registery->a) & (cpu->temp ^ value) & 0x0080);
	cpu_status_set(cpu, FLAG_N, cpu->temp & 0x80);
	cpu->registery->a = cpu->temp & 0x00ff;
	return 1;
}

// Instruction: Bitwise Logic AND
// Function:    A = A & M
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_and(CPU* cpu)
{
	fetch(cpu);
	cpu->registery->a &= cpu->alu;
	cpu_status_set(cpu, FLAG_Z, cpu->registery->a == 0x00);
	cpu_status_set(cpu, FLAG_N, cpu->registery->a & 0x80);
	return 1;
}

// Instruction: Arithmetic Shift Left
// Function:    A = C <- (A << 1) <- 0
// Flags Out:   N, Z, C
uint8_t cpu_instruction_operation_asl(CPU* cpu)
{
	fetch(cpu);
	cpu->temp = ((uint16_t)cpu->alu) << 1;
	cpu_status_set(cpu, FLAG_C, (cpu->temp & 0xff00) > 0);
	cpu_status_set(cpu, FLAG_Z, (cpu->temp & 0x00ff) == 0x0000);
	cpu_status_set(cpu, FLAG_N, cpu->temp & 0x0080);
	if (lookup[cpu->opt_code].addr_mode == &cpu_instruction_addressing_imp)
		cpu->registery->a = cpu->temp & 0x00ff;
	else
		cpu_bus_write(cpu, cpu->addr_abs, cpu->temp & 0x00ff);
	return 0;

}

// Instruction: Branch if Carry Clear
// Function:    if(C == 0) pc = address 
uint8_t cpu_instruction_operation_bcc(CPU* cpu)
{
	if (cpu_status_get(cpu, FLAG_C) != FALSE)
		return 0;
	cpu->cycles++;
	cpu->addr_abs = cpu->registery->pc + cpu->addr_rel;
	if ((cpu->addr_abs & 0xff00) != (cpu->registery->pc & 0xff00))
		cpu->cycles++;
	cpu->registery->pc = cpu->addr_abs;
	return 0;
}

// Instruction: Branch if Carry Set
// Function:    if(C == 1) pc = address
uint8_t cpu_instruction_operation_bcs(CPU* cpu)
{
	if (cpu_status_get(cpu, FLAG_C) == FALSE)
		return 0;
	cpu->cycles++;
	cpu->addr_abs = cpu->registery->pc + cpu->addr_rel;
	if ((cpu->addr_abs & 0xff00) != (cpu->registery->pc & 0xff00))
		cpu->cycles++;
	cpu->registery->pc = cpu->addr_abs;
	return 0;
}

// Instruction: Branch if Equal
// Function:    if(Z == 1) pc = address
uint8_t cpu_instruction_operation_beq(CPU* cpu)
{
	if (cpu_status_get(cpu, FLAG_Z) == FALSE)
		return 0;
	cpu->cycles++;
	cpu->addr_abs = cpu->registery->pc + cpu->addr_rel;
	if ((cpu->addr_abs & 0xff00) != (cpu->registery->pc & 0xff00))
		cpu->cycles++;
	cpu->registery->pc = cpu->addr_abs;
	return 0;
}

// Instruction: Test Bits in Memory with Accumulator
// Function:    A AND M, M7 -> N, M6 -> V
uint8_t cpu_instruction_operation_bit(CPU* cpu)
{
	fetch(cpu);
	cpu->temp = cpu->registery->a & cpu->alu;
	cpu_status_set(cpu, FLAG_Z, (cpu->temp & 0x00ff) == 0x0000);
	cpu_status_set(cpu, FLAG_N, cpu->alu & (1 << 7));
	cpu_status_set(cpu, FLAG_V, cpu->alu & (1 << 6));
	return 0;
}

// Instruction: Branch if Negative
// Function:    if(N == 1) pc = address
uint8_t cpu_instruction_operation_bmi(CPU* cpu)
{
	if (cpu_status_get(cpu, FLAG_N) == FALSE)
		return 0;
	cpu->cycles++;
	cpu->addr_abs = cpu->registery->pc + cpu->addr_rel;
	if ((cpu->addr_abs & 0xff00) != (cpu->registery->pc & 0xff00))
		cpu->cycles++;
	cpu->registery->pc = cpu->addr_abs;
	return 0;
}

// Instruction: Branch if Not Equal
// Function:    if(Z == 0) pc = addres
uint8_t cpu_instruction_operation_bne(CPU* cpu)
{
	if (cpu_status_get(cpu, FLAG_Z) != FALSE)
		return 0;
	cpu->cycles++;
	cpu->addr_abs = cpu->registery->pc + cpu->addr_rel;
	if ((cpu->addr_abs & 0xff00) != (cpu->registery->pc & 0xff00))
		cpu->cycles++;
	cpu->registery->pc = cpu->addr_abs;
	return 0;
}

// Instruction: Branch if Not Equal
// Function:    if(Z == 0) pc = address
uint8_t cpu_instruction_operation_bpl(CPU* cpu)
{
	if (cpu_status_get(cpu, FLAG_N) != FALSE)
		return 0;
	cpu->cycles++;
	cpu->addr_abs = cpu->registery->pc + cpu->addr_rel;
	if ((cpu->addr_abs & 0xff00) != (cpu->registery->pc & 0xff00))
		cpu->cycles++;
	cpu->registery->pc = cpu->addr_abs;
	return 0;
}

// Instruction: Break
// Function:    Program Sourced Interrupt
uint8_t cpu_instruction_operation_brk(CPU* cpu)
{
	cpu->registery->pc++;
	cpu_status_set(cpu, FLAG_I, TRUE);
	cpu_stack_push(cpu, (cpu->registery->pc >> 8) & 0x00ff);
	cpu_stack_push(cpu, cpu->registery->pc & 0x00ff);
	cpu_status_set(cpu, FLAG_B, TRUE);
	cpu_stack_push(cpu, cpu->registery->s);
	cpu_status_set(cpu, FLAG_B, FALSE);
	uint16_t lo = cpu_bus_read(cpu, IRQ_ADDRESS);
	uint16_t hi = cpu_bus_read(cpu, IRQ_ADDRESS + 1);
	cpu->registery->pc = (hi << 8) | lo;
	return 0;
}

// Instruction: Branch if Overflow Clear
// Function:    if(V == 0) pc = address
uint8_t cpu_instruction_operation_bvc(CPU* cpu)
{
	if (cpu_status_get(cpu, FLAG_V) != FALSE)
		return 0;
	cpu->cycles++;
	cpu->addr_abs = cpu->registery->pc + cpu->addr_rel;
	if ((cpu->addr_abs & 0xff00) != (cpu->registery->pc & 0xff00))
		cpu->cycles++;
	cpu->registery->pc = cpu->addr_abs;
	return 0;
}

// Instruction: Branch if Overflow Set
// Function:    if(V == 1) pc = address
uint8_t cpu_instruction_operation_bvs(CPU* cpu)
{
	if (cpu_status_get(cpu, FLAG_V) == FALSE)
		return 0;
	cpu->cycles++;
	cpu->addr_abs = cpu->registery->pc + cpu->addr_rel;
	if ((cpu->addr_abs & 0xff00) != (cpu->registery->pc & 0xff00))
		cpu->cycles++;
	cpu->registery->pc = cpu->addr_abs;
	return 0;
}

// Instruction: Clear Carry Flag
// Function:    C = 0
uint8_t cpu_instruction_operation_clc(CPU* cpu)
{
	cpu_status_set(cpu, FLAG_C, FALSE);
	return 0;
}

// Instruction: Clear Decimal Flag
// Function:    D = 0
uint8_t cpu_instruction_operation_cld(CPU* cpu)
{
	cpu_status_set(cpu, FLAG_D, FALSE);
	return 0;
}

// Instruction: Disable Interrupts / Clear Interrupt Flag
// Function:    I = 0
uint8_t cpu_instruction_operation_cli(CPU* cpu)
{
	cpu_status_set(cpu, FLAG_I, FALSE);
	return 0;
}

// Instruction: Clear Overflow Flag
// Function:    V = 0
uint8_t cpu_instruction_operation_clv(CPU* cpu)
{
	cpu_status_set(cpu, FLAG_V, FALSE);
	return 0;
}

// Instruction: Compare Accumulator
// Function:    C <- A >= M      Z <- (A - M) == 0
// Flags Out:   N, C, Z
uint8_t cpu_instruction_operation_cmp(CPU* cpu)
{
	fetch(cpu);
	cpu->temp = cpu->registery->a;
	cpu->temp -= cpu->alu;
	cpu_status_set(cpu, FLAG_C, cpu->registery->a >= cpu->alu);
	cpu_status_set(cpu, FLAG_Z, (cpu->temp & 0x00ff) == 0x0000);
	cpu_status_set(cpu, FLAG_N, cpu->temp & 0x0080);
	return 1;
}

// Instruction: Compare X Register
// Function:    C <- X >= M      Z <- (X - M) == 0
// Flags Out:   N, C, Z
uint8_t cpu_instruction_operation_cpx(CPU* cpu)
{
	fetch(cpu);
	cpu->temp = cpu->registery->x;
	cpu->temp -= cpu->alu;
	cpu_status_set(cpu, FLAG_C, cpu->registery->x >= cpu->alu);
	cpu_status_set(cpu, FLAG_Z, (cpu->temp & 0x00ff) == 0x0000);
	cpu_status_set(cpu, FLAG_N, cpu->temp & 0x0080);
	return 0;
}

// Instruction: Compare Y Register
// Function:    C <- Y >= M      Z <- (Y - M) == 0
// Flags Out:   N, C, Z
uint8_t cpu_instruction_operation_cpy(CPU* cpu)
{
	fetch(cpu);
	cpu->temp = cpu->registery->y;
	cpu->temp -= cpu->alu;
	cpu_status_set(cpu, FLAG_C, cpu->registery->y >= cpu->alu);
	cpu_status_set(cpu, FLAG_Z, (cpu->temp & 0x00ff) == 0x0000);
	cpu_status_set(cpu, FLAG_N, cpu->temp & 0x0080);
	return 0;
}

// Instruction: Decrement Value at Memory Location
// Function:    M = M - 1
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_dec(CPU* cpu)
{
	fetch(cpu);
	cpu->temp = cpu->alu - 1;
	cpu_bus_write(cpu, cpu->addr_abs, cpu->temp & 0x00ff);
	cpu_status_set(cpu, FLAG_Z, (cpu->temp & 0x00ff) == 0x0000);
	cpu_status_set(cpu, FLAG_N, cpu->temp & 0x0080);
	return 0;
}

// Instruction: Decrement X Register
// Function:    X = X - 1
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_dex(CPU* cpu)
{
	cpu->registery->x--;
	cpu_status_set(cpu, FLAG_Z, cpu->registery->x == 0x00);
	cpu_status_set(cpu, FLAG_N, cpu->registery->x & 0x80);
	return 0;
}

// Instruction: Decrement Y Register
// Function:    Y = Y - 1
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_dey(CPU* cpu)
{
	cpu->registery->y--;
	cpu_status_set(cpu, FLAG_Z, cpu->registery->y == 0x00);
	cpu_status_set(cpu, FLAG_N, cpu->registery->y & 0x80);
	return 0;
}

// Instruction: Bitwise Logic XOR
// Function:    A = A xor M
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_eor(CPU* cpu)
{
	fetch(cpu);
	cpu->registery->a ^= cpu->alu;
	cpu_status_set(cpu, FLAG_Z, cpu->registery->a == 0x00);
	cpu_status_set(cpu, FLAG_N, cpu->registery->a & 0x80);
	return 1;

}

// Instruction: Increment Value at Memory Location
// Function:    M = M + 1
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_inc(CPU* cpu)
{
	fetch(cpu);
	cpu->temp = cpu->alu + 1;
	cpu_bus_write(cpu, cpu->addr_abs, cpu->temp & 0x00ff);
	cpu_status_set(cpu, FLAG_Z, (cpu->temp & 0x00ff) == 0x0000);
	cpu_status_set(cpu, FLAG_N, cpu->temp & 0x0080);
	return 0;
}

// Instruction: Increment X Register
// Function:    X = X + 1
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_inx(CPU* cpu)
{
	cpu->registery->x++;
	cpu_status_set(cpu, FLAG_Z, cpu->registery->x == 0x00);
	cpu_status_set(cpu, FLAG_N, cpu->registery->x & 0x80);
	return 0;
}

// Instruction: Increment Y Register
// Function:    Y = Y + 1
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_iny(CPU* cpu)
{
	cpu->registery->y++;
	cpu_status_set(cpu, FLAG_Z, cpu->registery->y == 0x00);
	cpu_status_set(cpu, FLAG_N, cpu->registery->y & 0x80);
	return 0;
}

// Instruction: Jump To Location
// Function:    pc = address
uint8_t cpu_instruction_operation_jmp(CPU* cpu)
{
	cpu->registery->pc = cpu->addr_abs;
	return 0;
}

// Instruction: Jump To Sub-Routine
// Function:    Push current pc to stack, pc = address
uint8_t cpu_instruction_operation_jsr(CPU* cpu)
{
	cpu->registery->pc--;
	cpu_stack_push(cpu, (cpu->registery->pc >> 8) & 0x00ff);
	cpu_stack_push(cpu, cpu->registery->pc & 0x00ff);
	cpu->registery->pc = cpu->addr_abs;
	return 0;
}

// Instruction: Load The Accumulator
// Function:    A = M
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_lda(CPU* cpu)
{
	fetch(cpu);
	cpu->registery->a = cpu->alu;
	cpu_status_set(cpu, FLAG_Z, cpu->registery->a == 0x00);
	cpu_status_set(cpu, FLAG_N, cpu->registery->a & 0x80);
	return 1;
}

// Instruction: Load The X Register
// Function:    X = M
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_ldx(CPU* cpu)
{
	fetch(cpu);
	cpu->registery->x = cpu->alu;
	cpu_status_set(cpu, FLAG_Z, cpu->registery->x == 0x00);
	cpu_status_set(cpu, FLAG_N, cpu->registery->x & 0x80);
	return 1;
}

// Instruction: Load The Y Register
// Function:    Y = M
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_ldy(CPU* cpu)
{
	fetch(cpu);
	cpu->registery->y = cpu->alu;
	cpu_status_set(cpu, FLAG_Z, cpu->registery->y == 0x00);
	cpu_status_set(cpu, FLAG_N, cpu->registery->y & 0x80);
	return 1;
}

// Instruction: Shift One Bit Right (Memory or Accumulator)
// Function:    0 -> [76543210] -> C
uint8_t cpu_instruction_operation_lsr(CPU* cpu)
{
	fetch(cpu);
	cpu_status_set(cpu, FLAG_C, cpu->alu & 0x0001);
	cpu->temp = cpu->alu >> 1;
	cpu_status_set(cpu, FLAG_Z, (cpu->temp & 0x00ff) == 0x0000);
	cpu_status_set(cpu, FLAG_N, cpu->temp & 0x0080);
	if (lookup[cpu->opt_code].addr_mode == &cpu_instruction_addressing_imp)
		cpu->registery->a = cpu->temp & 0x00ff;
	else
		cpu_bus_write(cpu, cpu->addr_abs, cpu->temp & 0x00ff);
	return 0;
}

// Instruction: No Operation
uint8_t cpu_instruction_operation_nop(CPU* cpu)
{
	switch (cpu->opt_code) {
	case 0x1C:
	case 0x3C:
	case 0x5C:
	case 0x7C:
	case 0xDC:
	case 0xFC:
		return 1;
	}
	return 0;
}

// Instruction: Bitwise Logic OR
// Function:    A = A | M
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_ora(CPU* cpu)
{
	fetch(cpu);
	cpu->registery->a |= cpu->alu;
	cpu_status_set(cpu, FLAG_Z, cpu->registery->a == 0x00);
	cpu_status_set(cpu, FLAG_N, cpu->registery->a & 0x80);
	return 1;
}

// Instruction: Push Accumulator to Stack
// Function:    A -> stack
uint8_t cpu_instruction_operation_pha(CPU* cpu)
{
	cpu_stack_push(cpu, cpu->registery->a);
	return 0;
}

// Instruction: Push Status Register to Stack
// Function:    status -> stack
// Note:        Break flag is set to 1 before push
uint8_t cpu_instruction_operation_php(CPU* cpu)
{
	cpu_bus_write(cpu, STACK_POSITION_START + cpu->registery->sp, cpu->registery->s | FLAG_B | FLAG_U);
	cpu_status_set(cpu, FLAG_B, FALSE);
	cpu_status_set(cpu, FLAG_U, FALSE);
	cpu->registery->sp--;
	return 0;
}

// Instruction: Pop Accumulator off Stack
// Function:    A <- stack
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_pla(CPU* cpu)
{
	cpu->registery->a = cpu_stack_pop(cpu);
	cpu_status_set(cpu, FLAG_U, TRUE);
	cpu_status_set(cpu, FLAG_Z, cpu->registery->a == 0x00);
	cpu_status_set(cpu, FLAG_N, cpu->registery->a & 0x80);
	return 0;
}

// Instruction: Pop Status Register off Stack
// Function:    Status <- stack
uint8_t cpu_instruction_operation_plp(CPU* cpu)
{
	cpu->registery->s = cpu_stack_pop(cpu);
	cpu_status_set(cpu, FLAG_U, TRUE);
	return 0;
}

// Instruction: Rotate One Bit Left (Memory or Accumulator)
// C <- [76543210] <- C
uint8_t cpu_instruction_operation_rol(CPU* cpu)
{
	fetch(cpu);
	cpu->temp = cpu->alu << 1;
	if (cpu_status_get(cpu, FLAG_C) == TRUE)
		cpu->temp |= 0x01;
	cpu_status_set(cpu, FLAG_C, cpu->temp & 0xff00);
	cpu_status_set(cpu, FLAG_Z, (cpu->temp & 0x00ff) == 0x00);
	cpu_status_set(cpu, FLAG_N, cpu->temp & 0x0080);
	if (lookup[cpu->opt_code].addr_mode == &cpu_instruction_addressing_imp)
		cpu->registery->a = cpu->temp & 0x00ff;
	else
		cpu_bus_write(cpu, cpu->addr_abs, cpu->temp & 0x00ff);
	return 0;
}

// Instruction: Rotate One Bit Right (Memory or Accumulator)
// C -> [76543210] -> C
uint8_t cpu_instruction_operation_ror(CPU* cpu)
{
	fetch(cpu);
	cpu->temp = cpu->alu >> 1;
	if (cpu_status_get(cpu, FLAG_C) == TRUE)
		cpu->temp |= 0x0080;
	cpu_status_set(cpu, FLAG_C, cpu->alu & 0x01);
	cpu_status_set(cpu, FLAG_Z, (cpu->temp & 0x00ff) == 0x00);
	cpu_status_set(cpu, FLAG_N, cpu->temp & 0x0080);
	if (lookup[cpu->opt_code].addr_mode == &cpu_instruction_addressing_imp)
		cpu->registery->a = cpu->temp & 0x00ff;
	else
		cpu_bus_write(cpu, cpu->addr_abs, cpu->temp & 0x00ff);
	return 0;
}

// Instruction: Return from Interrupt
// Function:    pull SR, pull PC
uint8_t cpu_instruction_operation_rti(CPU* cpu)
{
	cpu->registery->s = cpu_stack_pop(cpu);
	cpu->registery->s &= ~FLAG_B;
	cpu->registery->s &= ~FLAG_U;
	cpu->registery->pc = cpu_stack_pop(cpu);
	cpu->registery->pc |= cpu_stack_pop(cpu) << 8;
	cpu->registery->pc++;
	return 0;
}

// Instruction: Return from Subroutine
// Function:    pull PC, PC+1 -> PC
uint8_t cpu_instruction_operation_rts(CPU* cpu)
{
	cpu->registery->pc = cpu_stack_pop(cpu);
	cpu->registery->pc |= cpu_stack_pop(cpu) << 8;
	cpu->registery->pc++;
	return 0;
}

// Instruction: Set Carry Flag
// Function:    C = 1
uint8_t cpu_instruction_operation_sec(CPU* cpu)
{
	cpu_status_set(cpu, FLAG_C, TRUE);
	return 0;
}

// Instruction: Set Decimal Flag
// Function:    D = 1
uint8_t cpu_instruction_operation_sed(CPU* cpu)
{
	cpu_status_set(cpu, FLAG_D, TRUE);
	return 0;
}

// Instruction: Set Interrupt Flag / Enable Interrupts
// Function:    I = 1
uint8_t cpu_instruction_operation_sei(CPU* cpu)
{
	cpu_status_set(cpu, FLAG_I, TRUE);
	return 0;
}

// Instruction: Store Accumulator at Address
// Function:    M = A
uint8_t cpu_instruction_operation_sta(CPU* cpu)
{
	cpu_bus_write(cpu, cpu->addr_abs, cpu->registery->a);
	return 0;
}

// Instruction: Store X Register at Address
// Function:    M = X
uint8_t cpu_instruction_operation_stx(CPU* cpu)
{
	cpu_bus_write(cpu, cpu->addr_abs, cpu->registery->x);
	return 0;
}

// Instruction: Store Y Register at Address
// Function:    M = Y
uint8_t cpu_instruction_operation_sty(CPU* cpu)
{
	cpu_bus_write(cpu, cpu->addr_abs, cpu->registery->y);
	return 0;
}

// Instruction: Transfer Accumulator to X Register
// Function:    X = A
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_tax(CPU* cpu)
{
	cpu->registery->x = cpu->registery->a;
	cpu_status_set(cpu, FLAG_Z, cpu->registery->x == 0x00);
	cpu_status_set(cpu, FLAG_N, cpu->registery->x & 0x80);
	return 0;
}

// Instruction: Transfer Accumulator to Y Register
// Function:    Y = A
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_tay(CPU* cpu)
{
	cpu->registery->y = cpu->registery->a;
	cpu_status_set(cpu, FLAG_Z, cpu->registery->y == 0x00);
	cpu_status_set(cpu, FLAG_N, cpu->registery->y & 0x80);
	return 0;
}

// Instruction: Transfer Stack Pointer to X Register
// Function:    X = stack pointer
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_tsx(CPU* cpu)
{
	cpu->registery->x = cpu->registery->sp;
	cpu_status_set(cpu, FLAG_Z, cpu->registery->x == 0x00);
	cpu_status_set(cpu, FLAG_N, cpu->registery->x & 0x80);
	return 0;
}

// Instruction: Transfer X Register to Accumulator
// Function:    A = X
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_txa(CPU* cpu)
{
	cpu->registery->a = cpu->registery->x;
	cpu_status_set(cpu, FLAG_Z, cpu->registery->a == 0x00);
	cpu_status_set(cpu, FLAG_N, cpu->registery->a & 0x80);
	return 0;
}

// Instruction: Transfer X Register to Stack Pointer
// Function:    stack pointer = X
uint8_t cpu_instruction_operation_txs(CPU* cpu)
{
	cpu->registery->sp = cpu->registery->x;
	return 0;
}

// Instruction: Transfer Y Register to Accumulator
// Function:    A = Y
// Flags Out:   N, Z
uint8_t cpu_instruction_operation_tya(CPU* cpu)
{
	cpu->registery->a = cpu->registery->y;
	cpu_status_set(cpu, FLAG_Z, cpu->registery->a == 0x00);
	cpu_status_set(cpu, FLAG_N, cpu->registery->a & 0x80);
	return 0;
}

// This function captures illegal opcodes
uint8_t cpu_instruction_operation_xxx(CPU* cpu)
{
	return 0;
}
