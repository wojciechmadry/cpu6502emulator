#ifndef INTERPRETER_INSTRUCTION
#define INTERPRETER_INSTRUCTION

#include <string>
#include <vector>
#include <cstdint>

namespace cpu6502::interpreter
{
    enum class Addressing
    {
        Implicit = 0,
        Accumulator,
        Immediate,
        ZeroPage,
        ZeroPageX,
        ZeroPageY,
        Relative,
        Absolute,
        AbsoluteX,
        AbsoluteY,
        Indirect,
        IndirectX,
        IndirectY,
        NUM_OF_ADDRESSING,
        BAD_ADDRESING_MODE,
        Comment,
        CreateLabel
    };

    std::string_view address_enum_to_str(const Addressing addressing_mode);

    enum class AVL_type
    {
        address,
        value,
        label,
        none
    };

    enum class ADDITIONAL_info
    {
        LO,
        HI,
        none
    };
    
    enum class VALUE_TYPE
    {
        binary = 2,
        decimal = 10,
        hex = 16
    };

    static_assert(static_cast<int>(Addressing::NUM_OF_ADDRESSING) == 13, "There are 13 addressing mode");

    class InstructionInfo
    {
        public:
        class SmallAddressInfo
        {
            Addressing m_mode = Addressing::BAD_ADDRESING_MODE;
            int m_op = 255;

            public:

            [[nodiscard]] int get_op_code() const noexcept;
            [[nodiscard]] Addressing get_mode() const noexcept;
            void set_op_code(int op) noexcept;
            void set_mode(Addressing mode) noexcept;
        };

        private:

        std::string m_instruction_name;
        std::vector<SmallAddressInfo> m_possible_addressing_mode;

        public:

        [[nodiscard]] const std::string& get_instruction_name() const noexcept;

        std::string& get_instruction_name() noexcept;

        [[nodiscard]] const std::vector<SmallAddressInfo>& get_addressing_vector() const noexcept;

        void add_address(const SmallAddressInfo sAi) noexcept;
        
    };
    
    class AddressInfo
    {

        // Address or value or label - type
        AVL_type m_type = AVL_type::none;
        // Address or value or label - value
        std::string m_value;
        // Addressing mode
        Addressing m_mode;
        // Additional info like HI/LO
        ADDITIONAL_info m_info = ADDITIONAL_info::none;
        // Value base value (binary/hex/decimal)
        VALUE_TYPE m_value_type = VALUE_TYPE::decimal;

        public:
        
        static AddressInfo create_address(Addressing mode, AVL_type avl = AVL_type::none, std::string_view value = "", VALUE_TYPE value_type = VALUE_TYPE::hex) noexcept;
        
        [[nodiscard]] std::uint32_t get_val_as_uint32() const;

        [[nodiscard]] VALUE_TYPE get_value_type() const noexcept;

        void set_value_type(const VALUE_TYPE value_type) noexcept;

        [[nodiscard]] AVL_type get_avl() const noexcept;

        void set_avl(AVL_type type) noexcept;

        [[nodiscard]] const std::string& get_value() const noexcept;

        void set_value(std::string value) noexcept;

        [[nodiscard]] Addressing get_mode() const noexcept;

        void set_mode(Addressing mode) noexcept;

        [[nodiscard]] ADDITIONAL_info get_additional_info() const noexcept;
        
        void set_additional_info(ADDITIONAL_info info) noexcept;
    };

}
#endif  // INTERPRETER_INSTRUCTION
