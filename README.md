General info
---

Emulator processor 6502 with dummy interpreter and simple gui.

All instructions with description: https://www.masswerk.at/6502/6502_instruction_set.html

WORKFLOWS
---

| GCC - Build and test | Clang - Build and test | Docker build | Clang-Tidy |
| --------------- | -------------- | -------------- | -------------- |
| ![GCC - Build and test](https://github.com/wojciechmadry/cpu6502emulator/actions/workflows/gcc.yml/badge.svg)|![Clang - Build and test](https://github.com/wojciechmadry/cpu6502emulator/actions/workflows/clang.yml/badge.svg)|![Dockerfile build](https://github.com/wojciechmadry/cpu6502emulator/actions/workflows/docker_build.yml/badge.svg)|![Clang-tidy check](https://github.com/wojciechmadry/cpu6502emulator/actions/workflows/clang-tidy.yml/badge.svg)

SUBMODULES
---

- fmt [`https://github.com/fmtlib/fmt`]

BUILD
---

**Requirements:**

- `C++20  support`
-  `Qt6`

**Build steps:**

- `git submodule init && git submodule update`
- `mkdir build && cd build`
- `cmake ../`
- `cmake --build . -j`

**Output files:**

- `cpu_6502_gui` - Qt6 GUI with interpreter
- `cpu_6502_tests` - Run interpreter and simulator tests.

GUI
---

![GUI look](https://github.com/wojciechmadry/cpu6502emulator/blob/master/gui/gui_appearance.png)

EXAMPLES
---

- `examples/fibonacci.asm` - Calculate Fibonacci
- `examples/factorial.asm` - Calculate factorial

Docker
---

- Docker contain minimal setup to compile cpu 6502 emulator.
- You can run test on it (You can't run cpu emulator with gui)
 - How to run docker:
    1. `sudo docker build -t cpu_docker .`
    2. `sudo docker run -it cpu_docker`

