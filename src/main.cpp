#include "memory.hpp"
#include "cpu.hpp"

Byte test_program[] = {
  0x10, 0x00, 0x0F,        // MVI A, 10
  0x11, 0x00, 0x01,        // ADI A, 1
  0x12, 0x34, 0x12, 0x00, // STA [0x1234], A ; Res should be 11 or B
  0xFF,                   // HLT
};

int main() {
  Memory mem;
  CPU    cpu;

  std::size_t test_program_size = sizeof(test_program) / sizeof(test_program[0]);

  // Write the program in the memory
  for(std::size_t i=0;i<test_program_size;++i) {
    cpu.WriteCycle(mem, static_cast<Address>(i), test_program[i]);
  }

  // Execute
  while(!cpu.halted) {
    cpu.step(mem);
  }

  Address add = { 0x1234 };
  std::println("Mem add[0x1234]: 0x{:02X}", mem.Read(add));
  return 0;
}
