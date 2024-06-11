#include "gui_manager.hpp"

void GuiManager::debugModeSwitchRemembered(int newValue) {
  this->m_interpreter.get().set_states_to_remember(
      static_cast<std::uint32_t>(newValue));
  this->refreshMenu();
}

void GuiManager::debugChangeCommand(
    cpu6502::interpreter::utils::DebugModeNextCommand nextCommand) {
  auto &interpreter = this->m_interpreter.get();
  interpreter.debug_mode_change_command(nextCommand);
  this->refreshMenu();
}
