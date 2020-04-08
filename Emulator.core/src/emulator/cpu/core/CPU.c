#include "CPU.h"
#include "instructions/cpu_instructions.h"

#include <stdlib.h>
#include <string.h>


CPU* cpu_init()
{
	CPU* cpu = (CPU*)malloc(sizeof(CPU));
	if (cpu == NULL)
		return NULL;

	memset(cpu, 0x00, sizeof(CPU));

	cpu->registery = registery_init();
	if (cpu->registery == NULL)
	{
		free(cpu);
		return NULL;
	}
	cpu->bus = bus_init();
	if (cpu->bus == NULL) {
		registery_destroy(cpu->registery);
		free(cpu);
		return NULL;
	}

	cpu->registery->sp = STACK_POINTER_INIT;

	return cpu;
}

void cpu_destroy(CPU* cpu)
{
	if (cpu == NULL)
		return;
	bus_destroy(cpu->bus);
	registery_destroy(cpu->registery);
	free(cpu);
}

void cpu_status_set(const CPU* cpu, flag flag, bool value)
{
	status_set(cpu->registery, flag, value);
}

bool cpu_status_get(const CPU* cpu, flag flag)
{
	return status_get(cpu->registery, flag);
}

uint8_t cpu_bus_read(const CPU* cpu, uint16_t address)
{
	return bus_read(cpu->bus, address);
}

void cpu_bus_write(const CPU* cpu, uint16_t address, uint8_t value)
{
	bus_write(cpu->bus, address, value);
}

uint8_t cpu_bus_read_pc(const CPU* cpu)
{
	uint8_t value = cpu_bus_read(cpu, cpu->registery->pc);
	cpu->registery->pc++;
	return value;
}

void cpu_stack_push(const CPU* cpu, uint8_t value)
{
	cpu_bus_write(cpu, STACK_POSITION_START + cpu->registery->sp, value);
	cpu->registery->sp--;
}

uint8_t cpu_stack_pop(const CPU* cpu)
{
	cpu->registery->sp++;
	uint8_t value = cpu_bus_read(cpu, STACK_POSITION_START + cpu->registery->sp);
	return value;
}


// Reset Interrupt - Forces CPU into known state
//
// in core, the core to send the reset interrupt
void cpu_signal_reset(CPU* cpu)
{
	cpu->addr_abs = RESET_ADDRESS;
	uint16_t lo = cpu_bus_read(cpu, cpu->addr_abs);
	uint16_t hi = cpu_bus_read(cpu, cpu->addr_abs + 1);

	cpu->registery->pc = (hi << 8) | lo;
	cpu->registery->a = 0x00;
	cpu->registery->x = 0x00;
	cpu->registery->y = 0x00;
	cpu->registery->sp = STACK_POINTER_INIT;
	cpu->registery->s = 0x00 | FLAG_U;

	cpu->addr_rel = 0x0000;
	cpu->addr_abs = 0x0000;
	cpu->alu = 0x00;
	cpu->cycles = 0x00;
}

// Interrupt Request - Executes an instruction at a specific location
//
// in core, the core to send the interrupt request
void cpu_signal_irq(CPU* cpu)
{
	if (cpu_status_get(cpu, FLAG_I) == TRUE)
		return;
	cpu_stack_push(cpu, (cpu->registery->pc >> 8) & 0x00ff);
	cpu_stack_push(cpu, cpu->registery->pc & 0x00ff);

	cpu_status_set(cpu, FLAG_B, FALSE);
	cpu_status_set(cpu, FLAG_U, TRUE);
	cpu_status_set(cpu, FLAG_I, TRUE);
	cpu_stack_push(cpu, cpu->registery->s);

	cpu->addr_abs = IRQ_ADDRESS;
	uint16_t lo = cpu_bus_read(cpu, cpu->addr_abs);
	uint16_t hi = cpu_bus_read(cpu, cpu->addr_abs + 1);
	cpu->registery->pc = (hi << 8) | lo;

	cpu->cycles = 7;
}

// Non-Maskable Interrupt Request - Executes an instruction at a specific
// location, but cannot be disabled
//
// in core, the core to send the interrupt request
void cpu_signal_nmi(CPU * cpu)
{
	cpu_stack_push(cpu, (cpu->registery->pc >> 8) & 0x00ff);
	cpu_stack_push(cpu, cpu->registery->pc & 0x00ff);

	cpu_status_set(cpu, FLAG_B, FALSE);
	cpu_status_set(cpu, FLAG_U, TRUE);
	cpu_status_set(cpu, FLAG_I, TRUE);
	cpu_stack_push(cpu, cpu->registery->s);

	cpu->addr_abs = NMI_ADDRESS;
	uint16_t lo = cpu_bus_read(cpu, cpu->addr_abs);
	uint16_t hi = cpu_bus_read(cpu, cpu->addr_abs + 1);
	cpu->registery->pc = (hi << 8) | lo;

	cpu->cycles = 8;
}

// Perform one clock cycle's worth of update
//
// in core, the core to tick
void cpu_clock(CPU* cpu)
{
#ifdef COUNT_CYCLES
	cpu->clock_count++;
#endif
	if (cpu_clock_complete(cpu) == FALSE) {
		cpu->cycles--;
		return;
	}
	if (cpu->registery->pc == 0x0C6BD)
	{
		int i = 0;
	}
	cpu->opt_code = cpu_bus_read_pc(cpu);
	cpu_status_set(cpu, FLAG_U, TRUE);

	cpu->cycles = lookup[cpu->opt_code].cycles;

	uint8_t extra_addr = (*lookup[cpu->opt_code].addr_mode)(cpu);
	uint8_t extra_oper = (*lookup[cpu->opt_code].operation)(cpu);

	cpu->cycles += extra_addr & extra_oper;

	cpu_status_set(cpu, FLAG_U, TRUE);

	cpu->cycles--;
}

bool cpu_clock_complete(const CPU * cpu)
{
	if (cpu->cycles == 0)
		return TRUE;
	return FALSE;
}

