#ifndef CPU_EXCEPT_HPP
#define CPU_EXCEPT_HPP

#include <exception>
#include <stdexcept>

namespace cpu6502::exceptions{

class infinite_loop : public std::exception
{
    const char * what () const noexcept override;
};

}

#endif  // CPU_EXCEPT_HPP
