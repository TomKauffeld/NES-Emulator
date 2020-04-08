#ifndef __EMULATOR_CPU_CORE_SETTINGS_H__
#define __EMULATOR_CPU_CORE_SETTINGS_H__


#define INCLUDE_HARDWARE_BUG_IND

#define RAM_START       0x0000
#define RAM_END         0x07ff

#define RAM_CLONE_START 0x0800
#define RAM_CLONE_END   0x1fff

#define PPU_START       0x2000
#define PPU_END         0x2007

#define PPU_CLONE_START 0x2008
#define PPU_CLONE_END   0x3fff

#define APU_START       0x4000
#define APU_END         0x4017

#define DIS_START       0x4018
#define DIS_END         0x401f

#define ROM_START       0x4020
#define ROM_END         0xffff


#define CAR_PRG_START   0x8000
#define CAR_PRG_END     0xffff

#define RESET_ADDRESS 0xFFFC // the address where the pc will be fetched after a reset signal
#define IRQ_ADDRESS 0xFFFE // the address where the pc will be fetched after a irq signal
#define NMI_ADDRESS 0xFFFA // the address where the pc will be fetched after a nmi signal

#define STACK_POINTER_INIT 0x00FD // the stack pointer initial value
#define STACK_POSITION_START 0x0100 // the starting position of the stack


#endif