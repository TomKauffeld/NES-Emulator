#ifndef __EMULATOR_CPU_CORE_INSTRUCTIONS_INSTRUCTIONS_H__
#define __EMULATOR_CPU_CORE_INSTRUCTIONS_INSTRUCTIONS_H__

#include "operations.h"
#include "addressing.h"

typedef uint8_t(*cpu_instruction_addressing)(CPU*);
typedef uint8_t(*cpu_instruction_operation)(CPU*);

static const struct instruction {
	cpu_instruction_addressing addr_mode;
	cpu_instruction_operation operation;
	uint8_t cycles;
} lookup[256] = {
	{ &cpu_instruction_addressing_imm, &cpu_instruction_operation_brk, 7 }, //00
	{ &cpu_instruction_addressing_izx, &cpu_instruction_operation_ora, 6 }, //01
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_xxx, 2 }, //02
	{ &cpu_instruction_addressing_izx, &cpu_instruction_operation_slo, 8 }, //03
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_nop, 3 }, //04
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_ora, 3 }, //05
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_asl, 5 }, //06
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_slo, 5 }, //07
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_php, 3 }, //08
	{ &cpu_instruction_addressing_imm, &cpu_instruction_operation_ora, 2 }, //09
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_asl, 2 }, //0A
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_xxx, 2 }, //0B
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_nop, 4 }, //0C
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_ora, 4 }, //0D
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_asl, 6 }, //0E
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_slo, 6 }, //0F
	{ &cpu_instruction_addressing_rel, &cpu_instruction_operation_bpl, 2 }, //10
	{ &cpu_instruction_addressing_izy, &cpu_instruction_operation_ora, 5 }, //11
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_xxx, 2 }, //12
	{ &cpu_instruction_addressing_izy, &cpu_instruction_operation_slo, 8 }, //13
	{ &cpu_instruction_addressing_zpx, &cpu_instruction_operation_nop, 4 }, //14
	{ &cpu_instruction_addressing_zpx, &cpu_instruction_operation_ora, 4 }, //15
	{ &cpu_instruction_addressing_zpx, &cpu_instruction_operation_asl, 6 }, //16
	{ &cpu_instruction_addressing_zpx, &cpu_instruction_operation_slo, 6 }, //17
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_clc, 2 }, //18
	{ &cpu_instruction_addressing_aby, &cpu_instruction_operation_ora, 4 }, //19
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_nop, 2 }, //1A
	{ &cpu_instruction_addressing_aby, &cpu_instruction_operation_slo, 7 }, //1B
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_nop, 4 }, //1C
	{ &cpu_instruction_addressing_abx, &cpu_instruction_operation_ora, 4 }, //1D
	{ &cpu_instruction_addressing_abx, &cpu_instruction_operation_asl, 7 }, //1E
	{ &cpu_instruction_addressing_abx, &cpu_instruction_operation_slo, 7 }, //1F
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_jsr, 6 }, //20
	{ &cpu_instruction_addressing_izx, &cpu_instruction_operation_and, 6 }, //21
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_xxx, 2 }, //22
	{ &cpu_instruction_addressing_izx, &cpu_instruction_operation_rla, 8 }, //23
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_bit, 3 }, //24
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_and, 3 }, //25
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_rol, 5 }, //26
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_rla, 5 }, //27
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_plp, 4 }, //28
	{ &cpu_instruction_addressing_imm, &cpu_instruction_operation_and, 2 }, //29
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_rol, 2 }, //2A
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_xxx, 2 }, //2B
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_bit, 4 }, //2C
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_and, 4 }, //2D
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_rol, 6 }, //2E
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_rla, 6 }, //2F
	{ &cpu_instruction_addressing_rel, &cpu_instruction_operation_bmi, 2 }, //30
	{ &cpu_instruction_addressing_izy, &cpu_instruction_operation_and, 5 }, //31
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_xxx, 2 }, //32
	{ &cpu_instruction_addressing_izy, &cpu_instruction_operation_rla, 8 }, //33
	{ &cpu_instruction_addressing_zpx, &cpu_instruction_operation_nop, 4 }, //34
	{ &cpu_instruction_addressing_zpx, &cpu_instruction_operation_and, 4 }, //35
	{ &cpu_instruction_addressing_zpx, &cpu_instruction_operation_rol, 6 }, //36
	{ &cpu_instruction_addressing_zpx, &cpu_instruction_operation_rla, 6 }, //37
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_sec, 2 }, //38
	{ &cpu_instruction_addressing_aby, &cpu_instruction_operation_and, 4 }, //39
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_nop, 2 }, //3A
	{ &cpu_instruction_addressing_aby, &cpu_instruction_operation_rla, 7 }, //3B
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_nop, 4 }, //3C
	{ &cpu_instruction_addressing_abx, &cpu_instruction_operation_and, 4 }, //3D
	{ &cpu_instruction_addressing_abx, &cpu_instruction_operation_rol, 7 }, //3E
	{ &cpu_instruction_addressing_abx, &cpu_instruction_operation_rla, 7 }, //3F
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_rti, 6 }, //40
	{ &cpu_instruction_addressing_izx, &cpu_instruction_operation_eor, 6 }, //41
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_xxx, 2 }, //42
	{ &cpu_instruction_addressing_izx, &cpu_instruction_operation_sre, 8 }, //43
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_nop, 3 }, //44
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_eor, 3 }, //45
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_lsr, 5 }, //46
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_sre, 5 }, //47
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_pha, 3 }, //48
	{ &cpu_instruction_addressing_imm, &cpu_instruction_operation_eor, 2 }, //49
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_lsr, 2 }, //4A
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_xxx, 2 }, //4B
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_jmp, 3 }, //4C
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_eor, 4 }, //4D
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_lsr, 6 }, //4E
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_sre, 6 }, //4F
	{ &cpu_instruction_addressing_rel, &cpu_instruction_operation_bvc, 2 }, //50
	{ &cpu_instruction_addressing_izy, &cpu_instruction_operation_eor, 5 }, //51
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_xxx, 2 }, //52
	{ &cpu_instruction_addressing_izy, &cpu_instruction_operation_sre, 8 }, //53
	{ &cpu_instruction_addressing_zpx, &cpu_instruction_operation_nop, 4 }, //54
	{ &cpu_instruction_addressing_zpx, &cpu_instruction_operation_eor, 4 }, //55
	{ &cpu_instruction_addressing_zpx, &cpu_instruction_operation_lsr, 6 }, //56
	{ &cpu_instruction_addressing_zpx, &cpu_instruction_operation_sre, 6 }, //57
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_cli, 2 }, //58
	{ &cpu_instruction_addressing_aby, &cpu_instruction_operation_eor, 4 }, //59
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_nop, 2 }, //5A
	{ &cpu_instruction_addressing_aby, &cpu_instruction_operation_sre, 7 }, //5B
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_nop, 4 }, //5C
	{ &cpu_instruction_addressing_abx, &cpu_instruction_operation_eor, 4 }, //5D
	{ &cpu_instruction_addressing_abx, &cpu_instruction_operation_lsr, 7 }, //5E
	{ &cpu_instruction_addressing_abx, &cpu_instruction_operation_sre, 7 }, //5F
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_rts, 6 }, //60
	{ &cpu_instruction_addressing_izx, &cpu_instruction_operation_adc, 6 }, //61
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_xxx, 2 }, //62
	{ &cpu_instruction_addressing_izx, &cpu_instruction_operation_rra, 8 }, //63
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_nop, 3 }, //64
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_adc, 3 }, //65
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_ror, 5 }, //66
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_rra, 5 }, //67
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_pla, 4 }, //68
	{ &cpu_instruction_addressing_imm, &cpu_instruction_operation_adc, 2 }, //69
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_ror, 2 }, //6A
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_xxx, 2 }, //6B
	{ &cpu_instruction_addressing_ind, &cpu_instruction_operation_jmp, 5 }, //6C
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_adc, 4 }, //6D
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_ror, 6 }, //6E
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_rra, 6 }, //6F
	{ &cpu_instruction_addressing_rel, &cpu_instruction_operation_bvs, 2 }, //70
	{ &cpu_instruction_addressing_izy, &cpu_instruction_operation_adc, 5 }, //71
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_xxx, 2 }, //72
	{ &cpu_instruction_addressing_izy, &cpu_instruction_operation_rra, 8 }, //73
	{ &cpu_instruction_addressing_zpx, &cpu_instruction_operation_nop, 4 }, //74
	{ &cpu_instruction_addressing_zpx, &cpu_instruction_operation_adc, 4 }, //75
	{ &cpu_instruction_addressing_zpx, &cpu_instruction_operation_ror, 6 }, //76
	{ &cpu_instruction_addressing_zpx, &cpu_instruction_operation_rra, 6 }, //77
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_sei, 2 }, //78
	{ &cpu_instruction_addressing_aby, &cpu_instruction_operation_adc, 4 }, //79
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_nop, 2 }, //7A
	{ &cpu_instruction_addressing_aby, &cpu_instruction_operation_rra, 7 }, //7B
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_nop, 4 }, //7C
	{ &cpu_instruction_addressing_abx, &cpu_instruction_operation_adc, 4 }, //7D
	{ &cpu_instruction_addressing_abx, &cpu_instruction_operation_ror, 7 }, //7E
	{ &cpu_instruction_addressing_abx, &cpu_instruction_operation_rra, 7 }, //7F
	{ &cpu_instruction_addressing_rel, &cpu_instruction_operation_nop, 2 }, //80
	{ &cpu_instruction_addressing_izx, &cpu_instruction_operation_sta, 6 }, //81
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_nop, 2 }, //82
	{ &cpu_instruction_addressing_izx, &cpu_instruction_operation_sax, 6 }, //83
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_sty, 3 }, //84
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_sta, 3 }, //85
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_stx, 3 }, //86
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_sax, 3 }, //87
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_dey, 2 }, //88
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_nop, 2 }, //89
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_txa, 2 }, //8A
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_xxx, 2 }, //8B
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_sty, 4 }, //8C
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_sta, 4 }, //8D
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_stx, 4 }, //8E
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_sax, 4 }, //8F
	{ &cpu_instruction_addressing_rel, &cpu_instruction_operation_bcc, 2 }, //90
	{ &cpu_instruction_addressing_izy, &cpu_instruction_operation_sta, 6 }, //91
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_xxx, 2 }, //92
	{ &cpu_instruction_addressing_zpx, &cpu_instruction_operation_xxx, 6 }, //93
	{ &cpu_instruction_addressing_zpx, &cpu_instruction_operation_sty, 4 }, //94
	{ &cpu_instruction_addressing_zpx, &cpu_instruction_operation_sta, 4 }, //95
	{ &cpu_instruction_addressing_zpy, &cpu_instruction_operation_stx, 4 }, //96
	{ &cpu_instruction_addressing_zpy, &cpu_instruction_operation_sax, 4 }, //97
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_tya, 2 }, //98
	{ &cpu_instruction_addressing_aby, &cpu_instruction_operation_sta, 5 }, //99
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_txs, 2 }, //9A
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_xxx, 5 }, //9B
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_nop, 5 }, //9C
	{ &cpu_instruction_addressing_abx, &cpu_instruction_operation_sta, 5 }, //9D
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_xxx, 5 }, //9E
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_xxx, 5 }, //9F
	{ &cpu_instruction_addressing_imm, &cpu_instruction_operation_ldy, 2 }, //A0
	{ &cpu_instruction_addressing_izx, &cpu_instruction_operation_lda, 6 }, //A1
	{ &cpu_instruction_addressing_imm, &cpu_instruction_operation_ldx, 2 }, //A2
	{ &cpu_instruction_addressing_izx, &cpu_instruction_operation_lax, 6 }, //A3
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_ldy, 3 }, //A4
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_lda, 3 }, //A5
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_ldx, 3 }, //A6
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_lax, 3 }, //A7
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_tay, 2 }, //A8
	{ &cpu_instruction_addressing_imm, &cpu_instruction_operation_lda, 2 }, //A9
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_tax, 2 }, //AA
	{ &cpu_instruction_addressing_imm, &cpu_instruction_operation_lax, 2 }, //AB
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_ldy, 4 }, //AC
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_lda, 4 }, //AD
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_ldx, 4 }, //AE
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_lax, 4 }, //AF
	{ &cpu_instruction_addressing_rel, &cpu_instruction_operation_bcs, 2 }, //B0
	{ &cpu_instruction_addressing_izy, &cpu_instruction_operation_lda, 5 }, //B1
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_xxx, 2 }, //B2
	{ &cpu_instruction_addressing_izy, &cpu_instruction_operation_lax, 5 }, //B3
	{ &cpu_instruction_addressing_zpx, &cpu_instruction_operation_ldy, 4 }, //B4
	{ &cpu_instruction_addressing_zpx, &cpu_instruction_operation_lda, 4 }, //B5
	{ &cpu_instruction_addressing_zpy, &cpu_instruction_operation_ldx, 4 }, //B6
	{ &cpu_instruction_addressing_zpy, &cpu_instruction_operation_lax, 4 }, //B7
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_clv, 2 }, //B8
	{ &cpu_instruction_addressing_aby, &cpu_instruction_operation_lda, 4 }, //B9
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_tsx, 2 }, //BA
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_xxx, 4 }, //BB
	{ &cpu_instruction_addressing_abx, &cpu_instruction_operation_ldy, 4 }, //BC
	{ &cpu_instruction_addressing_abx, &cpu_instruction_operation_lda, 4 }, //BD
	{ &cpu_instruction_addressing_aby, &cpu_instruction_operation_ldx, 4 }, //BE
	{ &cpu_instruction_addressing_aby, &cpu_instruction_operation_lax, 4 }, //BF
	{ &cpu_instruction_addressing_imm, &cpu_instruction_operation_cpy, 2 }, //C0
	{ &cpu_instruction_addressing_izx, &cpu_instruction_operation_cmp, 6 }, //C1
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_nop, 2 }, //C2
	{ &cpu_instruction_addressing_izx, &cpu_instruction_operation_dcp, 8 }, //C3
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_cpy, 3 }, //C4
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_cmp, 3 }, //C5
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_dec, 5 }, //C6
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_dcp, 5 }, //C7
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_iny, 2 }, //C8
	{ &cpu_instruction_addressing_imm, &cpu_instruction_operation_cmp, 2 }, //C9
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_dex, 2 }, //CA
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_xxx, 2 }, //CB
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_cpy, 4 }, //CC
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_cmp, 4 }, //CD
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_dec, 6 }, //CE
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_dcp, 6 }, //CF
	{ &cpu_instruction_addressing_rel, &cpu_instruction_operation_bne, 2 }, //D0
	{ &cpu_instruction_addressing_izy, &cpu_instruction_operation_cmp, 5 }, //D1
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_xxx, 2 }, //D2
	{ &cpu_instruction_addressing_izy, &cpu_instruction_operation_dcp, 8 }, //D3
	{ &cpu_instruction_addressing_zpx, &cpu_instruction_operation_nop, 4 }, //D4
	{ &cpu_instruction_addressing_zpx, &cpu_instruction_operation_cmp, 4 }, //D5
	{ &cpu_instruction_addressing_zpx, &cpu_instruction_operation_dec, 6 }, //D6
	{ &cpu_instruction_addressing_zpx, &cpu_instruction_operation_dcp, 6 }, //D7
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_cld, 2 }, //D8
	{ &cpu_instruction_addressing_aby, &cpu_instruction_operation_cmp, 4 }, //D9
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_nop, 2 }, //DA
	{ &cpu_instruction_addressing_aby, &cpu_instruction_operation_dcp, 7 }, //DB
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_nop, 4 }, //DC
	{ &cpu_instruction_addressing_abx, &cpu_instruction_operation_cmp, 4 }, //DD
	{ &cpu_instruction_addressing_abx, &cpu_instruction_operation_dec, 7 }, //DE
	{ &cpu_instruction_addressing_abx, &cpu_instruction_operation_dcp, 7 }, //DF
	{ &cpu_instruction_addressing_imm, &cpu_instruction_operation_cpx, 2 }, //E0
	{ &cpu_instruction_addressing_izx, &cpu_instruction_operation_sbc, 6 }, //E1
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_nop, 2 }, //E2
	{ &cpu_instruction_addressing_izx, &cpu_instruction_operation_isc, 8 }, //E3
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_cpx, 3 }, //E4
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_sbc, 3 }, //E5
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_inc, 5 }, //E6
	{ &cpu_instruction_addressing_zp0, &cpu_instruction_operation_isc, 5 }, //E7
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_inx, 2 }, //E8
	{ &cpu_instruction_addressing_imm, &cpu_instruction_operation_sbc, 2 }, //E9
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_nop, 2 }, //EA
	{ &cpu_instruction_addressing_imm, &cpu_instruction_operation_sbc, 2 }, //EB
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_cpx, 4 }, //EC
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_sbc, 4 }, //ED
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_inc, 6 }, //EE
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_isc, 6 }, //EF
	{ &cpu_instruction_addressing_rel, &cpu_instruction_operation_beq, 2 }, //F0
	{ &cpu_instruction_addressing_izy, &cpu_instruction_operation_sbc, 5 }, //F1
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_xxx, 2 }, //F2
	{ &cpu_instruction_addressing_izy, &cpu_instruction_operation_isc, 8 }, //F3
	{ &cpu_instruction_addressing_zpx, &cpu_instruction_operation_nop, 4 }, //F4
	{ &cpu_instruction_addressing_zpx, &cpu_instruction_operation_sbc, 4 }, //F5
	{ &cpu_instruction_addressing_zpx, &cpu_instruction_operation_inc, 6 }, //F6
	{ &cpu_instruction_addressing_zpx, &cpu_instruction_operation_isc, 6 }, //F7
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_sed, 2 }, //F8
	{ &cpu_instruction_addressing_aby, &cpu_instruction_operation_sbc, 4 }, //F9
	{ &cpu_instruction_addressing_imp, &cpu_instruction_operation_nop, 2 }, //FA
	{ &cpu_instruction_addressing_aby, &cpu_instruction_operation_isc, 7 }, //FB
	{ &cpu_instruction_addressing_abs, &cpu_instruction_operation_nop, 4 }, //FC
	{ &cpu_instruction_addressing_abx, &cpu_instruction_operation_sbc, 4 }, //FD
	{ &cpu_instruction_addressing_abx, &cpu_instruction_operation_inc, 7 }, //FE
	{ &cpu_instruction_addressing_abx, &cpu_instruction_operation_isc, 7 }  //FF
};

#endif