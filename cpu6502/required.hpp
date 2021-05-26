#ifndef CPU_6502_required
#define CPU_6502_required

#include <vector>
#include <utility>
#include <functional>
#include <cassert>
#include <cstdint>

#include <iostream> // REMEMBER TO DELETE

namespace cpu6502
{
    using SByte = int8_t;
    using Byte = uint8_t;
    using Word = uint16_t;
    using u32 = uint32_t;
    using u64 = uint64_t;
}

#endif