
#include <stdint.h>
#include <stdio.h>



typedef struct Registers{
  uint16_t af, bc, de, hl, sp;
} Registers;


uint16_t stepHomeworkInstruction(void* mem, struct Registers* regs, uint16_t* pc,
    uint8_t(*readMemory)(void*, uint16_t), void(*writeMemory)(void*, uint16_t, uint8_t)){

  uint8_t opcode = readMemory(mem, *pc);
  return 0;
}
