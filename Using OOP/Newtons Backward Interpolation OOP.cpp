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
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

class NewtonsBackwardInterpolation {
private:
    int n; // Number of data points
    vector<double> x; // Vector to store x values
    vector<vector<double>> y; // 2D vector to store y values and the backward difference table

public:
    // Constructor: Initializes the number of data points and resizes the vectors
    NewtonsBackwardInterpolation() {
        cout << "\nEnter the number of values to be entered:\n";
        cin >> n;

        // Resize the vectors to hold n data points
        x.resize(n);
        y.resize(n, vector<double>(n, 0)); // Initialize all elements to 0
    }

    // Method to input the x and y values
    void getXYValues() {
        cout << "\nEnter the values of x:\n";
        for (int i = 0; i < n; i++)
            cin >> x[i]; // Input x values

        cout << "\nEnter the values of y:\n";
        for (int i = 0; i < n; i++)
            cin >> y[i][0]; // Input corresponding y values (first column of the table)
    }

    // Method to calculate and display the backward difference table
    void computeAndDisplayDifferenceTable() {
        // Compute the backward difference table
        for (int j = 1; j < n; j++) { // Loop over levels of differences
            for (int i = n - 1; i >= j; i--) { // Loop backward for each level
                y[i][j] = y[i][j - 1] - y[i - 1][j - 1]; // Calculate the difference
            }
        }

        // Print the backward difference table
        cout << "\nThe backward difference table is as follows:\n\n";
        cout << left << setw(12) << "x" << setw(15) << "y";

        // Print headers for difference columns
        for (int i = 1; i < n; i++) {
            cout << left << setw(15) << "d" + to_string(i) + "y";
        }
        cout << "\n" << string(15 * (n + 1), '-') << "\n";

        // Print rows of the table
        for (int i = 0; i < n; i++) {
            cout << left << setw(12) << x[i]; // Print x values
            for (int j = 0; j <=i; j++) { // Print y values and differences
                cout << left << setw(15) << y[i][j];
            }
            cout << endl; // New line after each row
        }
    }

    // Method to perform interpolation for a given value of x
    void performInterpolation() {
        bool calculateAgain = true; // Flag for repeated calculations
        while (calculateAgain) {
            double xn, h, p, sum = y[n - 1][0], temp = 1; // Initialize variables

            cout << "\nEnter the value of x at which y is to be calculated:\n";
            cin >> xn; // Input the value of x for interpolation

            h = x[1] - x[0]; // Calculate the uniform spacing h
            p = (xn - x[n - 1]) / h; // Calculate p for backward interpolation formula

            // Calculate interpolated value using Newton’s backward formula
            for (int i = 1; i < n; i++) {
                temp = temp * (p + i - 1) / i; // Update factorial term
                sum += temp * y[n - 1][i]; // Add term to interpolated value
            }

            // Display the interpolated value
            cout << "\nThe value of y at x = " << xn << " is: " << sum << endl;

            // Ask if user wants to calculate for another x value
            cout << "\nWould you like to calculate y for another value of x? Press 1 for Yes or 0 for No:\n";
            int subChoice;
            cin >> subChoice;
            calculateAgain = (subChoice == 1); // Update flag based on user input
        }
    }
};

int main() {
    // Set precision and fixed-point formatting for output
    cout.precision(6);
    cout.setf(ios::fixed);

    char choice; // Variable to allow restarting the program
    do {
        // Create an object of the class
        NewtonsBackwardInterpolation interpolator;

        // Get x and y values from the user
        interpolator.getXYValues();

        // Compute and display the backward difference table
        interpolator.computeAndDisplayDifferenceTable();

        // Perform interpolation for given values of x
        interpolator.performInterpolation();

        // Ask if user wants to restart with new data points
        cout << "\nDo you want to restart the program with new data points? Press Y/y for yes or any other key to exit:\n";
        cin >> choice;
    } while (tolower(choice) == 'y'); // Repeat if user enters 'Y' or 'y'

    return 0;
}
