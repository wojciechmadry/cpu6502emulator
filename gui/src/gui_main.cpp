#include "cpu.hpp"
#include "interpreter.hpp"
#include "gui_manager.hpp"
#include "memory.hpp"

#include <fmt/core.h>

int main(int argc, char** argv)
{
  // Initialise cpu6502 with memory and create interpreter
  static constexpr std::uint64_t MEM_SIZE = 1024u * 64u;
  cpu6502::Memory mem(MEM_SIZE);
  cpu6502::CPU cpu(mem);
  cpu6502::interpreter::Interpreter interpreter(cpu);

  // Create GUI and attach mem,cpu,interpreter to gui manager.
  GuiManager ui(cpu, interpreter, mem);
  QApplication app(argc, argv);
  QMainWindow window;
  ui.setupUi(&window);
  window.show();
  return app.exec();
}
