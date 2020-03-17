#ifndef __EMULATOR_CPU_CORE_INSTRUCTIONS_ADDRESSING_H__
#define __EMULATOR_CPU_CORE_INSTRUCTIONS_ADDRESSING_H__
#include "../CPU.h"

// Address Mode: Implied
// There is no additional data required for this instruction. The instruction
// does something very simple like like sets a status bit. However, we will
// target the accumulator, for instructions like PHA
uint8_t cpu_instruction_addressing_imp(CPU* core);

// Address Mode: Immediate
// The instruction expects the next byte to be used as a value, so we'll prep
// the read address to point to the next byte
uint8_t cpu_instruction_addressing_imm(CPU* core);

// Address Mode: Zero Page
// To save program bytes, zero page addressing allows you to absolutely address
// a location in first 0xFF bytes of address range. Clearly this only requires
// one byte instead of the usual two.
uint8_t cpu_instruction_addressing_zp0(CPU* core);

// Address Mode: Zero Page with X Offset
// Fundamentally the same as Zero Page addressing, but the contents of the X Register
// is added to the supplied single byte address. This is useful for iterating through
// ranges within the first page.
uint8_t cpu_instruction_addressing_zpx(CPU* core);

// Address Mode: Zero Page with Y Offset
// Fundamentally the same as Zero Page addressing, but the contents of the Y Register
// is added to the supplied single byte address. This is useful for iterating through
// ranges within the first page.
uint8_t cpu_instruction_addressing_zpy(CPU* core);

// Address Mode: Relative
// This address mode is exclusive to branch instructions. The address
// must reside within -128 to +127 of the branch instruction, i.e.
// you cant directly branch to any address in the addressable range.
uint8_t cpu_instruction_addressing_rel(CPU* core);

// Address Mode: Absolute 
// A full 16-bit address is loaded and used
uint8_t cpu_instruction_addressing_abs(CPU* core);

// Address Mode: Absolute with X Offset
// Fundamentally the same as absolute addressing, but the contents of the X Register
// is added to the supplied two byte address. If the resulting address changes
// the page, an additional clock cycle is required
uint8_t cpu_instruction_addressing_abx(CPU* core);

// Address Mode: Absolute with Y Offset
// Fundamentally the same as absolute addressing, but the contents of the Y Register
// is added to the supplied two byte address. If the resulting address changes
// the page, an additional clock cycle is required
uint8_t cpu_instruction_addressing_aby(CPU* core);

// Address Mode: Indirect
// The supplied 16-bit address is read to get the actual 16-bit address. This is
// instruction is unusual in that it has a bug in the hardware! To emulate its
// function accurately, we also need to emulate this bug. If the low byte of the
// supplied address is 0xFF, then to read the high byte of the actual address
// we need to cross a page boundary. This doesnt actually work on the chip as 
// designed, instead it wraps back around in the same page, yielding an 
// invalid actual address
uint8_t cpu_instruction_addressing_ind(CPU* core);

// Address Mode: Indirect X
// The supplied 8-bit address is offset by X Register to index
// a location in page 0x00. The actual 16-bit address is read 
// from this location
uint8_t cpu_instruction_addressing_izx(CPU* core);

// Address Mode: Indirect Y
// The supplied 8-bit address indexes a location in page 0x00. From 
// here the actual 16-bit address is read, and the contents of
// Y Register is added to it to offset it. If the offset causes a
// change in page then an additional clock cycle is required.
uint8_t cpu_instruction_addressing_izy(CPU* core);

#endif
