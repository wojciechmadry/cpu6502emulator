#ifndef CPU_6502_required
#define CPU_6502_required

#include <cstdint>
#include <functional>
#include <utility>
#include <vector>

namespace cpu6502 {
using SByte = int8_t;
using Byte = uint8_t;
using Word = uint16_t;
using SWord = int16_t;
using u32 = uint32_t;
using u64 = uint64_t;

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
