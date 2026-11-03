#include "memory.hpp"
#include "cpu.hpp"

// Test JMP 
Byte test_program[] = {
  0x10, 0x00, 0x11, // MVI A, 0x11
  0x10, 0x01, 0x22, // MVI B, 0x22
  0x14, 0x00,       // PUSH A
  0x14, 0x01,       // PUSH B
  0x15, 0x02,       // POP C ; C should have val of B
  0x15, 0x03,       // POP D ; D should have val of A
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

  std::println("Value at reg C: 0x{:02X}", cpu.GetRegister(Tundra::Register::C));
  std::println("Value at reg D: 0x{:02X}", cpu.GetRegister(Tundra::Register::D));
  cpu.ReadFlagStatus();
  return 0;
}
