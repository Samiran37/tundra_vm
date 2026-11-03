// #pragma once
#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include <cstdint>
#include <print>
#include <expected>

using Byte    = std::uint8_t;
using Address = std::uint16_t;

constexpr std::size_t MAX_MEM_SIZE    = (1024 * 64); // 64KB
inline constexpr Address STACK_TOP    = { 0xFFFF };  //
inline constexpr Address STACK_BOTTOM = { 0xFF00 };  // Total size 255KB for the stack


namespace Tundra {
	// Opcodes
	enum class Opcode : Byte {
		NOP = 0x00, // NO OPERATION
		MVI = 0x10, // Move Immediate  [ MVI reg, val ]
		ADI = 0x11, // ADD  Immediate  [ ADI reg, val ]
		STA = 0x12, // STORE           [ STA mem_add, {reg Value} ]
		
		JMP = 0x13, // JUMP [JMP mem_add]
		
		PUSH = 0x14, // PUSH [mem_add]
		POP  = 0x15, // POP

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
	enum class Error {
		OK,
		STACK_OVERFLOW,
		STACK_UNDERFLOW,
		ILLEGAL_INSTRUCTION,
		UNKNOWN_INSTRUCTION,
		ILLEGAL_REGISTER_ID,
		DIV_BY_ZERO,
	};
	constexpr Address GetAddressFromLH(Byte low, Byte high) {
		return static_cast<Address>(high << 8) | static_cast<Address>(low); 
	}
	constexpr std::expected<Byte, Error> ValidateRegisterID(Byte regID) {
		if(regID > static_cast<Byte>(Register::L)) {
			return std::unexpected(Error::ILLEGAL_REGISTER_ID);
		}
		return regID;
	}
};

#endif // DEFINITIONS_HPP
