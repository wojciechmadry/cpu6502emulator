General info
---
Emulator processor 6502 in C++20

Tutorial (I am suggesting this tutorial)

https://www.youtube.com/watch?v=qJgsuQoy9bc&t=2764s

Additional guides:
1. http://www.obelisk.me.uk/6502/ [ now: https://web.archive.org/web/20210909190432/http://www.obelisk.me.uk/6502/ ]
2. https://sta.c64.org/cbm64mem.html
3. https://www.c64-wiki.com/wiki/Reset_(Process)

TODO
---

- [ ] Add all `instruction set`
- [ ] Implement `Arithmetic` set
    - [ ] Add test to `ADC`
    - [ ] Add test to `SBC`
    - [ ] Add test to `CMP`
    - [ ] Add test to `CPX`
    - [ ] Add test to `CPY`
- [ ] Implementing `RTS` - Working - But I think something is wrong
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