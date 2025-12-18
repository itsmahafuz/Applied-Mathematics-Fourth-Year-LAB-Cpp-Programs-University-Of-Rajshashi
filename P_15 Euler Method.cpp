/* 
 Date      : December 16, 2025
 Author    : MD MAHAFUZUR RAHMAN
 Roll      : 2110428176
 Department: Applied Mathematics
 University: University of Rajshahi
 LinkedIn  : https://www.linkedin.com/in/itsmahafuz/
 GitHub    : https://github.com/itsmahafuz
*/

/*
 Program Title:
 --------------
 Solution of First Order Ordinary Differential Equation
 using Euler’s Method

 Objective:
 ----------
 To numerically solve the first order differential equation
 dy/dx = f(x, y) using Euler’s method with given initial conditions.

 Method:
 -------
 Euler’s Method formula:
     y_{i+1} = y_i + h f(x_i, y_i)

 where h is the step size.

 Options:
 --------
 1. Compute y at a specific value of x
 2. Display y values over a given interval
*/

#include<bits/stdc++.h>
using namespace std;

/* 
 Function defining the given differential equation
 dy/dx = 1 + 2y
*/
double f(double x, double y)
{
    return 1 + 2*y;
}

int main()
{
    /* Set fixed decimal precision for output */
    cout << fixed << setprecision(5);

    char check;   // Variable to control program repetition

    do
    {
        int choice;   // Stores menu choice

        /* Display menu */
        cout << "\nEuler Method Menu:\n";
        cout << "1. Find the value of y at a specific point.\n";
        cout << "2. Display values of y over a range.\n";
        cout << "\nEnter your choice (1 or 2): ";
        cin >> choice;

        double x0, y0, x_final, h;

        /* Input initial values and step size */
        cout << "\nEnter the initial value of x: ";
        cin >> x0;
        cout << "\nEnter the initial value of y: ";
        cin >> y0;
        cout << "\nEnter the step size h (must be positive): ";
        cin >> h;

        /* Step size validation */
        if(h <= 0)
        {
            cout << "\nStep size must be positive.\n";
            return 1;
        }

        /* Input final x depending on choice */
        if(choice == 1)
        {
            cout << "\nEnter the value of x at which you want to find y: ";
            cin >> x_final;
        }
        else if(choice == 2)
        {
            cout << "\nEnter the final value of x: ";
            cin >> x_final;
        }
        else
        {
            cout << "\nInvalid Option.\n";
            return 0;
        }

        /* Calculate number of steps using ceil to handle floating point issues */
        int n = (int)ceil((x_final - x0) / h);

        /* Validate number of steps */
        if(n <= 0 || x_final <= x0)
        {
            cout << "\nInvalid input values.\n";
            return 1;
        }

        /* Declare arrays to store x and y values */
        vector<double> x(n+1), y(n+1);

        /* Assign initial conditions */
        x[0] = x0;
        y[0] = y0;

        /* Apply Euler’s Method */
        for(int i = 0; i < n; i++)
        {
            /* Check for division by zero if required */
            if(y[i] == 0)
            {
                cout << "\nDivision by zero encountered.\n";
                return 1;
            }

            /* Euler update formula */
            y[i+1] = y[i] + h * f(x[i], y[i]);

            /* Increment x */
            x[i+1] = x[i] + h;
        }

        /* Case 1: Value of y at a specific x */
        if(choice == 1)
        {
            cout << "\nThe value of y at x = " << x_final << " is: " << y[n] << endl;

            double exact, pcerr;

            /* Input exact value for error calculation */
            cout << "\nEnter the exact value of y at x = " << x_final << ": ";
            cin >> exact;

            /* Percentage error calculation */
            if(exact != 0)
            {
                pcerr = fabs((exact - y[n]) / exact) * 100;
                cout << "\nPercentage error is: " << pcerr << " %.\n";
            }
            else
            {
                cout << "\nExact value is zero, percentage error undefined.\n";
            }
        }

        /* Case 2: Display table of values */
        else if(choice == 2)
        {
            cout << "\nValues of y at regular intervals:\n";
            cout << left << setw(12) << "x" << setw(15) << "y" << endl;
            cout << string(40, '-') << endl;

            /* Print computed values */
            for(int i = 0; i <= n; i++)
            {
                cout << left << setw(12) << x[i] << setw(15) << y[i] << endl;
            }
        }

        /* Ask user if they want to run again */
        cout << "\nDo you want to run the program again? (y/n): ";
        cin >> check;

    } while(tolower(check) == 'y');

    return 0;   // Successful program termination
}




