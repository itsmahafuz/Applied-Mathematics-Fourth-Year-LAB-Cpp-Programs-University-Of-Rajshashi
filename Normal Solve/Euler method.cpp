/*
 Date: July 17th, 2025
 Author: MD MAHAFUZUR RAHMAN
 Roll: 2110428176
 Department of Applied Mathematics
 University Of Rajshahi
 LinkedIn: https://www.linkedin.com/in/itsmahafuz/
 GitHub: https://github.com/itsmahafuz
*/

/*
🔷 Problem Statement:
Numerical solution of first order Differential Equation (DE) of the type:
        dy/dx = f(x, y)
using Euler's Method at a point and for particular range with example. :

Options:
  ▪ Option 1: To find the value of y at a specific point.
  ▪ Option 2: To display values at regular intervals over a range.
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;

// Define the differential equation dy/dx = f(x, y)
double f(double x, double y)
{
    return 1 + 2 * y; // Example: dy/dx = 1 + 2y
}

int main()
{
    cout << fixed << setprecision(6); // Set precision for floating point output

    int choice;
    cout << "\n Euler Method Menu:\n";
    cout << "1. Find the value of y at a specific point\n";
    cout << "2. Display values of y over a range at regular intervals\n";
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    if (choice == 1)
    {
        // ======= Option 1: Value at a specific x =======
        double x0, y0, x_final;
        int n;

        cout << "\nEnter the initial value of x : ";
        cin >> x0;
        cout << "Enter the initial value of y : ";
        cin >> y0;
        cout << "Enter the value of x at which y is needed : ";
        cin >> x_final;
        // cout << "Enter the number of sub-divisions : ";
        // cin >> n;
        double h;
        cout<<"\nEnter the value of h (step size) : ";
        cin>>h;
        n = (int)((x_final - x0) / h);

        // Error handling
        if (n <= 0 || x_final <= x0)
        {
            cout << "\n Invalid input values.\n";
            return 1;
        }

        // double h = (x_final - x0) / n; // Step size
        
        vector<double> x(n + 1), y(n + 1); // Vectors to store x and y values

        // Initial conditions
        x[0] = x0;
        y[0] = y0;

        // Euler's iteration
        for (int i = 0; i < n; i++)
        {
            y[i + 1] = y[i] + h * f(x[i], y[i]);
            x[i + 1] = x[i] + h;
        }

        // Final output
        cout << "\n The value of y at x = " << x_final << " is " << y[n] << endl;
    }

    else if (choice == 2)
    {
        // ======= Option 2: Values over a range =======
        double x0, y0, x_final;
        cout << "\nEnter the initial value of x : ";
        cin >> x0;
        cout << "Enter the initial value of y : ";
        cin >> y0;
        cout << "Enter the final value of x : ";
        cin >> x_final;

        double h = 0.0001;         // Small step size for better accuracy
        double epsilon = 1e-6;     // Tolerance for floating-point comparison
        double next_p = 0.0;       // Next x value where output is printed

        cout << "\n🔹 Values of y at regular intervals:\n";
        cout << setw(10) << "x" << setw(16) << "y" << endl;
        cout << string(36, '-') << endl;

        // Iterating using Euler's Method
        while (x0 <= x_final + epsilon)
        {
            // Check if x0 is close to the next output point (e.g., 0.0, 0.2, 0.4...)
            if (fabs(x0 - next_p) < epsilon)
            {
                cout << setw(10) << next_p << setw(16) << y0 << endl;
                next_p += 0.2; // Print y at every 0.2 interval
            }

            // Euler formula: y_(n+1) = y_n + h*f(x_n, y_n)
            y0 = y0 + h * f(x0, y0);
            x0 = x0 + h;
        }
    }

    else
    {
        // ======= Invalid menu option =======
        cout << "\n Invalid choice. Please run again and choose 1 or 2.\n";
    }

    return 0;
}
