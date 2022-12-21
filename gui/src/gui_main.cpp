#include "cpu.hpp"
#include "interpreter.hpp"
#include "gui_manager.hpp"
#include "memory.hpp"

#include <fmt/core.h>

int main(int argc, char** argv)
{
  // Initialise cpu6502 with memory and create interpreter
  static constexpr auto MEM_SIZE = static_cast<std::uint64_t>(1024u * 64u);
  cpu6502::Memory mem(MEM_SIZE);
  cpu6502::CPU cpu(mem);
  cpu6502::interpreter::Interpreter interpreter(cpu);

  QApplication app(argc, argv);
  // Create GUI and attach mem,cpu,interpreter to gui manager.
  GuiManager ui(cpu, interpreter, mem);
  QMainWindow window;
  ui.setupInterface(&window);
  window.show();
  return app.exec();
}
