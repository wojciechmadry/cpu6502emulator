#ifndef INTERPRETER_CPU6502
#define INTERPRETER_CPU6502

#include "cpu.hpp"
#include "instruction.hpp"
#include "utility.hpp"

#include <functional>
#include <string>
#include <string_view>
#include <cstdint>
#include <unordered_map>
#include <cstdint>
#include <vector>
#include <list>
#include <optional>

namespace cpu6502::interpreter
{
    class Interpreter
    {
        public:

        using INTERPRETER_CLONE_TYPE = std::pair<std::unordered_map<std::string, std::uint32_t>, CPU::CPU_CLONE_PAIR_TYPE>;

        Interpreter() = delete;

        Interpreter(Interpreter& other) noexcept;

        Interpreter(Interpreter&& other) noexcept = delete;

        Interpreter(const Interpreter& other) noexcept = delete;

        Interpreter(cpu6502::CPU& cpu) noexcept;

        ~Interpreter() noexcept = default;

        Interpreter& operator=(Interpreter&&) = delete;

        Interpreter& operator=(const Interpreter&) = delete;

        void reset();

        void debug_mode_change_command(utils::DebugModeNextCommand next_command);

        cpu6502::CPU& get_cpu() noexcept;

        const cpu6502::CPU& get_cpu() const noexcept;

        Addressing interprete(std::string_view line);

        void add_label(std::string label_name, const std::uint32_t address);

        const std::unordered_map<std::string, std::uint32_t>& get_labels() const noexcept;

        void clear_labels() noexcept;

        void load_asm(const std::string& filename) noexcept;

        void execute_asm();

        std::vector<std::string>& get_commands();

        const std::vector<std::string>& get_commands() const;

        void set_states_to_remember(std::uint32_t state_to_remember) noexcept;

        std::uint32_t get_states_to_remember() const noexcept;
        
        void load_state(std::list<INTERPRETER_CLONE_TYPE>::iterator it_state);

        std::optional<std::list<INTERPRETER_CLONE_TYPE>::iterator> get_current_state() const noexcept;

        INTERPRETER_CLONE_TYPE clone() const noexcept;
        
        const std::list<INTERPRETER_CLONE_TYPE>& get_debug_states() const noexcept;
        
        private:
        
        // CPU 6502 reference
        std::reference_wrapper<cpu6502::CPU> m_cpu;
        
        // Created labels
        std::unordered_map<std::string, std::uint32_t> m_labels;
        
        // Loaded .asm commands
        std::vector<std::string> m_asm_commands;

        // How many state should be remembered
        std::uint32_t m_debug_state_to_remember{0};

        // All remembered state
        std::list<INTERPRETER_CLONE_TYPE> m_debug_states;

        // Actual state
        std::list<INTERPRETER_CLONE_TYPE>::iterator m_debug_actual_state;

        void insert_new_state();

        Addressing load_instruction(std::string_view address, const InstructionInfo& info);
        
        bool create_label_instruction(std::string_view command);

        bool is_comment(std::string_view line) const noexcept;

        void debug_go_right();

        void debug_go_left();
    };

} // namespace cpu6502::interpreter

#endif  // INTERPRETER_CPU6502
