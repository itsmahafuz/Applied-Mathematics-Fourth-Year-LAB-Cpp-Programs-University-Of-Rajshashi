/*
 Date: June 4th, 2025
 MD MAHAFUZUR RAHMAN
 Roll: 2110428176
 Department of Applied Mathematics
 University Of Rajshahi
 LinkedIn: https://www.linkedin.com/in/itsmahafuz/
 GitHub: https://github.com/itsmahafuz
*/

/* Program to calculate Interpolation by Newton’s backward formula with example */

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    // Set precision and fixed-point format for output
    cout.precision(6);
    cout.setf(ios::fixed);

    char choice; // Variable to allow restarting the program
    do {
        int n;
        cout << "\nEnter the number of values to be entered:\n";
        cin >> n;

        // Declare arrays for x and y values
        double x[n], y[n][n];

        // Input x values
        cout << "\nEnter the values of x:\n";
        for (int i = 0; i < n; i++) {
            cin >> x[i];
        }

        // Input y values
        cout << "\nEnter the values of y:\n";
        for (int i = 0; i < n; i++) {
            cin >> y[i][0]; // Store corresponding y values in the first column
        }

        // Calculate the backward difference table
        for (int j = 1; j < n; j++) { // Iterate over levels of the table
            for (int i = n - 1; i >= j; i--) { // Iterate backward for each level
                y[i][j] = y[i][j - 1] - y[i - 1][j - 1]; // Compute backward difference
            }
        }

        // Print the backward difference table
        cout << "\nThe backward difference table is as follows:\n\n";
        cout << left << setw(12) << "x" << setw(15) << "y";

        // Print headers for the difference columns
        for (int i = 1; i < n; i++) {
            cout << left << setw(15) << "d" + to_string(i) + "y";
        }
        cout << "\n" << string(15 * (n + 1), '-') << "\n";

        // Print the rows of the table
        for (int i = 0; i < n; i++) {
            cout << left << setw(12) << x[i]; // Print x value
            for (int j = 0; j <= i; j++) {
                cout << left << setw(15) << y[i][j]; // Print y values and differences
            }
            cout << endl;
        }

        // Loop for interpolation
        bool calculateAgain = true;
        while (calculateAgain) {
            double xn, h, p, sum = y[n - 1][0], temp = 1;
            h = x[1] - x[0]; // Calculate uniform spacing h

            // Input the value of x at which y is to be calculated
            cout << "\nEnter the value of x at which y is to be calculated:\n";
            cin >> xn;

            // Calculate p for backward interpolation
            p = (xn - x[n - 1]) / h; // p = (x - x_n) / h
            for (int j = 1; j < n; j++) {
                temp = temp * (p + j - 1) / j; // Compute the factorial term
                sum = sum + temp * y[n - 1][j]; // Add the term to the interpolated value
            }

            // Print the interpolated value
            cout << "\nThe value of y at x = " << xn << " is: " << sum << endl;

            cout << "\nWould you like to calculate y for another value of x? Press 1 for Yes or 0 for No: ";
            int subChoice;
            cin >> subChoice;
            calculateAgain = (subChoice == 1);
        }

        cout << "\nDo you want to restart the program with new data points? Press Y/y for Yes or any other key to exit:\n";
        cin >> choice;

    } while (tolower(choice) == 'y');

    return 0;
}
