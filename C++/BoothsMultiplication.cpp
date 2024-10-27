#include <iostream>
#include <bitset>
#include <cmath>
using namespace std;

void showStep(string step, int A, int Q, int Q_1, int bits) {
    cout << step << ": ";
    cout << "A = " << bitset<16>(A).to_string().substr(16-bits) << ", ";
    cout << "Q = " << bitset<16>(Q).to_string().substr(16-bits) << ", ";
    cout << "Q_1 = " << Q_1 << endl;
}

int boothMultiplication(int multiplicand, int multiplier, int bits) {

    int A = 0;          // Accumulator
    int M = multiplicand;  // Multiplicand
    int Q = multiplier;    // Multiplier
    int Q_1 = 0;          // Extra bit
    int count = bits;      // Counter for steps

    cout << "\nInitial values:" << endl;
    cout << "M = " << bitset<16>(M).to_string().substr(16-bits) << " (Multiplicand)" << endl;
    showStep("Start", A, Q, Q_1, bits);

    while (count > 0) {
        cout << "\nStep " << bits - count + 1 << ":" << endl;
        
        // Checking last two bits
        if ((Q & 1) == 1 && Q_1 == 0) {    
            A = A - M;
            cout << "10: A = A - M" << endl;
            showStep("After subtraction", A, Q, Q_1, bits);
        }
        else if ((Q & 1) == 0 && Q_1 == 1) {
            A = A + M;
            cout << "01: A = A + M" << endl;
            showStep("After addition", A, Q, Q_1, bits);
        }
        else {
            cout << ((Q & 1) == 0 && Q_1 == 0 ? "00" : "11") << ": No operation" << endl;
        }

        Q_1 = Q & 1;   
        Q = (Q >> 1) | ((A & 1) << (bits - 1));
        A = (A >> 1);
        if (A < 0) A |= (1 << (bits - 1));  

        showStep("After shift", A, Q, Q_1, bits);
        count--;
    }


    int result = (A << bits) | Q;
    return result;
}

int main() {
    int multiplicand, multiplier;
    
    cout << "Enter multiplicand: ";
    cin >> multiplicand;
    
    cout << "Enter multiplier: ";
    cin >> multiplier;
    

    int bits = max(
        (int)log2(abs(multiplicand)) + 2,
        (int)log2(abs(multiplier)) + 2
    );
    bits = min(bits, 16);  
    
    cout << "\nBooth's Multiplication Algorithm" << endl;
    cout << "--------------------------------" << endl;
    
    int result = boothMultiplication(multiplicand, multiplier, bits);
    
    cout << "\nFinal Result:" << endl;
    cout << multiplicand << " × " << multiplier << " = " << result << endl;
    
    return 0;
}
