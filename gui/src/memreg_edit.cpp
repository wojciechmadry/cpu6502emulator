#include "gui_manager.hpp"
#include "registers.hpp"
#include "stackpointer.hpp"
#include "gui_utils.hpp"

void GuiManager::changeMemory(QGroupBox* groupbox)
{
    auto qLineOpt = utils::searchGroupBox<QLineEdit>(groupbox);
    if(qLineOpt.has_value())
    {
        const auto& qLine = (*qLineOpt).get();
        const auto newValue = utils::toUint32BaseX(qLine.text(), getBase()); 
        const auto address = utils::toUint32(groupbox->title());
        if (newValue.has_value() && address.has_value())
        {
            m_memory.get()[*address] = static_cast<cpu6502::Byte>(*newValue);
            this->refreshMenu();
        }
    }
}

void GuiManager::changeRegister(QGroupBox* groupbox, cpu6502::RegistersName regName, bool isProcessorStatus)
{
    auto qLineOpt = utils::searchGroupBox<QLineEdit>(groupbox);
    if(qLineOpt.has_value())
    {
        const auto& qLine = (*qLineOpt).get();
        const auto lowerStr = qLine.text().toLower();
        std::optional<std::uint32_t> newValueOpt;

        if (lowerStr == "false")
        {
            newValueOpt = 0;
        }
        else if (lowerStr == "true")
        {
            newValueOpt = 1;
        }
        else if (!isProcessorStatus)
        {
            newValueOpt = utils::toUint32BaseX(qLine.text(), getBase());
        }
        else
        {
            auto isZeroOrOne = utils::toUint32(qLine.text());
            if (isZeroOrOne.has_value() && (*isZeroOrOne == 0 || *isZeroOrOne == 1))
            {
                newValueOpt = isZeroOrOne;
            }
        }
        
        if(!newValueOpt.has_value())
        {
            return;
        }
        
        m_cpu.get().get_registers().setRegister(regName, *newValueOpt);
        this->refreshMenu();
    }
}
