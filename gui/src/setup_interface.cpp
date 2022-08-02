#include "gui_manager.hpp"


void GuiManager::setupInterface(QMainWindow* main_window)
{
    // Create UI
    this->setupUi(main_window);

    // Connect and set debugMode
    QAction::connect(this->actionDebug_mode, &QAction::triggered, this, &GuiManager::debugMode);

    // Connect execute button
    QObject::connect(this->ExecuteButton, &QPushButton::clicked, this, &GuiManager::execute);

    // Showing memory by defaul start from program counter value
    this->ShowMemoryStartAt->setText(QString::number(this->m_cpu.get().get_registers().PC.get()));

    // TODO: Connect all textbox, they should change register value in CPU
    // ...
    
    // Display all registers
    this->refreshMenu();
}

