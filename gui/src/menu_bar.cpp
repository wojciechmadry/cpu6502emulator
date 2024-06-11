#include "gui_manager.hpp"
#include "gui_utils.hpp"
#include <functional>
#include <iostream>
#include <qaction.h>

void GuiManager::debugMode() {
  const auto debugModeStatus = this->actionDebug_mode->isChecked();
  this->DebugModeBox->setEnabled(debugModeStatus);
  if (debugModeStatus == false) {
    m_interpreter.get().set_states_to_remember(0);
    spinCommandToRemember->setValue(0);
  }
}

void GuiManager::changeBaseSystem() {
  if (this->actionHex_mode->isChecked()) {
    m_base = BaseSystem::Hex;
  } else {
    m_base = BaseSystem::Decimal;
  }
  this->refreshMenu();
}

int GuiManager::getBase() const noexcept {
  return m_base == BaseSystem::Decimal ? 10 : 16;
}

void GuiManager::resetProgram() {
  // Reset CPU & Memory
  m_cpu.get().reset();

  // Reset interpreter
  m_interpreter.get().clear_labels();

  // Refresh GUI
  this->refreshMenu();
}
