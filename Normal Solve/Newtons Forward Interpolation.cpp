/*
 Date: June 3rd, 2025
 MD MAHAFUZUR RAHMAN
 Roll: 2110428176
 Department of Applied Mathematics
 University Of Rajshahi
 LinkedIn: https://www.linkedin.com/in/itsmahafuz/
 GitHub: https://github.com/itsmahafuz
*/

/* Program to calculate Interpolation by Newton's forward formula with example */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    // Set precision and fixed-point format for output
    cout.precision(6);
    cout.setf(ios::fixed);

    char choice; // Variable to allow restarting the program
    do {
        int i, j, n;

        // Input the number of values
        cout << "Enter the number of values to be entered:\n";
        cin >> n;

        double x[n], y[n][n]; // Declare arrays for x and y values

        // Input x values
        cout << "Enter the values of x:\n";
        for (i = 0; i < n; i++) {
            cin >> x[i]; // Store x values
        }

        // Input y values
        cout << "Enter the values of y:\n";
        for (i = 0; i < n; i++) {
            cin >> y[i][0]; // Store y values corresponding to x
        }

        // Calculate the forward difference table
        for (j = 1; j < n; j++) { // Loop over the levels of the difference table
            for (i = 0; i < n - j; i++) { // Loop over rows for each level
                y[i][j] = y[i + 1][j - 1] - y[i][j - 1]; // Calculate the difference
            }
        }

        // Print the forward difference table
        cout << "\nThe forward difference table is as follows:\n\n";
        cout << left << setw(12) << "x" << setw(15) << "y";

        // Print headers for the difference columns
        for (i = 1; i < n; i++) {
            cout << left << setw(15) << "d" + to_string(i) + "y";
        }
        cout << "\n" << string(15 * (n + 1), '-') << "\n";

        // Print the rows of the table
        for (i = 0; i < n; i++) {
            cout << left << setw(12) << x[i]; // Print x value
            for (j = 0; j < n - i; j++) { // Print differences for the current row
                cout << left << setw(15) << y[i][j]; // Print y values and differences
            }
            cout << "\n"; // New line after each row
        }

        // Loop for interpolation
        bool calculateAgain = true;
        while (calculateAgain) {
            double xn, h, p, sum = y[0][0], temp = 1;
            h = x[1] - x[0]; // Calculate uniform spacing h

            // Input the value of x at which y is to be calculated
            cout << "\nEnter the value of x at which y is to be calculated:\n";
            cin >> xn;

            // Calculate the interpolation value using Newton's Forward Formula
            p = (xn - x[0]) / h; // Calculate the value of p
            for (j = 1; j < n; j++) {
                temp = temp * (p - j + 1) / j; // Update the factorial terms
                sum += temp * y[0][j]; // Add the term to the interpolated value
            }

            // Output the result
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
