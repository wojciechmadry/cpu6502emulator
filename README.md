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
- [ ] Add implementation of decimal flag
- [ ] Implementing `RTS` - Working - But I think something is wrong
- [ ] Implement `Shifts` instructions
    - [ ] Add test to `ASL` 
    - [ ] Add test to `LSR` 
    - [ ] Add test to `ROL` 
    - [ ] Add test to `ROR` 
- [ ] Implement `Increments & Decrements` instructions
    - [ ] Add test to `INC` 
    - [ ] Add test to `INX` 
    - [ ] Add test to `INY` 
    - [ ] Add test to `DEC` 
    - [ ] Add test to `DEX` 
    - [ ] Add test to `DEY` 
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