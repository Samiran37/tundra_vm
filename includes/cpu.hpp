#pragma once
#ifndef CPU_HPP
#define CPU_HPP
#include "definitions.hpp"
#include "memory.hpp"

using Register = Tundra::Register;
using Opcode   = Tundra::Opcode;

class CPU {
private:
  // 7 General Purpose Registers: A, B, C, D, E, H, L
  std::array<Byte, 7> registers{};

  // Special Registers
  // Address SP = { 0xFFFF }; // STACK POINTER
  Address PC = { 0 };    // PROGRAM COUNTER --> Currently points at the last address of the memory
  Byte    IR = { 0 };    // INSTRUCTION REGISTER
  
  // Interface registers to connect our CPU to the Memory
  Address MAR = { 0x0000 }; // MEMORY ADDRESS REGISTER
  Byte    MDR = { 0x0 };    // MEMORY DATA REGISTER

  // FLAGS
  bool Zero     = false;
  bool Carry    = false;
  bool Negative = false;
  bool Overflow = false;
 
  
public:
  bool halted = { false };

  void ReadCycle(Memory &mem, Address add) {
    MAR = add;
    MDR = mem.Read(add);
  }
  void WriteCycle(Memory &mem, Address add, Byte data) {
    MAR = add;
    MDR = data;
    mem.Write(add, data);
  }
  Byte FetchByte(Memory &mem) {
    ReadCycle(mem, PC);
    PC++;
    return MDR;
  }

  // Get Register by the register ID
  Byte GetRegister(Register reg) {
    return registers[static_cast<std::size_t>(reg)]; // Get the register by its corresponding index
  }

  // Set the value of the register by ID
  void SetRegister(Register reg, Byte value) {
    // Set the value to the register by its corresponding index
    registers[static_cast<std::size_t>(reg)] = value; 
  }

  void FetchCycle(Memory &mem);
  void ExecuteCycle(Memory &mem);
  
  void step(Memory &mem);
  void reset();
};

#endif
