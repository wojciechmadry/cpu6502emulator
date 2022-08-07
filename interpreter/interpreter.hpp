#ifndef INTERPRETER_CPU6502
#define INTERPRETER_CPU6502

#include "cpu.hpp"
#include "instruction.hpp"

#include <functional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <cstdint>

namespace cpu6502::interpreter
{
    class Interpreter
    {
        std::reference_wrapper<cpu6502::CPU> m_cpu;
        std::unordered_map<std::string, std::uint32_t> m_labels;

        Addressing load_instruction(std::string_view address, const InstructionInfo& info);
        
        public:

        Interpreter() = delete;

        Interpreter(Interpreter& other) noexcept;

        Interpreter(Interpreter&& other) noexcept = delete;

        Interpreter(const Interpreter& other) noexcept = delete;

        Interpreter(cpu6502::CPU& cpu) noexcept;

        ~Interpreter() noexcept = default;

        Interpreter& operator=(Interpreter&&) = delete;

        Interpreter& operator=(const Interpreter&) = delete;

        cpu6502::CPU& get_cpu() noexcept;

        const cpu6502::CPU& get_cpu() const noexcept;

        Addressing interprete(std::string_view line);

        void add_label(std::string label_name, const std::uint32_t address) noexcept;

        void clear_labels() noexcept;

    };

} // namespace cpu6502::interpreter

#endif  // INTERPRETER_CPU6502
