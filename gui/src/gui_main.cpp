#include "cpu.hpp"
#include "interpreter.hpp"
#include "gui_manager.hpp"

#include <fmt/core.h>

int main(int argc, char** argv)
{
  GuiManager ui;
  QApplication app(argc, argv);
  QMainWindow window;
  ui.setupUi(&window);
  window.show();
  return app.exec();
}
