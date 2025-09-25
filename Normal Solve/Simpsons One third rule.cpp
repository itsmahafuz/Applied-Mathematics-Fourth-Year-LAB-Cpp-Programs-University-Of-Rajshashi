/*
 Date: July 8th, 2025
 MD MAHAFUZUR RAHMAN
 Roll: 2110428176
 Department of Applied Mathematics
 University Of Rajshahi
 LinkedIn: https://www.linkedin.com/in/itsmahafuz/
 GitHub: https://github.com/itsmahafuz
*/

/* Numerical Integration using Simpson's 1/3 Rule */

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;

// Define the function f(x) to integrate
double f(double x)
{
    return (2x);  
}

int main()
{
    cout.precision(5);        // Set precision to 5 decimal places
    cout.setf(ios::fixed);    // Use fixed-point format for decimals

    char check;               // To control program repetition

    do
    {
        double a, b;          // Integration limits: lower (a), upper (b)
        int n;                // Number of subintervals

        // Prompt user for input limits
        cout << "\nEnter the lower and upper limits of the integral:\n";
        cin >> a >> b;

        // Input number of divisions (must be even for Simpson's 1/3 Rule)
    D:
        cout << "\nEnter the number of divisions: ";
        cin >> n;

        if (n % 2 != 0) {
            cout << "\nError: Number of divisions must be even for Simpson's 1/3 Rule.\n";
            goto D;  // Go back and ask again
        }

        double h = (b - a) / n;                // Step size
        vector<double> x(n + 1), y(n + 1);     // Arrays for x and f(x) values

        // Calculate x[i] and f(x[i])
        for (int i = 0; i <= n; i++) {
            x[i] = a + i * h;
            y[i] = f(x[i]);
        }

        // Display the table of x and f(x)
        cout << "\nThe values of f(x) at each subdivision are given below:\n";
        cout << setw(12) << "x" << setw(18) << "f(x)\n";
        cout << string(40, '-') << endl;

        for (int i = 0; i <= n; i++) {
            cout << setw(15) << x[i] << setw(15) << y[i] << "\n";
        }

        // Apply Simpson's 1/3 Rule:
        // result = h/3 * [y0 + yn + 4(y1 + y3 + ...) + 2(y2 + y4 + ...)]
        double sum = y[0] + y[n];

        for (int i = 1; i < n; i++) {
            if (i % 2 == 0)
                sum += 2 * y[i];  // Even-indexed terms
            else
                sum += 4 * y[i];  // Odd-indexed terms
        }

        double result = (h / 3.0) * sum;  // Final result

        // Output the result
        cout << "\nThe value of the integral is: " << result << "\n\n";

        // Ask user if they want to run the program again
        cout << "\nDo you want to run the program again? (Press 'Y' or 'y' to continue, or any other key to exit): ";
        cin >> check;

    } while (tolower(check) == 'y');  // Continue if user enters 'y' or 'Y'

    return 0;
}

