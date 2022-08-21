# N memory cell
N:=1333

# Program Counter == 720
MAIN:=720

# i memory cell (iterator 0 => N)
I:=5040

# Jump to main
JMP MAIN

# Load 5 to accumulator Factorial(5) == 120
LDA #5

# Store 5 to N
STA N

# Add 1 to N (Because our loop should interate until i <= N, without that it will be i < N)
INC N

# Load 0 to Accumulator
LDA #0

# Load 1 to Accumulator
LDA #1

# Load 1 to I
STA I

# Start do while loop i == 1 ; i <= N ; i += 1
LOOP_BEGIN:

# Multiply Accumulator * I
MUL I

# Increment I
INC I

# Push Accumulator to stack
PHA

# Load I to accumulator
LDA I

# Compare Accumulator with Memory(N)
CMP N

# Pull Accumulator from stack
PLA

# Carry flag is set when Accumulator >= Memory
# If Carry Flag == 0 then jump to LOOP_BEGIN
BCC LOOP_BEGIN

# End loop


