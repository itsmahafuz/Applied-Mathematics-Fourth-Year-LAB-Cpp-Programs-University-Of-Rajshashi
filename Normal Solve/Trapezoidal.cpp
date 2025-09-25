/*
 Date: July 8th, 2025
 MD MAHAFUZUR RAHMAN
 Roll: 2110428176
 Department of Applied Mathematics
 University Of Rajshahi
 LinkedIn: https://www.linkedin.com/in/itsmahafuz/
 GitHub: https://github.com/itsmahafuz
*/
/*Numerical Integration by Trapezoidal Rule*/

#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
using namespace std;

// Define the function f(x) to be integrated
double f(double x)
{
    return (4*x); // Example: f(x) = 1 / (1 + x^2)
}

int main()
{
    cout.precision(5);     // Set output precision to 5 digits
    cout.setf(ios::fixed); // Use fixed-point notation
    cout << "\nNumerical Integration by Trapezoidal Rule\n\n";
    char check;
    do
    {
        int n;       // Number of sub-intervals
        double a, b; // Lower and upper limits

        

        // Input limits
        cout << "Enter the lower and upper limits of the integral:\n";
        cin >> a >> b;

        // Input number of divisions
        cout << "Enter the number of divisions:\n";
        cin >> n;

        double h = (b - a) / n;            // Step size
        vector<double> x(n + 1), y(n + 1); // Vectors to store x and f(x) values

        // Calculate x[i] and corresponding y[i] = f(x[i])
        for (int i = 0; i <= n; i++)
        {
            x[i] = a + i * h;
            y[i] = f(x[i]);
        }

        // Display the values of x and f(x) in table format
        cout << "\nThe values of f(x) at each subdivision are:\n";
        cout << setw(12) << "x" << setw(18) << "f(x)\n";
        cout << string(40, '-') << endl;
        for (int i = 0; i <= n; ++i)
        {
            cout << setw(15) << x[i] << setw(15) << y[i] << "\n";
        }

        // Apply Trapezoidal Rule:
        // Integral ≈ h/2 * [f(x0) + 2*f(x1) + 2*f(x2) + ... + 2*f(xn-1) + f(xn)]
        double sum = y[0] + y[n];
        for (int i = 1; i < n; ++i)
            sum += 2 * y[i];

        double result = (h / 2.0) * sum;

        // Output the result
        cout << "\nThe value of the integral is: " << result << "\n\n";
        cout << "\nDo you want to run the program again? (Press 'Y' or 'y' to continue, or any other key to exit): ";
        cin >> check;
    } while (tolower(check) == 'y');

    return 0;
}

