#include "cpu.hpp"

void Tundra::CPU::FetchCycle(Memory &mem) {
	IR = FetchByte(mem);
}

void Tundra::CPU::ExecuteCycle(Memory &mem) {
	if(halted) {
		return;
	}
	switch(static_cast<Opcode>(IR)) {
	case Opcode::NOP: break; // Do Nothing
	case Opcode::MVI: {
		Byte regID = FetchByte(mem);
        if(regID > static_cast<Byte>(Register::L)) {
          std::println("[Error]: Invalid Register ID {}", regID);
          halted = true;
          break;
      	}
        
	    Register reg = static_cast<Register>(regID);
	    Byte     val = FetchByte(mem); 
	    SetRegister(reg, val);
	    break;
	}
	case Opcode::ADI: {
		Byte regID = FetchByte(mem);
		if(regID > static_cast<Byte>(Register::L)) {
			std::println("[Error]: Invalid Register ID {}", regID);
			halted = true;
			break;
		}
		Register reg = static_cast<Register>(regID);
		Byte     val = FetchByte(mem); 
		
		// Get the original Register value
    Byte lhs = GetRegister(reg);

		// Store Result in wider integer
		std::uint16_t result = static_cast<std::uint16_t>(GetRegister(reg)) + static_cast<std::uint16_t>(val);

		Byte res = static_cast<Byte>(result);

		SetRegister(reg, res); // Set res value to register

		Zero = (res == 0); // If res is zero, zero flag is set
		Negative = (res & 0x80) != 0; // If the 8th bit is not zero, Negative flag is set
		Carry    = (result > 0xFF);   // If the result overflows beyound 8 bit, Carray flag is set
		Overflow = ((~(lhs ^ val) & (lhs ^ res) & 0x80) != 0); // WHAT THE FUCK???		
		break;
	}
	case Opcode::STA: { 
		Byte low   = FetchByte(mem); // Low Address
	    Byte high  = FetchByte(mem); // High Address
	    Byte regID = FetchByte(mem);
	    if(regID > static_cast<Byte>(Register::L)) {
	       std::println("[Error]: Invalid Register ID {}", regID);
	       halted = true;
	       break;
	    }
	    Register reg = static_cast<Register>(regID);
	    Address add = static_cast<Address>((static_cast<Address>(high) << 8) | (low));
	    Byte val = GetRegister(reg);
	    WriteCycle(mem, add, val);
	    break;
	}
	// TODO: Implement JMP instruction
	case Opcode::JMP: {
		Byte low  = FetchByte(mem); // Fetch Low address
		Byte high = FetchByte(mem); // Fetch high address

		Address add = static_cast<Address>(high << 8) | static_cast<Address>(low);
		PC = add;
		break;
	}
	case Opcode::HLT: 
		halted = true;
		break;
	default:
		std::println("[Error]: Unknown Opcode {}", IR);
		halted = true;
		break;

	}
}

void Tundra::CPU::step(Memory &mem) {
	FetchCycle(mem);
	ExecuteCycle(mem);
}

void Tundra::CPU::reset() {
	PC        = { 0x0000 };
	registers = { 0 };
	IR 		  = { 0 };
	MAR 	  = { 0x0000 };
	MDR 	  = { 0x0 };
	Zero 	  = { false };
	Negative  = { false };
	Overflow  = { false };
	Carry 	  = { false };
}
