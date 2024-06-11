#include "gui_manager.hpp"

#include <chrono>
#include <filesystem>
#include <list>
#include <string>
#include <vector>

void GuiManager::scanButton() {
  std::list<std::string> folder_path = {"."};
  std::vector<std::string> result;

  auto match = [](const std::string &str) -> bool {
    if (str.size() <= 4) {
      return false;
    }
    const auto m = str[str.size() - 1];
    const auto s = str[str.size() - 2];
    const auto a = str[str.size() - 3];
    const auto dot = str[str.size() - 4];
    return dot == '.' && a == 'a' && s == 's' && m == 'm';
  };

  while (!folder_path.empty()) {
    auto folder = std::move(*folder_path.begin());
    folder_path.pop_front();
    for (const auto &entry : std::filesystem::directory_iterator(folder)) {
      auto path = entry.path().string();
      if (entry.is_directory()) {
        folder_path.emplace_back(std::move(path));
      } else if (match(path)) {
        result.emplace_back(std::move(path));
      }
    }
  }

  this->listWidget->clear();
  for (const auto &asmFile : result) {
    this->listWidget->addItem(QString::fromStdString(asmFile));
  }
  this->refreshMenu();
}

void GuiManager::loadButton() {
  auto selected = this->listWidget->selectedItems();
  if (selected.size() != 1) {
    return;
  }
  auto asmFile = selected.first();
  auto asmFileStr = asmFile->text().toStdString();

  // Load .asm file
  this->m_interpreter.get().load_asm(asmFileStr);

  // Execute .asm file
  const auto start = std::chrono::high_resolution_clock::now();
  this->m_interpreter.get().execute_asm();
  const auto stop = std::chrono::high_resolution_clock::now();

  auto elapsed =
      std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start)
          .count();
  this->time_to_execute->setText(QString::number(elapsed) + " ns");

  this->refreshMenu();
}
