
# N memory cell
N:=1333

# Program Counter == 1597
MAIN:=1597

# F0 memory cell
F0:=377

# F1 memory cell
F1:=610

# i memory cell (iterator 1 => N)
I:=2584

# Jump to main
JMP MAIN

# Load 13 to accumulator F(13) == 233
LDA #13

# Store 13 to N
STA N

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

# Start for loop i == 1 ; i <= N ; i += 1
LOOP_BEGIN:

# Load F0 to Accumulator
LDA F0

# Add F1 to Accumulator
ADC F1

# Push Accumulator on stack
PHA

# Load F1 to Accumulator
LDA F1

# Copy Accumulator to F0
STA F0

# Pull Accumulator from stack
PLA

# Copy accumulator to F1
STA F1

# Increment I
INC I

# Load I to accumulator
LDA I

# Compare Accumulator with Memory(N)
CMP N

# Carry flag is set when Accumulator >= Memory
# If Carry Flag == 0 then jump to LOOP_BEGIN
BCC LOOP_BEGIN

# End loop