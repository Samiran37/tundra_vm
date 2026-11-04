#include "memory.hpp"
#include "cpu.hpp"


// program
Byte program[] {
  0x10, 0x01, 0x01, // MVI B, 0x01
  0x11, 0x00, 0x01, // ADI A, B
  0x13, 0x00, 0x00, // JMP 0x0000
};

int main() {
  Tundra::Memory mem;
  Tundra::CPU    cpu;

  // std::size_t test_program_size = sizeof(test_program) / sizeof(test_program[0]);
  std::size_t program_size = sizeof(program) / sizeof(program[0]);
  // Write the program in the memory
  for(std::size_t i=0;i<program_size;++i) {
    cpu.WriteCycle(mem, static_cast<Address>(i), program[i]);
  }

  // Execute
  for(std::size_t i=0;i<100;++i) {
    cpu.step(mem);
    std::println("Reg A: 0x{:02X}", cpu.GetRegister(Tundra::Register::A));
  }

  return 0;
}
