#include "gui_manager.hpp"
#include "registers.hpp"
#include "utils.hpp"

#include <functional>
#include <qgroupbox.h>
#include <qlineedit.h>

void GuiManager::setupInterface(QMainWindow* main_window)
{
    // Create UI
    this->setupUi(main_window);

    // Connect and set debugMode
    QAction::connect(this->actionDebug_mode, &QAction::triggered, this, &GuiManager::debugMode);

    // Connect execute button
    QObject::connect(this->ExecuteButton, &QPushButton::clicked, this, &GuiManager::execute);

    // Hide error message
    this->label_error_message->setVisible(false);

    // Showing memory by defaul start from program counter value
    this->ShowMemoryStartAt->setText(QString::number(this->m_cpu.get().get_registers().PC.get()));

    // Editing value in Start From by default refresh value
    QObject::connect(this->ShowMemoryStartAt, &QLineEdit::textChanged, this, &GuiManager::refreshMenu);

    // Connect "Reset program" button to function
    QObject::connect(this->actionReset_program, &QAction::triggered, this, &GuiManager::resetProgram);
    
    // Connect Refresh action
    QObject::connect(this->actionRefresh_program, &QAction::triggered, this, &GuiManager::refreshMenu);

    // Connect change base action
    QObject::connect(this->actionHex_mode, &QAction::triggered, this, &GuiManager::changeBaseSystem);

    // Connect Memory/Register to edit action
    auto MemConnect = [&](QGroupBox* groupBox)
    {
        auto textBoxOpt = utils::searchGroupBox<QLineEdit>(groupBox);
        if (textBoxOpt.has_value())
        {
            QObject::connect(&(*textBoxOpt).get(), &QLineEdit::textChanged, std::bind(&GuiManager::changeMemory, this, groupBox));
        }
    };
    auto RegConnect = [&](QGroupBox* groupBox, cpu6502::RegistersName regName, bool isProcessorStatus)
    {
        auto textBoxOpt = utils::searchGroupBox<QLineEdit>(groupBox);
        if (textBoxOpt.has_value())
        {
            QObject::connect(&(*textBoxOpt).get(), &QLineEdit::textChanged, std::bind(&GuiManager::changeRegister, this, groupBox, regName, isProcessorStatus));
        }
    };
    // Program Counter memory
    MemConnect(MemorySP0);
    MemConnect(MemorySP1);
    MemConnect(MemorySP2);
    MemConnect(MemorySP3);
    MemConnect(MemorySP4);
    MemConnect(MemorySP5);
    // Start from memory
    MemConnect(MemoryStart0);
    MemConnect(MemoryStart1);
    MemConnect(MemoryStart2);
    MemConnect(MemoryStart3);
    MemConnect(MemoryStart4);
    MemConnect(MemoryStart5);

    // Connect register to edit action
    RegConnect(PC_group, cpu6502::RegistersName::ProgramCounter, false);
    RegConnect(IRY_group, cpu6502::RegistersName::IndexRegisterY, false);
    RegConnect(IRX_group, cpu6502::RegistersName::IndexRegisterX, false);
    RegConnect(SP_group, cpu6502::RegistersName::StackPointer, false);
    RegConnect(ACU_group, cpu6502::RegistersName::Accumulator, false);
    // Processor status
    RegConnect(CarryFlag_Group, cpu6502::RegistersName::ProcessorStatusCarryFlag, true);
    RegConnect(DecimalMode_group, cpu6502::RegistersName::ProcessorStatusDecimalMode, true);
    RegConnect(OverflowFlag_group, cpu6502::RegistersName::ProcessorStatusOverflowFlag, true);
    RegConnect(BreakCommand_group, cpu6502::RegistersName::ProcessorStatusBreakCommand, true);
    RegConnect(NegativeFlag_group, cpu6502::RegistersName::ProcessorStatusNegativeFlag, true);
    RegConnect(ZeroFlag_group, cpu6502::RegistersName::ProcessorStatusZeroFlag, true);
    RegConnect(InterruptDisable_group, cpu6502::RegistersName::ProcessorStatusInterruptDisable, true);

    // Connect Scan button
    QObject::connect(this->ScanASM, &QPushButton::clicked, this, &GuiManager::scanButton);

    // Connect Load button
    QObject::connect(this->LoadASM, &QPushButton::clicked, this, &GuiManager::loadButton);

    // Connect "CpuCommandLine" returnPressed to "ExecuteButton" press
    QAction::connect(this->CpuCommandLine, &QLineEdit::returnPressed, this, &GuiManager::executeAndClear);

    // Display all registers
    this->refreshMenu();
}

