/*
 Date: July 8th, 2025
 MD MAHAFUZUR RAHMAN
 Roll: 2110428176
 Department of Applied Mathematics
 University Of Rajshahi
 LinkedIn: https://www.linkedin.com/in/itsmahafuz/
 GitHub: https://github.com/itsmahafuz
*/

/* Numerical Integration using Simpson's 3/8 Rule */

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;

// Function to integrate
double f(double x) {
    // Example function: sin(x) - ln(x) + e^x
    return sin(x) +x*x+ exp(-x);
}

int main() {
    cout.precision(5);
    cout.setf(ios::fixed);

    char check;

    do {
        double a, b;   // integration limits
        int n;         // number of subintervals

        cout << "\nEnter the lower and upper limits of the integral:\n";
        cin >> a >> b;

    InputN:
        cout << "\nEnter the number of divisions (must be multiple of 3): ";
        cin >> n;

        // Validate n is multiple of 3
        if (n % 3 != 0) {
            cout << "Error: Number of divisions must be a multiple of 3 for Simpson's 3/8 Rule.\n";
            goto InputN;
        }

        double h = (b - a) / n;
        vector<double> x(n + 1), y(n + 1);

        // Compute x and f(x) values
        for (int i = 0; i <= n; ++i) {
            x[i] = a + i * h;
            y[i] = f(x[i]);
        }

        // Display the computed values
        cout << "\nValues of f(x) at subdivisions:\n";
        cout << setw(12) << "x" << setw(18) << "f(x)\n";
        cout << string(30, '-') << "\n";

        for (int i = 0; i <= n; ++i) {
            cout << setw(15) << x[i] << setw(15) << y[i] << "\n";
        }

        // Apply Simpson's 3/8 Rule formula
        double sum = y[0] + y[n]; // first and last terms

        for (int i = 1; i < n; ++i) {
            if (i % 3 == 0) {
                sum += 2 * y[i];
            } else {
                sum += 3 * y[i];
            }
        }

        double result = (3.0 * h / 8.0) * sum;

        cout << "\nThe value of the integral is: " << result << "\n\n";

        // Ask user if they want to run again
        cout << "Do you want to run the program again? (Y/y to continue): ";
        cin >> check;

    } while (tolower(check) == 'y');

    return 0;
}
