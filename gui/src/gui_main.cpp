#include "cpu.hpp"
#include "interpreter.hpp"
#include "qt_gui.h"

#include <fmt/core.h>

int main(int argc, char** argv)
{
  Ui_cpu6502_mainwindow ui;
  QApplication app(argc, argv);
  QMainWindow window;
  ui.setupUi(&window);
  window.show();
  return app.exec();
}
