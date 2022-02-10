#include "cpu.hpp"

namespace cpu6502{

    void CPU::ORAimmediate(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::Immediate>(Cycles);
        cpu_reg.ACU.set(fetched | cpu_reg.ACU.get());
        //0 Cycles

        //Flag set
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
    }

    void CPU::ORAzeropage(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::ZeroPage>(Cycles);
        // 1 cycles
        cpu_reg.ACU.set(cpu_reg.ACU.get() | fetched);
        // 0 cycles
        //Flag set
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
    }  

    
    void CPU::ORAzeropagex(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::ZeroPageX>(Cycles);
        cpu_reg.ACU.set(cpu_reg.ACU.get() | fetched);
        // 0 cycles

        //Flag set
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
    }    


    void CPU::ORAabsolute(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::Absolute>(Cycles);
        cpu_reg.ACU.set(cpu_reg.ACU.get() | fetched);
        // 0 Cycles

        //Flag set
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
    }  

    void CPU::ORAabsolutex(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::AbsoluteX>(Cycles);
        cpu_reg.ACU.set(cpu_reg.ACU.get() | fetched);
        // 0 cycles

        //Flag set
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
    }      

    void CPU::ORAabsolutey(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::AbsoluteY>(Cycles);
        cpu_reg.ACU.set(cpu_reg.ACU.get() | fetched);
        // 0 cycles

        //Flag set
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
    }      

    void CPU::ORAindirectx(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::IndirectX>(Cycles);
        cpu_reg.ACU.set(cpu_reg.ACU.get() | fetched);
        // 0 cycles

        //Flag set
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
    }  

    void CPU::ORAindirecty(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::IndirectY>(Cycles);
        cpu_reg.ACU.set(cpu_reg.ACU.get() | fetched);
        // 0 cycles

        //Flag set
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
    }  

}