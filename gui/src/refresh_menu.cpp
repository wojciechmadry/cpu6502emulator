#include "cpu.hpp"
#include "gui_manager.hpp"
#include "constant.hpp"

void GuiManager::refreshMenu()
{
    this->debugMode();
    const auto& cpu = this->m_cpu.get();
    const auto& reg = cpu.get_registers();
    const auto& mem = cpu.get_memory();

    auto boolToString = [](bool b)
    {
        return b ? constant::true_str : constant::false_str;
    };

    // Load Program Counter
    this->PC_value->setText(QString::number(reg.PC.get()));

    // Load Index Register Y
    this->IRY_value->setText(QString::number(reg.IRY.get()));

    // Load Index Register X
    this->IRX_value->setText(QString::number(reg.IRX.get()));

    // Load Stack Pointer
    this->SP_value->setText(QString::number(reg.SP.get()));

    // Load Accumulator
    this->ACU_value->setText(QString::number(reg.ACU.get()));

    // Load Carry Flag
    this->CF_value->setText(QString{boolToString(reg.PS.get(cpu6502::CPU::PSFlags::CarryFlag))});

    // Load Overflow Flag
    this->OF_value->setText(QString{boolToString(reg.PS.get(cpu6502::CPU::PSFlags::OverflowFlag))});

    // Load Negative Flag
    this->NF_value->setText(QString{boolToString(reg.PS.get(cpu6502::CPU::PSFlags::NegativeFlag))});

    // Load Interrupt Disable
    this->ID_value->setText(QString{boolToString(reg.PS.get(cpu6502::CPU::PSFlags::InterruptDisable))});

    // Load Decimal Mode
    this->DM_value->setText(QString{boolToString(reg.PS.get(cpu6502::CPU::PSFlags::DecimalMode))});

    // Load Break Command
    this->BC_value->setText(QString{boolToString(reg.PS.get(cpu6502::CPU::PSFlags::BreakCommand))});

    // Load Zero Flag
    this->ZF_value->setText(QString{boolToString(reg.PS.get(cpu6502::CPU::PSFlags::ZeroFlag))});

}