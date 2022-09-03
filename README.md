General info
---

Emulator processor 6502 with dummy interpreter and simple gui.

All instructions with description: https://www.masswerk.at/6502/6502_instruction_set.html

WORKFLOWS
---

| Build and test | Docker build |
| --------------- | --------------|
| ![Ubuntu 22.04 - Build and test](https://github.com/wojciechmadry/cpu6502emulator/actions/workflows/ubuntu22.yml/badge.svg)|![Ubuntu 22.04 - Docker file](https://github.com/wojciechmadry/cpu6502emulator/actions/workflows/ubuntu22_docker.yml/badge.svg)

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

![alt text](https://github.com/wojciechmadry/cpu6502emulator/tree/master/gui/gui_appearance.png)

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

