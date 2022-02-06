
#include <stdint.h>
#include <stdio.h>

#include "assignment1.h"


typedef struct Registers{
  uint16_t af, bc, de, hl, sp;
} Registers;


//return the LSB of the 2-byte value
uint8_t getLow(uint16_t reg){
  return reg;
}

//set the LSB of the 2-byte value pointed to by reg_p to val
void setLow(uint16_t* reg_p, uint8_t val){
  *reg_p &= 0xFF00;
  *reg_p |= val;
}

//return the MSB of the 2-byte value
uint8_t getHigh(uint16_t reg){
  return reg >> 8;
}

//set the MSB of the 2-byte value pointed to by reg_p to val
void setHigh(uint16_t* reg_p, uint8_t val){
  *reg_p &= 0xFF;
  *reg_p |=  ((uint16_t)val) << 8;
}

//set the i'th bit of the value pointed to by reg_p to 1
void setBit(uint16_t* reg_p, uint8_t i){
  *reg_p |= (1 << i);
}

//set the i'th bit of the value pointed to by reg_p to 0
void clearBit(uint16_t* reg_p, uint8_t i){
  *reg_p &= ~(1 << i);
}

//p points to LSB of imm, This advances p past the imm
uint16_t readImm16(void* mem, uint8_t(*readMemory)(void*, uint16_t), uint16_t* p){
  uint16_t l = readMemory(mem, *p);
  ++(*p);
  uint16_t h = readMemory(mem, *p);
  ++(*p);
  return (h << 8) | l;
}


uint16_t stepHomeworkInstruction(void* mem, struct Registers* regs, uint16_t* pc,
    uint8_t(*readMemory)(void*, uint16_t), void(*writeMemory)(void*, uint16_t, uint8_t)){

  uint8_t opcode = readMemory(mem, *pc);
  //printf("student code, opcode: %x\n", opcode);
  if(opcode == 0x3E){ //ld a, imm
    ++(*pc);
    uint8_t val = readMemory(mem, *pc);
    setHigh(&(regs->af), val);
    ++(*pc);
    return 2;
  } else if(opcode == 0xC3){ //jump a16

    ++(*pc);
    uint16_t imm = readImm16(mem, readMemory, pc);
    *pc = imm;
    return 4;
  } else if(opcode == 0x3C){ //inc a

    uint16_t* af = &(regs->af);
    uint8_t oldA = getHigh(*af);
    uint8_t newA = oldA + 1;

    setHigh(af, newA);

    if(newA == 0){
      setBit(af, 7);
    } else {
      clearBit(af, 7);
    }

    clearBit(af, 6);

    if(oldA > newA){
      setBit(af, 5);
    } else {
      clearBit(af, 5);
    }

    ++(*pc);
    return 1;
  } else if(opcode == 0xEA){ //ld [imm16], a
    ++(*pc);
    uint16_t imm = readImm16(mem, readMemory, pc);
    writeMemory(mem, imm, getHigh(regs->af));
    return 4;
  } else if(opcode == 0x22){ //ld [hl+], a
    writeMemory(mem, (regs->hl)++, getHigh(regs->af));
    ++(*pc);
    return 2;
  } else if(opcode == 0x3A){ //ld a, [hl-]
    setHigh(&(regs->af), readMemory(mem, (regs->hl)--));
    ++(*pc);
    return 2;
  } else if(opcode == 0x32){ //ld [hl-], a
    writeMemory(mem, (regs->hl)--, getHigh(regs->af));
    ++(*pc);
    return 2;
  } else if(opcode == 0x2A){ //ld a, [hl+]
    setHigh(&(regs->af), readMemory(mem, (regs->hl)++));
    ++(*pc);
    return 2;
  } else if(opcode == 0xC6){//add a, imm8
    ++(*pc);
    uint8_t imm = readMemory(mem, *pc);
    ++(*pc);

    uint8_t oldA = getHigh(regs->af);
    uint8_t nibble = (imm & 0xF) + (oldA & 0xF);
    uint8_t newA = oldA + imm;

    uint16_t* af = &(regs->af);
    setHigh(af, newA);
    
    if(newA == 0){
      setBit(af, 7);
    } else {
      clearBit(af, 7);
    }

    clearBit(af, 6);

    if(nibble > 0xF){
      setBit(af, 5);
    } else {
      clearBit(af, 5);
    }

    if(newA < oldA){
      setBit(af, 4);
    } else {
      clearBit(af, 4);
    }

    return 2;
  } else if(opcode == 0xD6){ //sub a, imm8
    ++(*pc);
    uint8_t imm = readMemory(mem, *pc);
    ++(*pc);
    uint8_t oldA = getHigh(regs->af);
    uint8_t nibble = (oldA & 0xF) - (imm & 0xF);
    uint8_t newA = oldA - imm;

    uint16_t* af = &(regs->af);
    setHigh(af, newA);

    if(newA == 0){
      setBit(af, 7);
    } else {
      clearBit(af, 7);
    }

    setBit(af, 6);
    if(nibble > 0xF){
      setBit(af, 5);
    } else {
      clearBit(af, 5);
    }

    if(newA > oldA){
      setBit(af, 4);
    } else {
      clearBit(af, 4);
    }

    return 2;
  } else if(opcode == 0x1F) { //rotate right a

    ++(*pc);
    uint8_t oldCarry = (regs->af >> 4) & 1;
    uint8_t oldA = getHigh(regs->af);

    uint8_t newA = (oldA >> 1) | (oldCarry << 7);

    uint16_t* af = &(regs->af);
    setHigh(af, newA);

    if(oldA & 1){
      setBit(af, 4);
    } else {
      clearBit(af, 4);
    }
    clearBit(af, 7);
    clearBit(af, 6);
    clearBit(af, 5);

    return 1;
  } else if(opcode == 0xFE){ //compare a, imm8
    ++(*pc);
    uint8_t imm = readMemory(mem, *pc);
    ++(*pc);

    uint8_t oldA = getHigh(regs->af);
    uint8_t nibble = (oldA & 0xF) - (imm & 0xF);
    uint8_t newA = oldA - imm;

    uint16_t* af = &(regs->af);

    if(newA == 0){
      setBit(af, 7);
    } else {
      clearBit(af, 7);
    }

    setBit(af, 6);

    if(nibble > 0xF){
      setBit(af, 5);
    } else {
      clearBit(af, 5);
    }

    if(newA > oldA){
      setBit(af, 4);
    } else {
      clearBit(af, 5);
    }

    return 2;

  } else if(opcode == 0xCA){ //jp z, imm16
    ++(*pc);
    uint16_t imm = readImm16(mem, readMemory, pc);
    if(getLow(regs->af) >> 7){
      *pc = imm ;
      return 4;
    } else {
      return 3;
    }

  } else if(opcode == 0xDA){ //jp c, imm16
    ++(*pc);
    uint16_t imm = readImm16(mem, readMemory, pc);
    if(getLow(regs->af) >> 4){
      *pc = imm;
      return 4;
    } else {
      return 3;
    }

  } else if(opcode == 0x18){ //jr, signed imm8
    ++(*pc);
    int8_t offset = readMemory(mem, *pc);
    (*pc) += offset + 1;
    return 3;
  } else if(opcode == 0xC5){ //push BC
    ++(*pc);
    regs->sp -= 2;
    writeMemory(mem, regs->sp, getLow(regs->bc));
    writeMemory(mem, regs->sp + 1, getHigh(regs->bc));
    return 4;
  } else if(opcode == 0xD1){ //pop DE
    ++(*pc);
    setLow(&(regs->de), readMemory(mem, regs->sp));
    setHigh(&(regs->de), readMemory(mem, regs->sp + 1));
    regs->sp += 2;
    return 3;
  } else if(opcode == 0xCD) { //call imm16
    ++(*pc);
    uint16_t imm = readImm16(mem, readMemory, pc);
    regs->sp -= 2;
    writeMemory(mem, regs->sp, getLow(*pc));
    writeMemory(mem, regs->sp + 1, getHigh(*pc));
    *pc = imm;
    return 6;
  } else if(opcode == 0xC9) { //ret
    uint16_t l = readMemory(mem, regs->sp);
    uint16_t h = readMemory(mem, regs->sp + 1);
    regs->sp += 2;
    *pc = (h<<8) | (l);
    return 4;
  }



  return -1;
}
