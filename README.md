General info
---
Emulator processor 6502 in c++20

Tutorial (I am suggesting this tutorial)

https://www.youtube.com/watch?v=qJgsuQoy9bc&t=2764s

Additional guides:
1. http://www.obelisk.me.uk/6502/
2. https://sta.c64.org/cbm64mem.html
3. https://www.c64-wiki.com/wiki/Reset_(Process)

Progress in tutorial
---
- [x] Episode 1 - https://www.youtube.com/watch?v=qJgsuQoy9bc&t=2764s
- [ ] Episode 2 - https://www.youtube.com/watch?v=L7J1pPokEyw `0m 0sec`

TODO
---
- [ ] Add all `instruction set`
- [ ] Implementing `RTS` - Working - But I think something is wrong
- [ ] I'm not sure about `page crossing` (need to check that)
- [ ] Add test to `Logical`
- [X] Implement `Logical` instruction set (`AND`, `EOR`, `ORA`, `BIT`)
- [X] Add test to `Stack Operations`
- [X] Implement `Stack Operations` instruction set (`TSX`, `TXS`, `PHA`, `PHP`, `PLA`, `PLP`)
- [X] Upgrade all tests (They don't look good)
- [x] Add test to `Register Transfers`
- [x] `Jump Calls` instruction set (`JMP`, `JSR`, `RTS`)
- [x] Add all `registers`
- [x] Memory
- [x] `Load & Store` instruction set (`LDA`, `LDX`, `LDY`, `STA`, `STX`, `STY`)
- [x] `Register Transfers` instruction set (`TAX`, `TAY`, `TXA`, `TYA`)
- [x] `Status Flag Changes` instruction set (`CLC`, `CLD`, `CLI`, `CLV`, `SEC`, `SED`, `SEI`)