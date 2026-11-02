// #pragma once
#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <array>
#include "definitions.hpp"

namespace Tundra {
  class Memory {
  private:
    std::array<Byte, MAX_MEM_SIZE> storage{};

  public:

    // Reads the data from given address
    Byte Read(Address add) {
      return storage[add];
    }

    // Writes the data to the given address
    void Write(Address add, Byte data) {
      storage[add] = data;
    }
  };
};
#endif // MEMORY_HPP
