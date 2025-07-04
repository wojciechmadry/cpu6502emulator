#ifndef CPU_6502_required
#define CPU_6502_required

#include <cstdint>
#include <functional>
#include <utility>
#include <vector>

namespace cpu6502 {
using SByte = std::int8_t;
using Byte = std::uint8_t;
using Word = std::uint16_t;
using SWord = std::int16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

enum class AddressingMode : Byte {
  Immediate,
  ZeroPage,
  ZeroPageX,
  ZeroPageY,
  Absolute,
  AbsoluteX,
  AbsoluteY,
  Indirect,
  IndirectX,
  IndirectY
};

} // namespace cpu6502

#endif
