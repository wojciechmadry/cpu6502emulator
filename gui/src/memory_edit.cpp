#include "gui_manager.hpp"
#include "utils.hpp"

void GuiManager::changeMemory(QGroupBox* groupbox)
{
    auto allChildrens = groupbox->children();
    for(auto child : allChildrens)
    {
        auto qLine = dynamic_cast<QLineEdit*>(child);
        if(qLine)
        {
            const auto newValue = utils::toUint32(qLine->text()); 
            const auto address = utils::toUint32(groupbox->title());
            if (newValue.has_value() && address.has_value())
            {
                m_memory.get()[*address] = static_cast<cpu6502::Byte>(*newValue);
                this->refreshMenu();
            }
            break;
        }
    }
}
