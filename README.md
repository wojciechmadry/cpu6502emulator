General info
---
Emulator processor 6502 in C++20

Tutorial (I am suggesting this tutorial)

https://www.youtube.com/watch?v=qJgsuQoy9bc&t=2764s

Additional guides:
1. http://www.obelisk.me.uk/6502/ [ now: https://web.archive.org/web/20210909190432/http://www.obelisk.me.uk/6502/ ]
2. https://sta.c64.org/cbm64mem.html
3. https://www.c64-wiki.com/wiki/Reset_(Process)

SUBMODULES
---
- fmt [`https://github.com/fmtlib/fmt`]

TODO
---


- [ ] Add implementation of decimal flag
- [ ] Better organise code in `Shifts` and `Increments & Decrements`
- [ ] Read about non-maskable irq (0xFFFA/B) and reset location (0xFFFC/D)
- [X] Implement interpreter
    - [X] Add test to interpreter
- [X] Move functions in test to some utility file
- [X] Implementing `RTS` - Working - But I think something is wrong
- [X] Add all `instruction set`
- [X] Move stack memory to diffrent range -> 0x100 - 0x1FF (Now its 0 - 255 whereas it is zero page memory location)
- [X] Implement `Shifts` instructions (`ASL`, `LSR`, `ROL`, `ROR`)
- [X] Implement `Increments & Decrements` instructions (`INC`, `INX`, `INY`, `DEC`, `DEX`, `DEY`)
- [X] Implement `System Functions` instructions (`BRK`, `NOP`, `RTI`)
- [X] Implement `Arithmetic` instructions (`ADC`, `SBC`, `CMP`, `CPX`, `CPY`)
- [X] Implement better addressing mode
- [X] Remove `LUT`
- [X] Impement `Branches`
    - [X] Add test to `Branches`
- [X] Not sure about `IndirectX/Y`
- [X] I'm not sure about `page crossing` (need to check that)
- [X] Implement `Logical` instruction set (`AND`, `EOR`, `ORA`, `BIT`)
    - [X] Add test to `Logical`
- [X] Implement `Stack Operations` instruction set (`TSX`, `TXS`, `PHA`, `PHP`, `PLA`, `PLP`)
    - [X] Add test to `Stack Operations`
- [X] Upgrade all tests (They don't look good)
- [x] Add all `registers`
- [x] Memory
- [x] `Jump Calls` instruction set (`JMP`, `JSR`, `RTS`)
- [x] `Load & Store` instruction set (`LDA`, `LDX`, `LDY`, `STA`, `STX`, `STY`)
- [x] `Register Transfers` instruction set (`TAX`, `TAY`, `TXA`, `TYA`)
    - [x] Add test to `Register Transfers`
- [x] `Status Flag Changes` instruction set (`CLC`, `CLD`, `CLI`, `CLV`, `SEC`, `SED`, `SEI`)

Docker
---
- Docker contain minimal setup to compile cpu 6502 emulator.
- You can run test on it (You can't run cpu emulator with gui)
 - How to run docker:
    1. `sudo docker build -t cpu_docker .`
    2. `sudo docker run -it cpu_docker`

