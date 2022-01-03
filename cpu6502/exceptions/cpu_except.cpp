#include "cpu_except.hpp"

namespace cpu6502::exceptions{

const char * infinite_loop::what () const noexcept
{
    return "Cycles counter don't change, propably infinity loop.";
}

}