#include "gui_manager.hpp"
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

    // Connect Memory to edit action
    auto memoryConnect = [&](QLineEdit* textBox, QGroupBox* groupBox)
    {
        QObject::connect(textBox, &QLineEdit::textChanged, std::bind(&GuiManager::changeMemory, this, groupBox));
    };
    // Program Counter memory
    memoryConnect(MemorySPEdit0, MemorySP0);
    memoryConnect(MemorySPEdit1, MemorySP1);
    memoryConnect(MemorySPEdit2, MemorySP2);
    memoryConnect(MemorySPEdit3, MemorySP3);
    memoryConnect(MemorySPEdit4, MemorySP4);
    memoryConnect(MemorySPEdit5, MemorySP5);
    // Start from memory
    memoryConnect(MemoryStartEdit0, MemoryStart0);
    memoryConnect(MemoryStartEdit1, MemoryStart1);
    memoryConnect(MemoryStartEdit2, MemoryStart2);
    memoryConnect(MemoryStartEdit3, MemoryStart3);
    memoryConnect(MemoryStartEdit4, MemoryStart4);
    memoryConnect(MemoryStartEdit5, MemoryStart5);


    // TODO: Connect all textbox, they should change register value in CPU
    // ...
    
    // Display all registers
    this->refreshMenu();
}

