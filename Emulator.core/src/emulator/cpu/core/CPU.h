#ifndef __EMULATOR_CPU_CORE_CPU_H__
#define __EMULATOR_CPU_CORE_CPU_H__

#include "Registery.h"
#include "settings.h"
#include "../bus/Bus.h"

typedef struct cpu {
	Registery * registery;
	uint8_t alu; // Represents the working input value to the ALU
	uint16_t temp; // A convenience variable used everywhere
	uint16_t addr_abs; // All used memory addresses end up in here
	uint16_t addr_rel; // Represents absolute address following a branch
	uint8_t opt_code; // Is the instruction byte
	uint8_t cycles; // Counts how many cycles the instruction has remaining
#ifdef COUNT_CYCLES
	uint64_t clock_count; //  global accumulation of the number of clocks
#endif
	Bus* bus;
} CPU;

CPU* cpu_init();

void cpu_destroy(CPU* cpu);

void cpu_status_set(const CPU* cpu, flag flag, bool value);

bool cpu_status_get(const CPU* cpu, flag flag);

uint8_t cpu_bus_read(const CPU* cpu, uint16_t address);

void cpu_bus_write(const CPU* cpu, uint16_t address, uint8_t value);

uint8_t cpu_bus_read_pc(const CPU* cpu);

void cpu_stack_push(const CPU* cpu, uint8_t value);

uint8_t cpu_stack_pop(const CPU* cpu);

// Reset Interrupt - Forces CPU into known state
//
// in core, the core to send the reset interrupt
void cpu_signal_reset(CPU* cpu);

// Interrupt Request - Executes an instruction at a specific location
//
// in core, the core to send the interrupt request
void cpu_signal_irq(CPU* cpu);

// Non-Maskable Interrupt Request - Executes an instruction at a specific
// location, but cannot be disabled
//
// in core, the core to send the interrupt request
void cpu_signal_nmi(CPU* cpu);

// Perform one clock cycle's worth of update
//
// in core, the core to tick
void cpu_clock(CPU* cpu);

bool cpu_clock_complete(const CPU* cpu);

#endif
