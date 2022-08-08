#include "gui_manager.hpp"
#include "utils.hpp"
#include <functional>
#include <qaction.h>
#include <iostream>


void GuiManager::debugMode()
{
    const auto debugModeStatus = this->actionDebug_mode->isChecked();
    this->DebugModeBox->setEnabled(debugModeStatus);
}

void GuiManager::changeBaseSystem()
{
    if (this->actionHex_mode->isChecked())
    {
        m_base = BaseSystem::Hex;
    }
    else
    {
        m_base = BaseSystem::Decimal;
    }
    this->refreshMenu();
}

int GuiManager::getBase() const noexcept
{
    return m_base == BaseSystem::Decimal ? 10 : 16;
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
