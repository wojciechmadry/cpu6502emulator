#include "cpu.hpp"
#include "gui_manager.hpp"
#include "memory.hpp"
#include "utils.hpp"
#include <cstdint>
#include <limits>
#include <qgroupbox.h>

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

    // Show Memory started from Program Counter
    showProgramCounterMemory();

    // Show memory started from 'ShowMemoryStartAt' QLineEdit
    showStartFromMemory();
}


void setMemoryBox(QGroupBox* group_box, QLineEdit* qline_edit, std::uint32_t idx, const cpu6502::Memory& mem)
{
    if (group_box == nullptr || qline_edit == nullptr)
    {
        return;
    }

    if (idx > std::numeric_limits<std::uint16_t>::max())
    {
        idx = std::numeric_limits<std::uint16_t>::max();
    }

    group_box->setTitle(utils::toHex(idx));
    qline_edit->setText(QString::number(mem[idx]));
}

void GuiManager::showProgramCounterMemory()
{
    const auto& mem = m_memory.get();
    auto PC = static_cast<std::uint32_t>(m_cpu.get().get_registers().PC.get());
    setMemoryBox(MemorySP0, MemorySPEdit0, PC, mem);
    ++PC;
    setMemoryBox(MemorySP1, MemorySPEdit1, PC, mem);
    ++PC;
    setMemoryBox(MemorySP2, MemorySPEdit2, PC, mem);
    ++PC;
    setMemoryBox(MemorySP3, MemorySPEdit3, PC, mem);
    ++PC;
    setMemoryBox(MemorySP4, MemorySPEdit4, PC, mem);
    ++PC;
    setMemoryBox(MemorySP5, MemorySPEdit5, PC, mem);
}

void GuiManager::showStartFromMemory()
{
    const auto& mem = m_memory.get();
    bool numIsOk;
    auto At = static_cast<std::uint32_t>(ShowMemoryStartAt->text().toInt(&numIsOk));
    if ( !numIsOk ) 
    {
        return;
    }
    
    setMemoryBox(MemoryStart0, MemoryStartEdit0, At, mem);
    ++At;
    setMemoryBox(MemoryStart1, MemoryStartEdit1, At, mem);
    ++At;
    setMemoryBox(MemoryStart2, MemoryStartEdit2, At, mem);
    ++At;
    setMemoryBox(MemoryStart3, MemoryStartEdit3, At, mem);
    ++At;
    setMemoryBox(MemoryStart4, MemoryStartEdit4, At, mem);
    ++At;
    setMemoryBox(MemoryStart5, MemoryStartEdit5, At, mem);
}