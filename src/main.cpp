#include "memory.hpp"
#include "cpu.hpp"

// Test JMP 
Byte test_program[] = {
  0x10, 0x00, 0x0A, // MVI A, 10
  0x13, 0x09, 0x00, // JMP [0x0009]
  0x10, 0x00, 0x05, // MVI A, 5
  0xFF,             // HLT
};

int main() {
  Tundra::Memory mem;
  Tundra::CPU    cpu;

  std::size_t test_program_size = sizeof(test_program) / sizeof(test_program[0]);

  // Write the program in the memory
  for(std::size_t i=0;i<test_program_size;++i) {
    cpu.WriteCycle(mem, static_cast<Address>(i), test_program[i]);
  }

  // Execute
  while(!cpu.isHalted()) {
    cpu.step(mem);
  }

  std::println("Value at reg  A: 0x{:02X}", cpu.GetRegister(Tundra::Register::A));
  cpu.ReadFlagStatus();
  return 0;
}
