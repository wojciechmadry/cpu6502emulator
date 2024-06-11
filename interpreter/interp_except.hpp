#ifndef INTERPRETER_EXCEPTIONS
#define INTERPRETER_EXCEPTIONS

#include <exception>

namespace cpu6502::interpreter::exceptions {

class empty_instruction : public std::exception {
public:
  empty_instruction() noexcept;
  [[nodiscard]] const char *what() const noexcept override;
};

class bad_instruction_size : public std::exception {
public:
  bad_instruction_size() noexcept;
  [[nodiscard]] const char *what() const noexcept override;
};

class bad_addressing_mode : public std::exception {
public:
  bad_addressing_mode() noexcept;
  [[nodiscard]] const char *what() const noexcept override;
};

class bad_label_value : public std::exception {
public:
  bad_label_value() noexcept;
  [[nodiscard]] const char *what() const noexcept override;
};

} // namespace cpu6502::interpreter::exceptions
#endif // INTERPRETER_EXCEPTIONS
