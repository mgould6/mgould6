#ifndef CPU_H
#define CPU_H

#include <stdint.h>

typedef struct {
    uint8_t registers[8];
    uint8_t F;  // Added to handle flags
    uint8_t A;
    uint8_t B;
    uint8_t C;
    uint8_t D;
    uint8_t E;
    uint8_t H;
    uint8_t L;
    uint16_t SP;
    uint16_t PC;
    bool interruptMasterEnable;
    bool halt;
    uint64_t cycles;
    struct {
        uint8_t Z : 1;
        uint8_t N : 1;
        uint8_t H : 1;
        uint8_t C : 1;
    } flags;
    struct {
        uint8_t ROM[0x8000];    // 32KB ROM
        uint8_t RAM[0x2000];    // 8KB RAM
        uint8_t VRAM[0x2000];   // 8KB Video RAM
        uint8_t OAM[0xA0];      // Sprite Attribute Table
        uint8_t IO[0x80];       // Input/Output registers
        uint8_t ZRAM[0x80];     // Zero Page RAM
    } memory;
} CPU;


enum class Flags : uint8_t {
    FLAG_ZERO = 0x80,
    FLAG_NEGATIVE = 0x40,
    FLAG_HALFCARRY = 0x20,
    FLAG_CARRY = 0x10,
    FLAG_ZERO_SHIFT = 7,
    FLAG_NEGATIVE_SHIFT = 6,
    FLAG_HALFCARRY_SHIFT = 5,
    FLAG_CARRY_SHIFT = 4
};

typedef struct {
    uint8_t value;
    const char* mnemonic;
    uint8_t cycles;
} Opcode;


// Add new function declarations
uint16_t get16BitRegValue(CPU* cpu, uint8_t reg1, uint8_t reg2);
Opcode decode_instruction(uint8_t opcode);
void decode_and_execute_instruction(uint8_t opcode, CPU* cpu);
uint8_t read_mem(CPU* cpu, uint16_t address);
void write_mem(CPU* cpu, uint16_t address, uint8_t value);
uint16_t read_mem_16(CPU* cpu, uint16_t address);
uint8_t read_io(CPU* cpu, uint8_t port);
void write_io(CPU* cpu, uint8_t port, uint8_t value);
uint8_t F(CPU* cpu);
void xor_a_n(CPU* cpu, uint8_t n);
void sub_a_n(CPU* cpu, uint8_t n);
void push16(CPU* cpu, uint8_t* memory, uint16_t val);
uint16_t pop16(CPU* cpu, uint8_t* memory);
void or_a_n(CPU* cpu, uint8_t n);
void and_a_n(CPU* cpu, uint8_t n);
// Load/Store Instructions
void ld_r_r(CPU* cpu, uint8_t opcode);
void ld_r_n(CPU* cpu, uint8_t opcode);
void ld_r_hl(CPU* cpu, uint8_t opcode);
void ld_hl_r(CPU* cpu, uint8_t opcode);
void ld_hl_n(CPU* cpu, uint8_t opcode);
void ld_a_bc(CPU* cpu, uint8_t opcode);
void ld_bc_a(CPU* cpu, uint8_t opcode);
void ld_a_de(CPU* cpu, uint8_t opcode);
void ld_de_a(CPU* cpu, uint8_t opcode);
void ld_a_nn(CPU* cpu, uint8_t opcode);
void ld_nn_a(CPU* cpu, uint8_t opcode);
void ldh_n_a(CPU* cpu, uint8_t opcode);
void ldh_a_n(CPU* cpu, uint8_t opcode);
void add_a_r(CPU* cpu, uint8_t opcode);
void add_a_n(CPU* cpu, uint8_t opcode);
void add_a_hl(CPU* cpu, uint8_t opcode);
void adc_a_r(CPU* cpu, uint8_t opcode);
void adc_a_n(CPU* cpu, uint8_t opcode);
void sub_r(CPU* cpu, uint8_t opcode);
void sub_n(CPU* cpu, uint8_t opcode);
void sub_hl(CPU* cpu, uint8_t opcode);
void sbc_a_r(CPU* cpu, uint8_t opcode);
void sbc_a_n(CPU* cpu, uint8_t opcode);
void and_r(CPU* cpu, uint8_t opcode);
void and_n(CPU* cpu, uint8_t opcode);
void or_r(CPU* cpu, uint8_t opcode);
void or_n(CPU* cpu, uint8_t opcode);
void xor_r(CPU* cpu, uint8_t opcode);
void xor_n(CPU* cpu, uint8_t opcode);
void cp_r(CPU* cpu, uint8_t opcode);
void cp_n(CPU* cpu, uint8_t opcode);
void inc_r(CPU* cpu, uint8_t opcode);
void dec_r(CPU* cpu, uint8_t opcode);
void jp_nn(CPU* cpu, uint8_t opcode);
void jp_cc_nn(CPU* cpu, uint8_t opcode);
void jr_n(CPU* cpu, uint8_t opcode);
void jr_cc_n(CPU* cpu, uint8_t opcode);
void call_nn(CPU* cpu, uint8_t opcode);
void call_cc_nn(CPU* cpu, uint8_t opcode);
void ret(CPU* cpu, uint8_t opcode);
void ret_cc(CPU* cpu, uint8_t opcode);
void reti(CPU* cpu, uint8_t opcode);
void bit_b_r(CPU* cpu, uint8_t opcode);
void set_b_r(CPU* cpu, uint8_t opcode);
void res_b_r(CPU* cpu, uint8_t opcode);
void push_rr(CPU* cpu, uint8_t opcode);
void pop_rr(CPU* cpu, uint8_t opcode);
void nop(CPU* cpu, uint8_t opcode);
void di(CPU* cpu, uint8_t opcode);
void ei(CPU* cpu, uint8_t opcode);
void cpl(CPU* cpu, uint8_t opcode);
void stop_0(CPU* cpu, uint8_t opcode);
void halt(CPU* cpu, uint8_t opcode);
void jp_a16(CPU* cpu, uint8_t opcode);
void call_a16(CPU* cpu, uint8_t opcode);
void jp_hl(CPU* cpu, uint8_t opcode);
void jp_nz_a16(CPU* cpu, uint8_t opcode);
void call_nz_a16(CPU* cpu, uint8_t opcode);
void jp_z_a16(CPU* cpu, uint8_t opcode);
void call_z_a16(CPU* cpu, uint8_t opcode);
void jp_nc_a16(CPU* cpu, uint8_t opcode);
void call_nc_a16(CPU* cpu, uint8_t opcode);
void jp_c_a16(CPU* cpu, uint8_t opcode);
void call_c_a16(CPU* cpu, uint8_t opcode);
void jr_nz_r8(CPU* cpu, uint8_t opcode);
void jr_z_r8(CPU* cpu, uint8_t opcode);
void jr_nc_r8(CPU* cpu, uint8_t opcode);
void jr_c_r8(CPU* cpu, uint8_t opcode);
void add_a_d8(CPU* cpu, uint8_t opcode);
void adc_a_d8(CPU* cpu, uint8_t opcode);
void sub_d8(CPU* cpu, uint8_t opcode);
void sbc_a_d8(CPU* cpu, uint8_t opcode);
void and_d8(CPU* cpu, uint8_t opcode);
void xor_d8(CPU* cpu, uint8_t opcode);
void or_d8(CPU* cpu, uint8_t opcode);
void cp_d8(CPU* cpu, uint8_t opcode);
void rlca(CPU* cpu, uint8_t opcode);
void rrca(CPU* cpu, uint8_t opcode);
void rla(CPU* cpu, uint8_t opcode);
void rra(CPU* cpu, uint8_t opcode);
void daa(CPU* cpu, uint8_t opcode);
void scf(CPU* cpu, uint8_t opcode);
void ccf(CPU* cpu, uint8_t opcode);
void rst_00h(CPU* cpu, uint8_t opcode);
void rst_08h(CPU* cpu, uint8_t opcode);
void rst_10h(CPU* cpu, uint8_t opcode);
void rst_18h(CPU* cpu, uint8_t opcode);
void rst_20h(CPU* cpu, uint8_t opcode);
void rst_28h(CPU* cpu, uint8_t opcode);
void rst_30h(CPU* cpu, uint8_t opcode);
void rst_38h(CPU* cpu, uint8_t opcode);

#endif /* CPU_H */
