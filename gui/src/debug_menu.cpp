#include "gui_manager.hpp"

#include <fmt/core.h> // TODO: delete this

void GuiManager::debugModeSwitchRemembered(int newValue)
{
    this->m_interpreter.get().set_states_to_remember(static_cast<std::uint32_t>(newValue));
}
