/*
 Date: June 5th, 2025
 MD MAHAFUZUR RAHMAN
 Roll: 2110428176
 Department of Applied Mathematics
 University Of Rajshahi
 LinkedIn: https://www.linkedin.com/in/itsmahafuz/
 GitHub: https://github.com/itsmahafuz
*/

/* Program to calculate Interpolation by Newton’s forward formula with example */

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>
using namespace std;

class NewtonsForwardInterpolation
{
private:
    int n;                    // Number of data points
    vector<double> x;         // Stores x values
    vector<vector<double>> y; // Stores y values and the forward difference table

public:
    // Constructor: Initializes the size of vectors based on user input
    NewtonsForwardInterpolation()
    {
        cout << "\nEnter the number of values to be entered:\n";
        cin >> n;

        if (n < 2)
        {
            cout << "Error: Number of points must be at least 2.\n";
            exit(1); // Exit the program if input is invalid
        }

        x.resize(n);
        y.resize(n, vector<double>(n, 0)); // Initialize a 2D vector for the table
    }

    // Method to input x and y values
    void GetInput()
    {
        cout << "\nEnter the values of x (e.g., 1 2 3 4):\n";
        for (int i = 0; i < n; i++)
        {
            cin >> x[i];
        }

        cout << "\nEnter the corresponding values of y (e.g., 1 8 27 64):\n";
        for (int i = 0; i < n; i++)
        {
            cin >> y[i][0];
        }
    }

    // Method to calculate and display the forward difference table
    void ComputeAndDisplayDifferenceTable()
    {
        for (int j = 1; j < n; j++)
        { // Compute differences level by level
            for (int i = 0; i < n - j; i++)
            {
                y[i][j] = y[i + 1][j - 1] - y[i][j - 1];
            }
        }

        // Print the difference table
        cout << "\nThe forward difference table is as follows:\n\n";
        cout << left << setw(12) << "x" << setw(15) << "y";

        // Print headers for the difference columns
        for (int i = 1; i < n; i++)
        {
            cout << left << setw(15) << "d" + to_string(i) + "y";
        }
        cout << endl
             << string(15 * (n + 1), '-') << endl;

        for (int i = 0; i < n; i++)
        {
            cout << left << setw(12) << x[i]; // Print x values
            for (int j = 0; j < n - i; j++)
            {
                cout << left << setw(15) << y[i][j]; // Print differences
            }
            cout << endl;
        }
    }

    // Method to perform interpolation for a given value of x
    void PerformInterpolation()
    {
        bool calculateAgain = true;
        while (calculateAgain)
        {
            double xn, h, p, sum = y[0][0], temp = 1;
            cout << "\nEnter the value of x at which y is to be calculated:\n";
            cin >> xn;

            h = x[1] - x[0];     // Uniform spacing (assuming x is equally spaced)
            p = (xn - x[0]) / h; // Calculate p for forward interpolation formula

            // Compute the interpolated value
            for (int j = 1; j < n; j++)
            {
                temp = temp * (p - j + 1) / j;
                sum += temp * y[0][j];
            }

            cout << "\nThe value of y at x = " << xn << " is: " << sum << endl;

            cout << "\nWould you like to calculate y for another value of x? Press 1 for Yes or 0 for No: ";
            int subChoice;
            cin >> subChoice;
            calculateAgain = (subChoice == 1);
        }
    }
};

int main()
{
    cout.precision(6);
    cout.setf(ios::fixed);

    char choice;
    do
    {
        NewtonsForwardInterpolation interpolator;        // Create an object
        interpolator.GetInput();                         // Input x and y values
        interpolator.ComputeAndDisplayDifferenceTable(); // Compute and display table
        interpolator.PerformInterpolation();             // Perform interpolation

        cout << "\nDo you want to restart the program with new data points? Press Y/y for yes or any other key to exit:\n";
        cin >> choice;
    } while (tolower(choice) == 'y'); // Repeat if user enters 'y' or 'Y'

    return 0;
}
