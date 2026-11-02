#pragma once
#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include <cstdint>
#include <print>

using Byte    = std::uint8_t;
using Address = std::uint16_t;

constexpr std::size_t MAX_MEM_SIZE = (1024 * 64);


namespace Tundra {
	// Opcodes
	enum class Opcode : Byte {
		NOP = 0x00, // NO OPERATION
		MVI = 0x10, // Move Immediate  [ MVI reg, val ]
		ADI = 0x11, // ADD  Immediate  [ ADI reg, val ]
		STA = 0x12, // STORE           [ STA mem_add, {reg Value} ]
		// TODO: Implement JMP instruction
		JMP = 0x12, // JUMP [JMP mem_add]

	  	HLT = 0xFF, // TERMINATE/HALT
	};

	enum class Register : Byte {
	  A = 0x00, // Accumulator
	  B = 0x01,
	  C = 0x02,
	  D = 0x03,
	  E = 0x04,
	  H = 0x05, // HIGH
	  L = 0x06, // LOW
	};

	// TODO: Define Errors with proper types
	// enum class Error {
	// };
};

#endif
