#ifndef GUI_MANAGER_HPP
#define GUI_MANAGER_HPP

#include <functional>

#include <qgroupbox.h>

#include "memory.hpp"
#include "qt_gui.h"
#include "cpu.hpp"
#include "interpreter.hpp"
#include "utils.hpp"

class GuiManager : public QWidget, public Ui::cpu6502_mainwindow
{
    public:
    GuiManager(cpu6502::CPU& cpu, cpu6502::interpreter::Interpreter& interpreter, cpu6502::Memory& memory) noexcept;
    void setupInterface(QMainWindow *cpu6502_mainwindow);

    private slots:
    void debugMode();
    void execute();
    void resetProgram();
    void changeBaseSystem();
    void changeMemory(QGroupBox* groupbox);
    void changeRegister(QGroupBox* groupbox, cpu6502::RegistersName regName, bool isProcessorStatus);

    private:
    void refreshMenu();
    void showMemory();
    int getBase() const noexcept;
    
    BaseSystem m_base = BaseSystem::Decimal;
    std::reference_wrapper<cpu6502::CPU> m_cpu;
    std::reference_wrapper<cpu6502::interpreter::Interpreter> m_interpreter;
    std::reference_wrapper<cpu6502::Memory> m_memory;
};

#endif  // GUI_MANAGER_HPP