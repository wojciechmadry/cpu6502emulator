#include "cpu.hpp"

namespace cpu6502{

    void cpy_operation(CPU& cpu, const Byte fetched) noexcept
    {
        auto& reg = cpu.get_registers();
        const auto y_reg = reg.IRY.get();
        const auto result = static_cast<Byte>(y_reg - fetched);

        reg.PS.set(CPU::PSFlags::CarryFlag, y_reg >= fetched);
        reg.PS.set(CPU::PSFlags::ZeroFlag, y_reg == fetched);
        reg.PS.set(CPU::PSFlags::NegativeFlag, static_cast<bool>(result & 0x80));
    }

    void CPU::CPYimmediate(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::Immediate>(Cycles);
        cpy_operation(*this, fetched);
    }

    void CPU::CPYzeropage(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::ZeroPage>(Cycles);
        cpy_operation(*this, fetched);
    }

    void CPU::CPYabsolute(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::Absolute>(Cycles);
        cpy_operation(*this, fetched);
    }
    
}
