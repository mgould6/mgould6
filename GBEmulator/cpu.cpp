#include "cpu.h"
#include "memory.h"
#include <iostream>
uint16_t get16BitRegValue(CPU* cpu, uint8_t reg1, uint8_t reg2) {
    return (reg1 << 8) | reg2;
}

const int opcode_cycles[256] = {
    4,  12, 8,  8,  4,  4,  8,  4,  20, 8,  8,  8,  4,  4,  8, 4,  
    // 0x00 - 0x0F
    4,  12, 8,  8,  4,  4,  8,  4,  12, 8,  8,  8,  4,  4,  8,  4,  
    // 0x10 - 0x1F
    12, 12, 8,  8,  4,  4,  8,  4,  12, 8,  8,  8,  4,  4,  8,  4,  
    // 0x20 - 0x2F
    12, 12, 8,  8,  4,  4,  8,  4,  12, 8,  8,  8,  4,  4,  8,  4,  
    // 0x30 - 0x3F
    4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,  
    // 0x40 - 0x4F
    4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,  
    // 0x50 - 0x5F
    4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,  
    // 0x60 - 0x6F
    8,  8,  8,  8,  8,  8,  4,  8,  4,  4,  4,  4,  4,  4,  8,  4,  
    // 0x70 - 0x7F
    4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,  
    // 0x80 - 0x8F
    4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,
    // 0x90 - 0x9F
    4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,
    // 0xA0 - 0xAF
    4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,
    // 0xB0 - 0xBF
    20,  12,  16,  16,  24,  16,  8,  16,  20,  16,  16,  4,  24,  24,  8,  16,
    // 0xC0 - 0xCF
    20,  12,  16,  0,  24,  16,  8,  16,  20,  16,  16,  0,  24,  0,  8,  16,
    // 0xD0 - 0xDF
    2,  12,  8,  0,  0,  16,  8,  16,  16,  4,  16,  0,  0,  0,  8,  16,
    // 0xE0 - 0xEF
    2,  12,  8,  4,  0,  16,  8,  16,  12,  8,  16,  4,  0,  0,  8,  16
    // 0xF0 - 0xFF
};

Opcode decode_instruction(uint8_t opcode) {
    Opcode decodedOpcode;
    decodedOpcode.value = opcode;
    decodedOpcode.mnemonic = NULL;
    // TODO: Add logic to set the number of cycles based on the opcode
    decodedOpcode.cycles = opcode_cycles[opcode];  // <-- set cycles from the array
    return decodedOpcode;
}

uint8_t read_memory_byte(CPU* cpu, uint16_t address) {
    // Check which region the address falls into
    if (address < 0x8000) {        // ROM
        return cpu->memory.ROM[address];
    }
    else if (address < 0xA000) { // VRAM
        return cpu->memory.VRAM[address - 0x8000];
    }
    else if (address < 0xC000) { // Switchable RAM bank
        return cpu->memory.RAM[address - 0xA000];
    }
    else if (address < 0xE000) { // Internal RAM
        return cpu->memory.RAM[address - 0xC000];
    }
    else if (address < 0xFE00) { // Echo of Internal RAM
        return cpu->memory.RAM[address - 0xE000];
    }
    else if (address < 0xFEA0) { // OAM
        return cpu->memory.OAM[address - 0xFE00];
    }
    else if (address < 0xFF00) { // Unusable
        // Handle this case based on your needs
    }
    else if (address < 0xFF80) { // I/O Ports
        return cpu->memory.IO[address - 0xFF00];
    }
    else {                       // Zero Page RAM
        return cpu->memory.ZRAM[address - 0xFF80];
    }
}

uint8_t fetch_next_byte(CPU* cpu) {
    uint8_t next_byte = read_memory_byte(cpu, cpu->PC);
    cpu->PC++;  // Increment the program counter to the next byte
    return next_byte;
}


void decode_and_execute_instruction(uint8_t opcode, CPU* cpu) {

    if (opcode == 0xCB) {
        uint8_t cb_opcode = fetch_next_byte(cpu);  // This function would fetch the next byte in memory
        switch (cb_opcode) {
        case 0x00:  // This is a placeholder. Replace with actual CB opcode values
            // call the appropriate function
            break;
            // Add cases for all the CB opcode values
        default:
            // Handle unrecognized opcode
            break;
        }
    }

    else {
        Opcode decodedOpcode = decode_instruction(opcode);
        cpu->cycles += opcode_cycles[opcode]; // Adding the opcode cycle to the CPU's total cycle count.
        if (decodedOpcode.cycles == 0) {
            // This is an undefined opcode. You could either ignore it or throw an error.
            std::cout << "Null Opcode" << std::endl;
            return;
        }
        

        //Decode Opcode List ------ CONTINUE UPDATING COMMENTS FROM x4
        switch (decodedOpcode.value) {
            
            // xX0
            case 0x00: // NOP
                nop(cpu, opcode);
                break;
            case 0x10: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x20: // JR NZ,r8
                jr_nz_r8(cpu, opcode);
                break;
            case 0x30: // JR NC,r8
                jr_nc_r8(cpu, opcode);
                break;
            case 0x40: // LD B,B
                nop(cpu, opcode);
                break;
            case 0x50: // LD D,B
                ld_d_b(cpu);
                break;
            case 0x60: // LD H, B
                ld_h_b(cpu);
                break;
            case 0x70: // LD (HL), B
                ld_hl_b(cpu);
                break;
            case 0x80: // ADD A,B
                add_a_b(cpu);
                break;
            case 0x90: // SUB B
                sub_b(cpu);
                break;
            case 0xA0: // AND B
                and_b(cpu);
                break;
            case 0xB0: // OR B
                or_b(cpu);
                break;
            case 0xC0: // RET NZ
                ret_nz(cpu);
                break;
            case 0xD0: // RET NC
                ret_nc(cpu);
                break;
            case 0xE0: // LDH (a8),A 
                ldh_a8_a(cpu);
                break;
            case 0xF0: // LDH A,(a8) 
                ldh_a_a8(cpu);
                break;

            case 0x01: // LD BC,d16
                nop(cpu, opcode);
                break;
            case 0x11: // LD DE,d16
                stop_0(cpu, opcode);
                break;
            case 0x21: // LD HL,d16 
                stop_0(cpu, opcode);
                break;
            case 0x31: // LD SP,d16
                nop(cpu, opcode);
                break;
            case 0x41: // LD B,C
                stop_0(cpu, opcode);
                break;
            case 0x51: // LD D,C
                stop_0(cpu, opcode);
                break;
            case 0x61: // LD H,C
                nop(cpu, opcode);
                break;
            case 0x71: // LD HL,C
                stop_0(cpu, opcode);
                break;
            case 0x81: // ADD A,C
                stop_0(cpu, opcode);
                break;
            case 0x91: // SUB C
                nop(cpu, opcode);
                break;
            case 0xA1: // AND C
                stop_0(cpu, opcode);
                break;
            case 0xB1: // OR C
                stop_0(cpu, opcode);
                break;
            case 0xC1: // POP BC
                nop(cpu, opcode);
                break;
            case 0xD1: // POP DE
                stop_0(cpu, opcode);
                break;
            case 0xE1: // POP HL
                stop_0(cpu, opcode);
                break;
            case 0xF1: // POP AF
                stop_0(cpu, opcode);
                break; 

            case 0x02: // LD (BC),A
                nop(cpu, opcode);
                break;
            case 0x12: // LD (DE),A
                stop_0(cpu, opcode);
                break;
            case 0x22: // LD (HL+),A
                stop_0(cpu, opcode);
                break;
            case 0x32: // LD (HL-),A
                nop(cpu, opcode);
                break;
            case 0x42: // LD B,D
                stop_0(cpu, opcode);
                break;
            case 0x52: // LD D,D
                stop_0(cpu, opcode);
                break;
            case 0x62: // LD H,D
                nop(cpu, opcode);
                break;
            case 0x72: // LD (HL),D
                stop_0(cpu, opcode);
                break;
            case 0x82: // ADD A,D
                stop_0(cpu, opcode);
                break;
            case 0x92: // SUB D
                nop(cpu, opcode);
                break;
            case 0xA2: // AND D
                stop_0(cpu, opcode);
                break;
            case 0xB2: // OR D
                stop_0(cpu, opcode);
                break;
            case 0xC2: // JP NZ,a16
                nop(cpu, opcode);
                break;
            case 0xD2: // JP NC,a16
                stop_0(cpu, opcode);
                break;
            case 0xE2: // LD (C),A
                stop_0(cpu, opcode);
                break;
            case 0xF2: // LD A,(C)
                stop_0(cpu, opcode);
                break; 

            case 0x03: // INC BC
                nop(cpu, opcode);
                break;
            case 0x13: // INC DE
                stop_0(cpu, opcode);
                break;
            case 0x23: // INC HL
                stop_0(cpu, opcode);
                break;
            case 0x33: // INC SP
                nop(cpu, opcode);
                break;
            case 0x43: // LD B,E
                stop_0(cpu, opcode);
                break;
            case 0x53: // LD D,E
                stop_0(cpu, opcode);
                break;
            case 0x63: // LD H,E
                nop(cpu, opcode);
                break;
            case 0x73: // LD HL,E
                stop_0(cpu, opcode);
                break;
            case 0x83: // ADD A,E
                stop_0(cpu, opcode);
                break;
            case 0x93: // SUB E
                nop(cpu, opcode);
                break;
            case 0xA3: // AND E
                stop_0(cpu, opcode);
                break;
            case 0xB3: // OR E
                stop_0(cpu, opcode);
                break;
            case 0xC3: // JP a16
                nop(cpu, opcode);
                break;
            case 0xD3: // NOP
                stop_0(cpu, opcode);
                break;
            case 0xE3: // NOP
                stop_0(cpu, opcode);
                break;
            case 0xF3: // DI
                stop_0(cpu, opcode);
                break; 

            case 0x04: // NOP
                nop(cpu, opcode);
                break;
            case 0x14: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x24: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x34: // NOP
                nop(cpu, opcode);
                break;
            case 0x44: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x54: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x64: // NOP
                nop(cpu, opcode);
                break;
            case 0x74: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x84: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x94: // NOP
                nop(cpu, opcode);
                break;
            case 0xA4: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xB4: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xC4: // NOP
                nop(cpu, opcode);
                break;
            case 0xD4: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xE4: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xF4: // STOP 0
                stop_0(cpu, opcode);
                break;

            case 0x05: // NOP
                nop(cpu, opcode);
                break;
            case 0x15: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x25: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x35: // NOP
                nop(cpu, opcode);
                break;
            case 0x45: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x55: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x65: // NOP
                nop(cpu, opcode);
                break;
            case 0x75: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x85: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x95: // NOP
                nop(cpu, opcode);
                break;
            case 0xA5: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xB5: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xC5: // NOP
                nop(cpu, opcode);
                break;
            case 0xD5: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xE5: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xF5: // STOP 0
                stop_0(cpu, opcode);
                break; 
            
            case 0x06: // NOP
                nop(cpu, opcode);
                break;
            case 0x16: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x26: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x36: // NOP
                nop(cpu, opcode);
                break;
            case 0x46: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x56: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x66: // NOP
                nop(cpu, opcode);
                break;
            case 0x76: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x86: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x96: // NOP
                nop(cpu, opcode);
                break;
            case 0xA6: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xB6: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xC6: // NOP
                nop(cpu, opcode);
                break;
            case 0xD6: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xE6: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xF6: // STOP 0
                stop_0(cpu, opcode);
                break; 
            
            case 0x07: // NOP
                nop(cpu, opcode);
                break;
            case 0x17: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x27: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x37: // NOP
                nop(cpu, opcode);
                break;
            case 0x47: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x57: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x67: // NOP
                nop(cpu, opcode);
                break;
            case 0x77: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x87: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x97: // NOP
                nop(cpu, opcode);
                break;
            case 0xA7: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xB7: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xC7: // NOP
                nop(cpu, opcode);
                break;
            case 0xD7: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xE7: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xF7: // STOP 0
                stop_0(cpu, opcode);
                break; 
            
            case 0x08: // NOP
                nop(cpu, opcode);
                break;
            case 0x18: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x28: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x38: // NOP
                nop(cpu, opcode);
                break;
            case 0x48: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x58: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x68: // NOP
                nop(cpu, opcode);
                break;
            case 0x78: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x88: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x98: // NOP
                nop(cpu, opcode);
                break;
            case 0xA8: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xB8: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xC8: // NOP
                nop(cpu, opcode);
                break;
            case 0xD8: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xE8: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xF8: // STOP 0
                stop_0(cpu, opcode);
                break; 
            
            case 0x09: // NOP
                nop(cpu, opcode);
                break;
            case 0x19: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x29: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x39: // NOP
                nop(cpu, opcode);
                break;
            case 0x49: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x59: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x69: // NOP
                nop(cpu, opcode);
                break;
            case 0x79: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x89: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x99: // NOP
                nop(cpu, opcode);
                break;
            case 0xA9: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xB9: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xC9: // NOP
                nop(cpu, opcode);
                break;
            case 0xD9: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xE9: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xF9: // STOP 0
                stop_0(cpu, opcode);
                break; 
            
            case 0x0A: // NOP
                nop(cpu, opcode);
                break;
            case 0x1A: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x2A: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x3A: // NOP
                nop(cpu, opcode);
                break;
            case 0x4A: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x5A: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x6A: // NOP
                nop(cpu, opcode);
                break;
            case 0x7A: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x8A: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x9A: // NOP
                nop(cpu, opcode);
                break;
            case 0xAA: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xBA: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xCA: // NOP
                nop(cpu, opcode);
                break;
            case 0xDA: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xEA: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xFA: // STOP 0
                stop_0(cpu, opcode);
                break; 
            
            case 0x0B: // NOP
                nop(cpu, opcode);
                break;
            case 0x1B: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x2B: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x3B: // NOP
                nop(cpu, opcode);
                break;
            case 0x4B: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x5B: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x6B: // NOP
                nop(cpu, opcode);
                break;
            case 0x7B: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x8B: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x9B: // NOP
                nop(cpu, opcode);
                break;
            case 0xAB: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xBB: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xCB: // NOP
                nop(cpu, opcode);
                break;
            case 0xDB: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xEB: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xFB: // STOP 0
                stop_0(cpu, opcode);
                break; 
            
            case 0x0C: // NOP
                nop(cpu, opcode);
                break;
            case 0x1C: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x2C: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x3C: // NOP
                nop(cpu, opcode);
                break;
            case 0x4C: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x5C: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x6C: // NOP
                nop(cpu, opcode);
                break;
            case 0x7C: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x8C: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x9C: // NOP
                nop(cpu, opcode);
                break;
            case 0xAC: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xBC: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xCC: // NOP
                nop(cpu, opcode);
                break;
            case 0xDC: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xEC: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xFC: // STOP 0
                stop_0(cpu, opcode);
                break; 
            
            case 0x0D: // NOP
                nop(cpu, opcode);
                break;
            case 0x1D: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x2D: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x3D: // NOP
                nop(cpu, opcode);
                break;
            case 0x4D: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x5D: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x6D: // NOP
                nop(cpu, opcode);
                break;
            case 0x7D: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x8D: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x9D: // NOP
                nop(cpu, opcode);
                break;
            case 0xAD: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xBD: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xCD: // NOP
                nop(cpu, opcode);
                break;
            case 0xDD: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xED: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xFD: // STOP 0
                stop_0(cpu, opcode);
                break; 
            
            case 0x0E: // NOP
                nop(cpu, opcode);
                break;
            case 0x1E: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x2E: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x3E: // NOP
                break;
            case 0x4E: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x5E: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x6E: // NOP
                nop(cpu, opcode);
                break;
            case 0x7E: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x8E: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x9E: // NOP
                nop(cpu, opcode);
                break;
            case 0xAE: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xBE: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xCE: // NOP
                nop(cpu, opcode);
                break;
            case 0xDE: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xEE: // STOP 0
                stop_0(cpu, opcode);
                break;
            
            case 0xFE: // STOP 0
                stop_0(cpu, opcode);
                break; 
            case 0x0F: // NOP
                nop(cpu, opcode);
                break;
            case 0x1F: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x2F: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x3F: // NOP
                nop(cpu, opcode);
                break;
            case 0x4F: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x5F: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x6F: // NOP
                nop(cpu, opcode);
                break;
            case 0x7F: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x8F: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0x9F: // NOP
                nop(cpu, opcode);
                break;
            case 0xAF: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xBF: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xCF: // NOP
                nop(cpu, opcode);
                break;
            case 0xDF: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xEF: // STOP 0
                stop_0(cpu, opcode);
                break;
            case 0xFF: // STOP 0
                stop_0(cpu, opcode);
                break;
            default:
                // Handle unrecognized opcode
                std::cout << "Unrecognized opcode 0x" << std::hex << opcode << std::endl;
                break;
        }
    }
}

//  READ FUNCTIONS / WRITE FUNCTIONS 
uint8_t read_mem(CPU* cpu, uint16_t address) {
    if (address < 0x8000) {
        // The address is in the ROM
        return cpu->memory.ROM[address];
    }
    else if (address >= 0xA000 && address < 0xC000) {
        // The address is in the RAM
        return cpu->memory.RAM[address - 0xA000];
    }

    // TODO: Implement other memory banks

    // If the address isn't valid, return 0
    return 0;
}
void write_mem(CPU* cpu, uint16_t address, uint8_t value) {
    if (address < 0x8000) {
        // The address is in the ROM, which is read-only. Ignore the write.
    }
    else if (address >= 0xA000 && address < 0xC000) {
        // The address is in the RAM
        cpu->memory.RAM[address - 0xA000] = value;
    }

    // TODO: Implement other memory banks
}
uint16_t read_mem_16(CPU* cpu, uint16_t address) {
    // Read the least significant byte
    uint8_t lsb = read_mem(cpu, address);

    // Read the most significant byte
    uint8_t msb = read_mem(cpu, address + 1);

    // Combine the two bytes into a 16-bit value and return it
    return (msb << 8) | lsb;
}
uint8_t read_io(CPU* cpu, uint8_t port) {
    return cpu->memory.IO[port];
}
void write_io(CPU* cpu, uint8_t port, uint8_t value) {
    cpu->memory.IO[port] = value;
}

// F
uint8_t F(CPU* cpu) {
    // Here you return the value of the F register. It depends on how you have structured your program.
    return cpu->F;
}

// PUSH Ops / POP Ops
void push16(CPU* cpu, uint8_t* memory, uint16_t val) {
    memory[--cpu->SP] = val >> 8;   // High byte
    memory[--cpu->SP] = val & 0xFF; // Low byte
}
uint16_t pop16(CPU* cpu, uint8_t* memory) {
    uint16_t val = (memory[cpu->SP + 1] << 8) | memory[cpu->SP];
    cpu->SP += 2;
    return val;
}
void push_rr(CPU* cpu, uint8_t opcode) {
    uint8_t rr = (opcode >> 4) & 0x03;
    // push the value of 16-bit register rr onto the stack
}
void pop_rr(CPU* cpu, uint8_t opcode) {
    uint8_t rr = (opcode >> 4) & 0x03;
    // pop value from stack into 16-bit register rr
}

// LOAD Ops
void ld_r_r(CPU* cpu, uint8_t opcode) {
    uint8_t sourceRegisterIndex = (opcode >> 3) & 0x07;
    uint8_t destRegisterIndex = opcode & 0x07;
    cpu->registers[destRegisterIndex] = cpu->registers[sourceRegisterIndex];
}
void ld_r_n(CPU* cpu, uint8_t opcode) {
    uint8_t r = opcode & 0x07;
    uint8_t n = read_mem(cpu, cpu->PC++);
    cpu->registers[r] = n;
}
void ld_r_hl(CPU* cpu, uint8_t opcode) {
    uint8_t r = opcode & 0x07;
    cpu->registers[r] = read_mem(cpu, get16BitRegValue(cpu, cpu->H, cpu->L));
}
void ld_hl_r(CPU* cpu, uint8_t opcode) {
    uint8_t r = opcode & 0x07;
    write_mem(cpu, get16BitRegValue(cpu, cpu->H, cpu->L), cpu->registers[r]);
}
void ld_hl_n(CPU* cpu, uint8_t opcode) {
    uint8_t n = read_mem(cpu, cpu->PC++);
    write_mem(cpu, get16BitRegValue(cpu, cpu->H, cpu->L), n);
}
void ld_d_b(CPU* cpu) {
    cpu->D = cpu->B;
}
void ld_h_b(CPU* cpu) {
    cpu->H = cpu->B;
}
void ld_hl_b(CPU* cpu) {
    uint16_t hl = (cpu->H << 8) | cpu->L;
    write_mem(cpu, hl, cpu->B);
}
void ld_a_bc(CPU* cpu, uint8_t opcode) {
    cpu->A = read_mem(cpu, get16BitRegValue(cpu, cpu->B, cpu->C));
}
void ld_bc_a(CPU* cpu, uint8_t opcode) {
    write_mem(cpu, get16BitRegValue(cpu, cpu->B, cpu->C), cpu->A);
}
void ld_a_de(CPU* cpu, uint8_t opcode) {
    cpu->A = read_mem(cpu, get16BitRegValue(cpu, cpu->D, cpu->E));
}
void ld_de_a(CPU* cpu, uint8_t opcode) {
    write_mem(cpu, get16BitRegValue(cpu, cpu->D, cpu->E), cpu->A);
}
void ld_a_nn(CPU* cpu, uint8_t opcode) {
    uint16_t nn = read_mem_16(cpu, cpu->PC);
    cpu->PC += 2;
    cpu->A = read_mem(cpu, nn);
}
void ld_nn_a(CPU* cpu, uint8_t opcode) {
    uint16_t nn = read_mem_16(cpu, cpu->PC);
    cpu->PC += 2;
    write_mem(cpu, nn, cpu->A);
}
void ldh_n_a(CPU* cpu, uint8_t opcode) {
    uint8_t n = read_mem(cpu, cpu->PC++);
    write_io(cpu, 0xFF00 + n, cpu->A);
}
void ldh_a_n(CPU* cpu, uint8_t opcode) {
    uint8_t n = read_mem(cpu, cpu->PC++);
    cpu->A = read_io(cpu, 0xFF00 + n);
}
void ldh_a8_a(CPU* cpu) {
    uint8_t a8 = fetch_next_byte(cpu);
    if (a8 >= 0x00 && a8 <= 0x7F) {
        uint16_t address = 0xFF00 + a8;
        write_mem(cpu, address, cpu->A);
    }
    else {
        std::cout << "Invalid IO address" << std::endl;
    }
}
void ldh_a_a8(CPU* cpu) {
    uint8_t a8 = fetch_next_byte(cpu);
    if (a8 >= 0x00 && a8 <= 0x7F) {
        uint16_t address = 0xFF00 + a8;
        cpu->A = read_mem(cpu, address);
    }
    else {
        std::cout << "Invalid IO address" << std::endl;
    }
}

 // ADD Ops
void add_a_r(CPU* cpu, uint8_t opcode) {
    uint8_t r = opcode & 0x07;
    cpu->A += cpu->registers[r];
    // Update flags accordingly
}
void add_a_n(CPU* cpu, uint8_t opcode) {
    uint8_t n = read_mem(cpu, cpu->PC++);
    cpu->A += n;
    // Update flags accordingly
}
void add_a_hl(CPU* cpu, uint8_t opcode) {
    uint8_t oldValue = cpu->A;
    uint16_t address = get16BitRegValue(cpu, cpu->H, cpu->L);
    uint8_t value = read_mem(cpu, address);
    cpu->A += value;
    // Update flags
    cpu->flags.Z = (cpu->A == 0);
    cpu->flags.N = 0;
    cpu->flags.H = ((oldValue & 0xF) + (value & 0xF)) > 0xF;
    cpu->flags.C = oldValue > (cpu->A - value);
}
void adc_a_r(CPU* cpu, uint8_t opcode) {
    uint8_t r = opcode & 0x07;
    uint8_t carry = cpu->flags.C ? 1 : 0;
    uint8_t oldValue = cpu->A;
    cpu->A += cpu->registers[r] + carry;

    cpu->flags.Z = (cpu->A == 0);
    cpu->flags.N = 0;
    cpu->flags.H = ((oldValue & 0xF) + (cpu->registers[r] & 0xF) + carry) > 0xF;
    cpu->flags.C = (oldValue + cpu->registers[r] + carry) > 0xFF;
}
void adc_a_n(CPU* cpu, uint8_t opcode) {
    uint8_t n = read_mem(cpu, cpu->PC++);
    uint8_t carry = cpu->flags.C; // check the carry flag directly
    uint8_t oldValue = cpu->A;
    cpu->A += n + carry;

    // Update flags accordingly
    cpu->flags.Z = (cpu->A == 0);
    cpu->flags.N = 0;
    cpu->flags.H = ((oldValue & 0x0F) + (n & 0x0F) + carry) > 0x0F;
    cpu->flags.C = oldValue > (cpu->A - n - carry);
}
void add_a_d8(CPU* cpu, uint8_t opcode) {
    uint8_t value = read_mem(cpu, cpu->PC++);
    add_a_n(cpu, value);
}
void adc_a_d8(CPU* cpu, uint8_t opcode) {
    uint8_t value = read_mem(cpu, cpu->PC++);
    adc_a_n(cpu, value);
}
void add_a_b(CPU* cpu) {
    uint8_t B = cpu->B;
    cpu->F = 0;  // Clear flags

    if (((cpu->A & 0xF) + (B & 0xF)) > 0xF)
        cpu->F |= 0x20;  // Set half carry flag

    cpu->A += B;

    if (cpu->A == 0)
        cpu->F |= 0x80;  // Set zero flag

    if (cpu->A < B)
        cpu->F |= 0x10;  // Set carry flag
}

// SUB Ops
void sub_r(CPU* cpu, uint8_t opcode) {
    uint8_t r = opcode & 0x07;
    cpu->A -= cpu->registers[r];
    // Update flags accordingly
}
void sub_n(CPU* cpu, uint8_t opcode) {
    uint8_t n = read_mem(cpu, cpu->PC++);
    cpu->A -= n;
    // Update flags accordingly
}
void sub_hl(CPU* cpu, uint8_t opcode) {
    cpu->A -= read_mem(cpu, get16BitRegValue(cpu, cpu->H, cpu->L));
    // Update flags accordingly
}
void sub_a_n(CPU* cpu, uint8_t n) {
    uint16_t res = cpu->A - n;
    cpu->F = static_cast<uint8_t>(Flags::FLAG_NEGATIVE);
    if ((res & 0xFF) == 0) {
        cpu->F |= static_cast<uint8_t>(Flags::FLAG_ZERO);
    }
    if (res & 0x100) {
        cpu->F |= static_cast<uint8_t>(Flags::FLAG_CARRY);
    }
    cpu->A -= n;
}
void sbc_a_r(CPU* cpu, uint8_t opcode) {
    uint8_t r = opcode & 0x07;
    uint8_t carry = cpu->flags.C;  // Check the carry flag directly
    uint8_t oldValue = cpu->A;
    cpu->A -= cpu->registers[r] + carry;

    // Update flags accordingly
    cpu->flags.Z = (cpu->A == 0);
    cpu->flags.N = 1;
    cpu->flags.H = ((oldValue & 0x0F) - (cpu->registers[r] & 0x0F) - carry) < 0;
    cpu->flags.C = (oldValue < (cpu->registers[r] + carry));
}
void sbc_a_n(CPU* cpu, uint8_t opcode) {
    uint8_t n = read_mem(cpu, cpu->PC++);
    uint8_t carry = cpu->flags.C;  // Check the carry flag directly
    uint8_t oldValue = cpu->A;
    cpu->A -= n + carry;

    // Update flags accordingly
    cpu->flags.Z = (cpu->A == 0);
    cpu->flags.N = 1;
    cpu->flags.H = ((oldValue & 0x0F) - (n & 0x0F) - carry) < 0;
    cpu->flags.C = (oldValue < (n + carry));
}
void sub_d8(CPU* cpu, uint8_t opcode) {
    uint8_t value = read_mem(cpu, cpu->PC++);
    sub_a_n(cpu, value);
}
void sbc_a_d8(CPU* cpu, uint8_t opcode) {
    uint8_t value = read_mem(cpu, cpu->PC++);
    sbc_a_n(cpu, value);
}
void sub_b(CPU* cpu) {
    uint8_t B = cpu->B;
    cpu->F = 0x40;  // Set subtract flag

    if ((cpu->A & 0xF) < (B & 0xF))
        cpu->F |= 0x20;  // Set half carry flag

    cpu->A -= B;

    if (cpu->A == 0)
        cpu->F |= 0x80;  // Set zero flag

    if (cpu->A > B)
        cpu->F |= 0x10;  // Set carry flag
}

// AND Ops
void and_r(CPU* cpu, uint8_t opcode) {
    uint8_t r = opcode & 0x07;
    cpu->A &= cpu->registers[r];

    cpu->flags.Z = (cpu->A == 0);
    cpu->flags.N = 0;
    cpu->flags.H = 1;
    cpu->flags.C = 0;
}
void and_n(CPU* cpu, uint8_t opcode) {
    uint8_t n = read_mem(cpu, cpu->PC++);
    cpu->A &= n;

    cpu->flags.Z = (cpu->A == 0);
    cpu->flags.N = 0;
    cpu->flags.H = 1;
    cpu->flags.C = 0;
}
void and_a_n(CPU* cpu, uint8_t n) {
    cpu->A &= n;
    // Reset flags and set the zero flag if the result is zero
    cpu->F = (cpu->A == 0) ? static_cast<uint8_t>(Flags::FLAG_ZERO) : 0x00;
}
void and_d8(CPU* cpu, uint8_t opcode) {
    uint8_t value = read_mem(cpu, cpu->PC++);
    and_a_n(cpu, value);
}
void and_b(CPU* cpu) {
    cpu->A &= cpu->B;

    cpu->F = 0x20;  // Set half carry flag

    if (cpu->A == 0)
        cpu->F |= 0x80;  // Set zero flag
}

// OR Ops
void or_r(CPU* cpu, uint8_t opcode) {
    uint8_t r = opcode & 0x07;
    cpu->A |= cpu->registers[r];

    cpu->flags.Z = (cpu->A == 0);
    cpu->flags.N = 0;
    cpu->flags.H = 0;
    cpu->flags.C = 0;
}
void or_n(CPU* cpu, uint8_t opcode) {
    uint8_t n = read_mem(cpu, cpu->PC++);
    cpu->A |= n;

    cpu->flags.Z = (cpu->A == 0);
    cpu->flags.N = 0;
    cpu->flags.H = 0;
    cpu->flags.C = 0;
}
void or_a_n(CPU* cpu, uint8_t n) {
    cpu->A |= n;
    // Reset flags and set the zero flag if the result is zero
    cpu->F = (cpu->A == 0) ? static_cast<uint8_t>(Flags::FLAG_ZERO) : 0x00;
}
void or_d8(CPU* cpu, uint8_t opcode) {
    uint8_t value = read_mem(cpu, cpu->PC++);
    or_a_n(cpu, value);
}
void or_b(CPU* cpu) {
    cpu->A |= cpu->B;

    cpu->F = 0;

    if (cpu->A == 0)
        cpu->F |= 0x80;  // Set zero flag
}

// XOR Ops
void xor_a_n(CPU* cpu, uint8_t n) {
    cpu->A ^= n;
    // Reset flags and set the zero flag if the result is zero
    cpu->F = (cpu->A == 0) ? static_cast<uint8_t>(Flags::FLAG_ZERO) : 0x00;
}
void xor_r(CPU* cpu, uint8_t opcode) {
    uint8_t r = opcode & 0x07;
    cpu->A ^= cpu->registers[r];

    cpu->flags.Z = (cpu->A == 0);
    cpu->flags.N = 0;
    cpu->flags.H = 0;
    cpu->flags.C = 0;
}
void xor_n(CPU* cpu, uint8_t opcode) {
    uint8_t n = read_mem(cpu, cpu->PC++);
    cpu->A ^= n;

    cpu->flags.Z = (cpu->A == 0);
    cpu->flags.N = 0;
    cpu->flags.H = 0;
    cpu->flags.C = 0;
}
void xor_d8(CPU* cpu, uint8_t opcode) {
    uint8_t value = read_mem(cpu, cpu->PC++);
    xor_a_n(cpu, value);
}

// CP Ops
void cp_r(CPU* cpu, uint8_t opcode) {
    uint8_t r = opcode & 0x07;
    uint8_t result = cpu->A - cpu->registers[r];

    cpu->flags.Z = (result == 0);
    cpu->flags.N = 1;
    cpu->flags.H = ((cpu->A & 0xF) < (cpu->registers[r] & 0xF));
    cpu->flags.C = (cpu->A < cpu->registers[r]);
}
void cp_n(CPU* cpu, uint8_t opcode) {
    uint8_t n = read_mem(cpu, cpu->PC++);
    uint8_t result = cpu->A - n;

    cpu->flags.Z = (result == 0);
    cpu->flags.N = 1;
    cpu->flags.H = ((cpu->A & 0xF) < (n & 0xF));
    cpu->flags.C = (cpu->A < n);
}
void cpl(CPU* cpu, uint8_t opcode) {
    cpu->A = ~cpu->A; // Flip all bits in the A register
    cpu->F |= static_cast<uint8_t>(Flags::FLAG_NEGATIVE) | static_cast<uint8_t>(Flags::FLAG_HALFCARRY); // Set N and H flags
}
void cp_d8(CPU* cpu, uint8_t opcode) {
    uint8_t value = read_mem(cpu, cpu->PC++);
    cp_n(cpu, value);
}

// INC Ops
void inc_r(CPU* cpu, uint8_t opcode) {
    uint8_t r = opcode & 0x07;
    cpu->registers[r]++;

    cpu->flags.Z = (cpu->registers[r] == 0);
    cpu->flags.N = 0;
    cpu->flags.H = ((cpu->registers[r] & 0xF) == 0); // Carry from bit 3
}

// DEC Ops
void dec_r(CPU* cpu, uint8_t opcode) {
    uint8_t r = opcode & 0x07;
    cpu->registers[r]--;

    cpu->flags.Z = (cpu->registers[r] == 0);
    cpu->flags.N = 1;
    cpu->flags.H = ((cpu->registers[r] & 0xF) == 0xF); // Borrow from bit 4
}

// JUMP  Ops
void jp_nn(CPU* cpu, uint8_t opcode) {
    uint16_t nn = read_mem_16(cpu, cpu->PC);
    cpu->PC = nn;
}
void jp_cc_nn(CPU* cpu, uint8_t opcode) {
    uint16_t nn = read_mem_16(cpu, cpu->PC);
    cpu->PC += 2; // advance the PC even if the condition is not met
    uint8_t condition = opcode >> 3 & 0x03;
    // Check condition here, if it's met, jump
}
void jr_n(CPU* cpu, uint8_t opcode) {
    int8_t n = (int8_t)read_mem(cpu, cpu->PC++);
    cpu->PC += n;
}
void jr_cc_n(CPU* cpu, uint8_t opcode) {
    int8_t n = (int8_t)read_mem(cpu, cpu->PC++);
    uint8_t condition = opcode >> 3 & 0x03;
    // Check condition here, if it's met, jump relative
}
void jp_z_a16(CPU* cpu, uint8_t opcode) {
    uint16_t address = read_mem_16(cpu, cpu->PC);
    cpu->PC += 2;
    if (cpu->F & static_cast<uint8_t>(Flags::FLAG_ZERO)) { // If Zero flag is set
        cpu->PC = address; // Jump to the address
    }
}
void jp_nc_a16(CPU* cpu, uint8_t opcode) {
    uint16_t address = read_mem_16(cpu, cpu->PC);
    cpu->PC += 2;
    if (!(cpu->F & static_cast<uint8_t>(Flags::FLAG_CARRY))) { // If Carry flag is not set
        cpu->PC = address; // Jump to the address
    }
}
void jp_c_a16(CPU* cpu, uint8_t opcode) {
    uint16_t address = read_mem_16(cpu, cpu->PC);
    cpu->PC += 2;
    if (cpu->F & static_cast<uint8_t>(Flags::FLAG_CARRY)) { // If Carry flag is set
        cpu->PC = address; // Jump to the address
    }
}
void jr_nz_r8(CPU* cpu, uint8_t opcode) {
    int8_t offset = (int8_t)read_mem(cpu, cpu->PC++);
    if (!(cpu->F & static_cast<uint8_t>(Flags::FLAG_ZERO))) { // If Zero flag is not set
        cpu->PC += offset; // Relative jump by the offset
    }
}
void jr_z_r8(CPU* cpu, uint8_t opcode) {
    int8_t offset = (int8_t)read_mem(cpu, cpu->PC++);
    if (cpu->F & static_cast<uint8_t>(Flags::FLAG_ZERO)) { // If Zero flag is set
        cpu->PC += offset; // Relative jump by the offset
    }
}
void jr_nc_r8(CPU* cpu, uint8_t opcode) {
    int8_t offset = (int8_t)read_mem(cpu, cpu->PC++);
    if (!(cpu->F & static_cast<uint8_t>(Flags::FLAG_CARRY))) { // If Carry flag is not set
        cpu->PC += offset; // Relative jump by the offset
    }
}
void jr_c_r8(CPU* cpu, uint8_t opcode) {
    int8_t offset = (int8_t)read_mem(cpu, cpu->PC++);
    if (cpu->F & static_cast<uint8_t>(Flags::FLAG_CARRY)) { // If Carry flag is set
        cpu->PC += offset; // Relative jump by the offset
    }
}

// CALL Ops
void call_nn(CPU* cpu, uint8_t opcode) {
    uint16_t nn = read_mem_16(cpu, cpu->PC);
    cpu->PC += 2;
    push16(cpu, &(cpu->memory.RAM[cpu->SP]), cpu->PC); // This is assuming SP is the offset in RAM where you want to push the value.
    cpu->PC = nn;
}
void call_cc_nn(CPU* cpu, uint8_t opcode) {
    uint16_t nn = read_mem_16(cpu, cpu->PC);
    cpu->PC += 2; // advance the PC even if the condition is not met
    uint8_t condition = opcode >> 3 & 0x03;
    // Check condition here, if it's met, call nn
}
void call_a16(CPU* cpu, uint8_t opcode) {
    uint16_t address = read_mem_16(cpu, cpu->PC);
    push16(cpu, &(cpu->memory.RAM[cpu->SP]), cpu->PC); // Push the return address
    cpu->PC = address; // Jump to the address
}
void call_z_a16(CPU* cpu, uint8_t opcode) {
    uint16_t address = read_mem_16(cpu, cpu->PC);
    cpu->PC += 2;
    if (cpu->F & static_cast<uint8_t>(Flags::FLAG_ZERO)) { // If Zero flag is set
        push16(cpu, &(cpu->memory.RAM[cpu->SP]), cpu->PC); // Push return address to the stack
        cpu->PC = address; // Jump to the address
    }
}
void call_nc_a16(CPU* cpu, uint8_t opcode) {
    uint16_t address = read_mem_16(cpu, cpu->PC);
    cpu->PC += 2;
    if (!(cpu->F & static_cast<uint8_t>(Flags::FLAG_CARRY))) { // If Carry flag is not set
        push16(cpu, &(cpu->memory.RAM[cpu->SP]), cpu->PC); // Push return address to the stack
        cpu->PC = address; // Jump to the address
    }
}
void call_c_a16(CPU* cpu, uint8_t opcode) {
    uint16_t address = read_mem_16(cpu, cpu->PC);
    cpu->PC += 2;
    if (cpu->F && static_cast<uint8_t>(Flags::FLAG_CARRY)) { // If Carry flag is set
        push16(cpu, &(cpu->memory.RAM[cpu->SP]), cpu->PC); // Push return address to the stack
        cpu->PC = address; // Jump to the address
    }
}

// RETURN Ops
void ret(CPU* cpu, uint8_t opcode) {
    cpu->PC = pop16(cpu, &(cpu->memory.RAM[cpu->SP]));
    cpu->SP += 2; // Since we have popped a 16-bit value off the stack
}
void ret_cc(CPU* cpu, uint8_t opcode) {
    uint8_t condition = opcode >> 3 & 0x03;
    // Check condition here, if it's met, return
}
void reti(CPU* cpu, uint8_t opcode) {
    cpu->PC = pop16(cpu, &(cpu->memory.RAM[cpu->SP]));
    cpu->SP += 2; // Since we have popped a 16-bit value off the stack
    cpu->interruptMasterEnable = true; // Enable interrupts after this instruction
}
void ret_nz(CPU* cpu) {
    if (!(cpu->F & 0x80))  // Check if zero flag is not set
    {
        cpu->PC = (cpu->memory.RAM[cpu->SP++] << 8) | cpu->memory.RAM[cpu->SP++];
    }
}
void ret_nc(CPU* cpu) {
    if (!(cpu->F & 0x10))  // Check if carry flag is not set
    {
        cpu->PC = (cpu->memory.RAM[cpu->SP++] << 8) | cpu->memory.RAM[cpu->SP++];
    }
}

// RESTART Ops
void rst_00h(CPU* cpu, uint8_t opcode) {
    push16(cpu, &(cpu->memory.RAM[cpu->SP]), cpu->PC);
    cpu->PC = 0x00;
}
void rst_08h(CPU* cpu, uint8_t opcode) {
    push16(cpu, &(cpu->memory.RAM[cpu->SP]), cpu->PC);
    cpu->PC = 0x08;
}
void rst_10h(CPU* cpu, uint8_t opcode) {
    push16(cpu, &(cpu->memory.RAM[cpu->SP]), cpu->PC);
    cpu->PC = 0x10;
}
void rst_18h(CPU* cpu, uint8_t opcode) {
    push16(cpu, &(cpu->memory.RAM[cpu->SP]), cpu->PC);
    cpu->PC = 0x18;
}
void rst_20h(CPU* cpu, uint8_t opcode) {
    push16(cpu, &(cpu->memory.RAM[cpu->SP]), cpu->PC);
    cpu->PC = 0x20;
}
void rst_28h(CPU* cpu, uint8_t opcode) {
    push16(cpu, &(cpu->memory.RAM[cpu->SP]), cpu->PC);
    cpu->PC = 0x28;
}
void rst_30h(CPU* cpu, uint8_t opcode) {
    push16(cpu, &(cpu->memory.RAM[cpu->SP]), cpu->PC);
    cpu->PC = 0x30;
}
void rst_38h(CPU* cpu, uint8_t opcode) {
    push16(cpu, &(cpu->memory.RAM[cpu->SP]), cpu->PC);
    cpu->PC = 0x38;
}
void rlca(CPU* cpu, uint8_t opcode) {
    uint8_t top_bit = (cpu->A & 0x80) >> 7;
    cpu->A = (cpu->A << 1) | top_bit;
    cpu->F = (cpu->F & ~(static_cast<uint8_t>(Flags::FLAG_ZERO) | static_cast<uint8_t>(Flags::FLAG_NEGATIVE) | static_cast<uint8_t>(Flags::FLAG_HALFCARRY) | static_cast<uint8_t>(Flags::FLAG_CARRY) | (top_bit << static_cast<uint8_t>(Flags::FLAG_CARRY_SHIFT))));
}
void rrca(CPU* cpu, uint8_t opcode) {
    uint8_t bottom_bit = cpu->A & 0x01;
    cpu->A = (cpu->A >> 1) | (bottom_bit << 7);
    cpu->F = (cpu->F & ~static_cast<uint8_t>(Flags::FLAG_ZERO) | static_cast<uint8_t>(Flags::FLAG_NEGATIVE) | static_cast<uint8_t>(Flags::FLAG_HALFCARRY) | static_cast<uint8_t>(Flags::FLAG_CARRY)) | (bottom_bit << static_cast<uint8_t>(Flags::FLAG_CARRY_SHIFT));
}
void rla(CPU* cpu, uint8_t opcode) {
    uint8_t old_carry = cpu->F & static_cast<uint8_t>(Flags::FLAG_CARRY);
    uint8_t new_carry = (cpu->A & 0x80) >> 7;
    cpu->A = (cpu->A << 1) | (old_carry >> static_cast<uint8_t>(Flags::FLAG_CARRY_SHIFT));
    cpu->F = (cpu->F & ~static_cast<uint8_t>(Flags::FLAG_ZERO) | static_cast<uint8_t>(Flags::FLAG_NEGATIVE) | static_cast<uint8_t>(Flags::FLAG_HALFCARRY) | static_cast<uint8_t>(Flags::FLAG_CARRY)) | (new_carry << static_cast<uint8_t>(Flags::FLAG_CARRY_SHIFT));
}

// MISC Ops
void stop_0(CPU* cpu, uint8_t opcode) {
    // Not supported - Game Boy stops until next interrupt
}
void halt(CPU* cpu, uint8_t opcode) {
    cpu->halt = true; // Set halt mode on
}
void bit_b_r(CPU* cpu, uint8_t opcode) {
    uint8_t bitNumber = (opcode >> 3) & 0x07;
    uint8_t r = opcode & 0x07;
    uint8_t bit = (cpu->registers[r] >> bitNumber) & 0x01;
    // set Zero flag if bit is 0, reset otherwise
}
void set_b_r(CPU* cpu, uint8_t opcode) {
    uint8_t bitNumber = (opcode >> 3) & 0x07;
    uint8_t r = opcode & 0x07;
    cpu->registers[r] |= (1 << bitNumber);
}
void res_b_r(CPU* cpu, uint8_t opcode) {
    uint8_t bitNumber = (opcode >> 3) & 0x07;
    uint8_t r = opcode & 0x07;
    cpu->registers[r] &= ~(1 << bitNumber);
}
void nop(CPU* cpu, uint8_t opcode) {
    // No operation - do nothing
}
void di(CPU* cpu, uint8_t opcode) {
    cpu->interruptMasterEnable = false; // Disable interrupts
}
void ei(CPU* cpu, uint8_t opcode) {
    cpu->interruptMasterEnable = true; // Enable interrupts
}
void rra(CPU* cpu, uint8_t opcode) {
    uint8_t old_carry = cpu->F & static_cast<uint8_t>(Flags::FLAG_CARRY);
    uint8_t new_carry = cpu->A & 0x01;
    cpu->A = (cpu->A >> 1) | (old_carry << 7);
    cpu->F = (cpu->F & ~static_cast<uint8_t>(Flags::FLAG_ZERO) | static_cast<uint8_t>(Flags::FLAG_NEGATIVE) | static_cast<uint8_t>(Flags::FLAG_HALFCARRY) | static_cast<uint8_t>(Flags::FLAG_CARRY)) | (new_carry << static_cast<uint8_t>(Flags::FLAG_CARRY_SHIFT));
}
void daa(CPU* cpu, uint8_t opcode) {
    uint16_t correction = cpu->F & static_cast<uint8_t>(Flags::FLAG_CARRY);
    if (cpu->F & static_cast<uint8_t>(Flags::FLAG_HALFCARRY) || (cpu->A & 0x0F) > 9) {
        correction |= 0x06;
    }
    if (cpu->F & static_cast<uint8_t>(Flags::FLAG_CARRY) || cpu->A > 0x99) {
        correction |= 0x60;
    }
    cpu->A += cpu->F & static_cast<uint8_t>(Flags::FLAG_NEGATIVE) ? -correction : correction;
    cpu->F = (cpu->F & ~(static_cast<uint8_t>(Flags::FLAG_ZERO) | static_cast<uint8_t>(Flags::FLAG_HALFCARRY) | static_cast<uint8_t>(Flags::FLAG_CARRY))) |
        (cpu->A ? 0 : static_cast<uint8_t>(Flags::FLAG_ZERO)) |
        ((cpu->F & static_cast<uint8_t>(Flags::FLAG_NEGATIVE)) ? static_cast<uint8_t>(Flags::FLAG_NEGATIVE) : 0) |
        (correction >= 0x60 ? static_cast<uint8_t>(Flags::FLAG_CARRY) : 0);
}
void scf(CPU* cpu, uint8_t opcode) {
    cpu->F = (cpu->F & ~static_cast<uint8_t>(Flags::FLAG_NEGATIVE) | static_cast<uint8_t>(Flags::FLAG_HALFCARRY)) | static_cast<uint8_t>(Flags::FLAG_CARRY);
}
void ccf(CPU* cpu, uint8_t opcode) {
    cpu->F = (cpu->F & ~static_cast<uint8_t>(Flags::FLAG_NEGATIVE) | static_cast<uint8_t>(Flags::FLAG_HALFCARRY)) ^ static_cast<uint8_t>(Flags::FLAG_CARRY);
}
