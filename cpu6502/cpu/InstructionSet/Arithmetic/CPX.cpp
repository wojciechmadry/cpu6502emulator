#include "cpu.hpp"

namespace cpu6502{

    void cpx_operation(CPU& cpu, const Byte fetched) noexcept
    {
        auto& reg = cpu.get_registers();
        const auto x_reg = reg.IRX.get();
        const auto result = static_cast<Byte>(x_reg - fetched);

        reg.PS.set(CPU::PSFlags::CarryFlag, x_reg >= fetched);
        reg.PS.set(CPU::PSFlags::ZeroFlag, x_reg == fetched);
        reg.PS.set(CPU::PSFlags::NegativeFlag, static_cast<bool>(result & 0x80));
    }

    void CPU::CPXimmediate(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::Immediate>(Cycles);
        cpx_operation(*this, fetched);
    }

    void CPU::CPXzeropage(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::ZeroPage>(Cycles);
        cpx_operation(*this, fetched);
    }

    void CPU::CPXabsolute(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::Absolute>(Cycles);
        cpx_operation(*this, fetched);
    }

}
