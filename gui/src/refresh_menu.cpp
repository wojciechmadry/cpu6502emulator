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

    // Show Memory value in GUI
    showMemory();
}

void GuiManager::showMemory()
{
    const auto& mem = m_memory.get();

    auto setMemoryBox = [&](QGroupBox* group_box, QLineEdit* qline_edit, std::uint32_t idx)
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
    };

    auto PC = static_cast<std::uint32_t>(m_cpu.get().get_registers().PC.get());
    setMemoryBox(MemorySP0, MemorySPEdit0, PC);
    setMemoryBox(MemorySP1, MemorySPEdit1, PC + 1);
    setMemoryBox(MemorySP2, MemorySPEdit2, PC + 2);
    setMemoryBox(MemorySP3, MemorySPEdit3, PC + 3);
    setMemoryBox(MemorySP4, MemorySPEdit4, PC + 4);
    setMemoryBox(MemorySP5, MemorySPEdit5, PC + 5);


    bool numIsOk;
    auto At = static_cast<std::uint32_t>(ShowMemoryStartAt->text().toInt(&numIsOk));
    if ( !numIsOk ) 
    {
        return;
    }
    setMemoryBox(MemoryStart0, MemoryStartEdit0, At);
    setMemoryBox(MemoryStart1, MemoryStartEdit1, At + 1);
    setMemoryBox(MemoryStart2, MemoryStartEdit2, At + 2);
    setMemoryBox(MemoryStart3, MemoryStartEdit3, At + 3);
    setMemoryBox(MemoryStart4, MemoryStartEdit4, At + 4);
    setMemoryBox(MemoryStart5, MemoryStartEdit5, At + 5);
}

void GuiManager::resetProgram()
{
    // Reset CPU & Memory
    m_cpu.get().reset();

    // Reset interpreter
    m_interpreter.get().clear_labels();

    // Refresh GUI
    this->refreshMenu();
}