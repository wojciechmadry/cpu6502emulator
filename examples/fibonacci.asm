
# F(13) == 233
N:=13

# Program Counter == 1597
MAIN:=1597

# F0 memory cell
F0:=377

# F1 memory cell
F1:=610

# F2 memory cell (F2 = F0 + F1)
F2:=987

# i memory cell (iterator 1 => N)
I:=2584

# Jump to main
JMP MAIN

# Load 0 to accumulator
LDA #0

# Load 0 to F0
STA F0

# Load 0 to F1
STA F1

# Add 1 to F1
INC F1

# Load 0 to I
STA I

# Add 1 to I
INC I

# Start for loop i == 1 ; i != N ; i += 1
LOOP_BEGIN:

# Increment I
INC I

# Load I to accumulator
LDA I

# Compare Accumulator with Memory(N)
CMP N

# Zero Flag is set when Accumulator = N
# If Zero Flag == 0 then jump to LOOP_BEGIN
BNE LOOP_BEGIN

# End loop

