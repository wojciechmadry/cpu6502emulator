#include "gui_manager.hpp"
#include <functional>
#include <qaction.h>
#include <iostream>


void GuiManager::debugMode()
{
    const auto debugModeStatus = this->actionDebug_mode->isChecked();
    this->DebugModeBox->setEnabled(debugModeStatus);
}