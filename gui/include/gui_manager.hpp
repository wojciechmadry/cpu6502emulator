#ifndef GUI_MANAGER_HPP
#define GUI_MANAGER_HPP

#include <functional>
#include <qgroupbox.h>

#include "memory.hpp"
#include "qt_gui.h"
#include "cpu.hpp"
#include "interpreter.hpp"

class GuiManager : public QWidget, public Ui::cpu6502_mainwindow
{
    public:
    GuiManager(cpu6502::CPU& cpu, cpu6502::interpreter::Interpreter& interpreter, cpu6502::Memory& memory) noexcept;
    void setupInterface(QMainWindow *cpu6502_mainwindow);

    private slots:
    void debugMode();
    void execute();
    void resetProgram();
    void changeMemory(QGroupBox* groupbox);

    private:
    void refreshMenu();
    void showMemory();
    
    std::reference_wrapper<cpu6502::CPU> m_cpu;
    std::reference_wrapper<cpu6502::interpreter::Interpreter> m_interpreter;
    std::reference_wrapper<cpu6502::Memory> m_memory;
};

#endif  // GUI_MANAGER_HPP
