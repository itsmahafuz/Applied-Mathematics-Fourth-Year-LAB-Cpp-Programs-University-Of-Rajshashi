/*
 Program Title: Runge-Kutta 4th Order Method for Solving First Order Differential Equation
 Date      : December 17th, 2025
 Author    : MD MAHAFUZUR RAHMAN
 Roll      : 2110428176
 Department: Applied Mathematics
 University: University Of Rajshahi
 LinkedIn  : https://www.linkedin.com/in/itsmahafuz/
 GitHub    : https://github.com/itsmahafuz
*/

#include<bits/stdc++.h>
using namespace std;

/*
  Defines the differential equation:
  dy/dx = f(x, y)
*/
double f(double x, double y)
{
    return x / y;   // Given differential equation
}

int main()
{
    // Set fixed decimal output with 6 digits after decimal point
    cout << fixed << setprecision(6);

    char cc;  // To repeat the program

    do
    {
        int choice;
        cout << "\nRunge-Kutta 4th Order Method Menu:\n";
        cout << "1. Find the value of y at a specific point.\n";
        cout << "2. Display values of y over a range at regular intervals.\n";
        cout << "Enter your choice (1 or 2): ";
        cin >> choice;

        double x0, y0, x_final, h;

        // Input initial conditions
        cout << "\nEnter the initial value of x and y respectively:\n";
        cin >> x0 >> y0;

        // Input step size
        cout << "\nEnter the step size h (positive): \n";
        cin >> h;

        // Validation of step size
        if(h <= 0)
        {
            cout << "\nStep size h must be positive.\n";
            return 1;
        }

        int n;  // Number of steps

        /*------------------------------------------------
          Case 1: Find y at a specific point x = x_final
        ------------------------------------------------*/
        if(choice == 1)
        {
            cout << "\nEnter the value of x at which you want to find y:\n";
            cin >> x_final;

            // Calculate number of steps
            n = (int)((x_final - x0) / h);

            if(n <= 0 || x_final <= x0)
            {
                cout << "\nInvalid input values.\n";
                return 1;
            }

            double x = x0;
            double y = y0;
            double k1, k2, k3, k4;

            // RK-4 iteration
            for(int i = 0; i < n; i++)
            {
                k1 = h * f(x, y);
                k2 = h * f(x + h/2.0, y + k1/2.0);
                k3 = h * f(x + h/2.0, y + k2/2.0);
                k4 = h * f(x + h, y + k3);

                y = y + (k1 + 2*k2 + 2*k3 + k4) / 6.0;
                x = x + h;
            }

            cout << "\nThe value of y at x = " << x_final << " is " << y << endl;

            // Percentage error calculation
            double exact;
            cout << "\nEnter the exact value:\n";
            cin >> exact;

            if(exact != 0)
            {
                double pcerr = fabs((exact - y) / exact) * 100;
                cout << "\nPercentage error is " << pcerr << "%\n";
            }
            else
            {
                cout << "\nExact value is zero, percentage error undefined.\n";
            }
        }

        /*------------------------------------------------
          Case 2: Display values over a given range
        ------------------------------------------------*/
        else if(choice == 2)
        {
            cout << "\nEnter the final value of x:\n";
            cin >> x_final;

            n = (int)((x_final - x0) / h);

            if(n <= 0 || x_final <= x0)
            {
                cout << "\nInvalid input values.\n";
                return 1;
            }

            double x = x0;
            double y = y0;
            double k1, k2, k3, k4;

            // Table header
            cout << left << setw(12) << "x" << setw(15) << "y" << endl;
            cout << string(35, '-') << endl;
            cout << left << setw(12) << x << setw(15) << y << endl;

            // RK-4 iterations with tabular output
            for(int i = 0; i < n; i++)
            {
                k1 = h * f(x, y);
                k2 = h * f(x + h/2.0, y + k1/2.0);
                k3 = h * f(x + h/2.0, y + k2/2.0);
                k4 = h * f(x + h, y + k3);

                y = y + (k1 + 2*k2 + 2*k3 + k4) / 6.0;
                x = x + h;

                cout << left << setw(12) << x << setw(15) << y << endl;
            }
        }

        // Repeat option
        cout << "\nDo you want to run the code again? (y/Y to continue): ";
        cin >> cc;

    } while(tolower(cc) == 'y');

    return 0;
}

