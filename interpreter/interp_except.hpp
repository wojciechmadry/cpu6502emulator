#ifndef INTERPRETER_EXCEPTIONS
#define INTERPRETER_EXCEPTIONS

#include <exception>

namespace cpu6502::interpreter::exceptions{

class empty_instruction : public std::exception
{
    public:
    empty_instruction() noexcept;
    const char * what () const noexcept override;
};

class bad_instruction_size : public std::exception
{
    public:
    bad_instruction_size() noexcept;
    const char * what () const noexcept override;
};

class bad_addressing_mode : public std::exception
{
    public:
    bad_addressing_mode() noexcept;
    const char * what () const noexcept override;
};

class bad_label_value : public std::exception
{
    public:
    bad_label_value() noexcept;
    const char * what () const noexcept override;
};

}  // ns cpu6502::interpreter::exceptions
#endif  // INTERPRETER_EXCEPTIONS
