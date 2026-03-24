# EasyCPU Assembly → C++ Conversion

A C++ program that simulates a low-level EasyCPU assembly factorial algorithm,
modeling CPU registers (AX, BX, CX) and a Program Counter (PC) instruction cycle.

## What it does
- Simulates each assembly instruction step-by-step with a register trace
- Computes 6! = 720, matching the original assembly output at HALT
- Includes a clean high-level factorial equivalent for comparison

## How to run
```bash
g++ EasyCPUFactorial.cpp -o EasyCPUFactorial
./EasyCPUFactorial
```

## Concepts demonstrated
- CPU register simulation (AX, BX, CX, PC)
- Assembly-to-high-level language translation
- Iterative factorial algorithm
- Computer architecture fundamentals
EOF