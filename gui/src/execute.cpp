#include "gui_manager.hpp"
#include <exception>

void GuiManager::execute()
{
    auto command = this->CpuCommandLine->toPlainText().toStdString();

    // Execute command
    try 
    {
        m_interpreter.get().interprete(command);
        if (this->label_error_message->isVisible())
        {
            this->label_error_message->setVisible(false);
        }
    }
    catch(const std::exception& err)
    {
        this->label_error_message->setText(QString{err.what()});
        if (!this->label_error_message->isVisible())
        {
            this->label_error_message->setVisible(true);
        }
    }
    
    // After execute refresh gui
    this->refreshMenu();
}