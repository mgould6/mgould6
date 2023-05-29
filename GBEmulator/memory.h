#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

typedef struct {
    uint8_t data[0x10000];   // 64 KB of memory
    uint8_t io[0x100];       // 256 I/O ports
} Memory;

// Function declarations

uint8_t read_mem(Memory* memory, uint16_t address);
void write_mem(Memory* memory, uint16_t address, uint8_t value);
uint16_t read_mem_16(Memory* memory, uint16_t address);
uint8_t read_io(Memory* memory, uint16_t port);
void write_io(Memory* memory, uint16_t port, uint8_t value);


#endif /* MEMORY_H */
