/**
 * EasyCPU Assembly Language - C++ Conversion
 * Author: Yara Vasquez
 *
 * Original EasyCPU Assembly Program:
 * -----------------------------------------------------------
 * Address | Instruction | Description
 * --------|-------------|-------------------------------------
 *   0     | JUMP 3      | Skip data; jump to first instruction
 *   1     | 6           | Data: input value (n = 6)
 *   2     | 1           | Data: constant 1 (decrement step)
 *   3     | LOAD @1     | AX = mem[1] = 6
 *   4     | STORE BX    | BX = AX = 6
 *   5     | SUB @2      | AX = AX - 1
 *   6     | JZ 12       | if AX == 0: jump to HALT
 *   7     | STORE CX    | CX = AX  (save current counter)
 *   8     | MUL BX      | AX = AX * BX (multiply into accumulator)
 *   9     | STORE BX    | BX = AX  (update running product)
 *  10     | LOAD CX     | AX = CX  (restore counter)
 *  11     | JMP 5       | Jump back to subtract step
 *  12     | HLT         | Halt — result is in BX
 *
 * Algorithm: Computes n! (factorial) where n = 6
 * Result:    BX = 720  (6! = 6 × 5 × 4 × 3 × 2 × 1 = 720)
 */

#include <iostream>
#include <iomanip>
using namespace std;

/**
 * Simulates the EasyCPU assembly program using named register variables.
 *
 * Mirrors the original assembly 1-to-1:
 *   AX - Accumulator: holds the countdown counter and temporary products
 *   BX - Running product register: holds the result at HALT
 *   CX - Temporary register: saves the counter across multiply steps
 *   PC - Program Counter: controls which instruction executes next
 *
 * @param n  The input value loaded from memory address 1 (n=6 in original)
 * @return   The value of BX at HALT, which equals n!
 */
int easyCPUSimulate(int n) {
    // Memory: mirrors assembly addresses 1 (input) and 2 (constant decrement)
    int mem[3] = {0, n, 1};

    // Registers — named to match assembly directly
    int AX = 0;
    int BX = 0;
    int CX = 0;
    int PC = 3; // JUMP 3: execution begins at address 3

    cout << "EasyCPU Simulation (n = " << n << ")" << endl;
    cout << left << setw(5)  << "PC"
                 << setw(12) << "Instruction"
                 << setw(6)  << "AX"
                 << setw(8)  << "BX"
                 << setw(6)  << "CX" << endl;
    cout << string(42, '-') << endl;

    while (true) {
        switch (PC) {
            case 3: // LOAD @1 → AX = mem[1]
                AX = mem[1];
                cout << left << setw(5) << PC << setw(12) << "LOAD @1"
                     << setw(6) << AX << setw(8) << BX << setw(6) << CX << endl;
                PC = 4;
                break;

            case 4: // STORE BX → BX = AX
                BX = AX;
                cout << left << setw(5) << PC << setw(12) << "STORE BX"
                     << setw(6) << AX << setw(8) << BX << setw(6) << CX << endl;
                PC = 5;
                break;

            case 5: // SUB @2 → AX = AX - 1
                AX = AX - mem[2];
                cout << left << setw(5) << PC << setw(12) << "SUB @2"
                     << setw(6) << AX << setw(8) << BX << setw(6) << CX << endl;
                PC = 6;
                break;

            case 6: // JZ 12 → if AX == 0: jump to HALT
                PC = (AX == 0) ? 12 : 7;
                cout << left << setw(5) << PC << setw(12) << "JZ 12"
                     << setw(6) << AX << setw(8) << BX << setw(6) << CX << endl;
                break;

            case 7: // STORE CX → CX = AX
                CX = AX;
                cout << left << setw(5) << PC << setw(12) << "STORE CX"
                     << setw(6) << AX << setw(8) << BX << setw(6) << CX << endl;
                PC = 8;
                break;

            case 8: // MUL BX → AX = AX * BX
                AX = AX * BX;
                cout << left << setw(5) << PC << setw(12) << "MUL BX"
                     << setw(6) << AX << setw(8) << BX << setw(6) << CX << endl;
                PC = 9;
                break;

            case 9: // STORE BX → BX = AX
                BX = AX;
                cout << left << setw(5) << PC << setw(12) << "STORE BX"
                     << setw(6) << AX << setw(8) << BX << setw(6) << CX << endl;
                PC = 10;
                break;

            case 10: // LOAD CX → AX = CX
                AX = CX;
                cout << left << setw(5) << PC << setw(12) << "LOAD CX"
                     << setw(6) << AX << setw(8) << BX << setw(6) << CX << endl;
                PC = 11;
                break;

            case 11: // JMP 5 → unconditional jump back to loop start
                cout << left << setw(5) << PC << setw(12) << "JMP 5"
                     << setw(6) << AX << setw(8) << BX << setw(6) << CX << endl;
                PC = 5;
                break;

            case 12: // HLT → program ends, result is in BX
                cout << left << setw(5) << PC << setw(12) << "HLT"
                     << setw(6) << AX << setw(8) << BX << setw(6) << CX << endl;
                cout << string(42, '-') << endl;
                cout << "[HALT] AX=" << AX << ", BX=" << BX
                     << ", CX=" << CX << ", PC=" << PC << endl;
                return BX;

            default:
                cerr << "Unexpected PC value: " << PC << endl;
                return -1;
        }
    }
}

/**
 * Clean high-level equivalent of the assembly logic.
 *
 * The assembly implements iterative factorial using a countdown loop:
 *   - AX counts DOWN from n toward 0
 *   - BX accumulates the running product
 *   - CX saves AX between the multiply step and the next subtract
 *
 * @param n  Input integer
 * @return   n! (factorial of n)
 */
int factorial(int n) {
    if (n == 0) return 1;
    int result  = n;      // BX = n  (STORE BX)
    int counter = n - 1;  // AX after first SUB @2
    while (counter > 0) {
        result  = result * counter; // MUL BX → STORE BX
        counter--;                  // SUB @2 (next iteration)
    }
    return result;
}

int main() {
    int n = 6; // Value stored at memory address 1 in the assembly

    cout << string(42, '=') << endl;
    easyCPUSimulate(n);

    cout << "\n" << string(42, '=') << endl;
    cout << " Clean High-Level Factorial (1 through 7)" << endl;
    cout << string(42, '=') << endl;
    for (int i = 1; i <= 7; i++) {
        cout << "  factorial(" << i << ") = " << factorial(i) << endl;
    }
    cout << "\nVerification: 6! = " << factorial(6) << " checkmark" << endl;

    return 0;
}