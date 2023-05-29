#include "memory.h"
#include "cpu.h"

uint8_t read_mem(Memory* memory, uint16_t address) {
    return memory->data[address];
}

void write_mem(Memory* memory, uint16_t address, uint8_t value) {
    memory->data[address] = value;
}

uint16_t read_mem_16(Memory* memory, uint16_t address) {
    uint16_t low = memory->data[address];
    uint16_t high = memory->data[address + 1];
    return (high << 8) | low;
}

uint8_t read_io(Memory* memory, uint16_t port) {
    return memory->io[port & 0xFF];
}

void write_io(Memory* memory, uint16_t port, uint8_t value) {
    memory->io[port & 0xFF] = value;
}

