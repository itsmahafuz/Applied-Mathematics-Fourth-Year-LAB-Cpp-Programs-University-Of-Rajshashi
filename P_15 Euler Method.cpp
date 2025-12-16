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
 To numerically solve the differential equation
 dy/dx = f(x,y) with a given initial condition.

 Method:
 -------
 Euler’s Method uses the formula:
     y_{i+1} = y_i + h f(x_i, y_i)

 where h is the step size.

 Options:
 --------
 1. Compute y at a specific value of x
 2. Display y values over a given interval
*/

#include<bits/stdc++.h>
using namespace std;

/* Defines the differential equation dy/dx = f(x,y) */
double f(double x, double y)
{
    return x/y;
}

int main()
{
    /* Set output precision */
    cout.precision(5);
    cout.setf(ios::fixed);

    int choice, n;

    /* Display menu */
    cout << "\nEuler Method Menu:\n";
    cout << "1. Find the value of y at a specific point\n";
    cout << "2. Display values of y over a range\n";
    cout << "\nEnter your choice (1 or 2): ";
    cin >> choice;

    double x0, y0, x_final, h;

    /* Input initial conditions and step size */
    cout << "\nEnter the initial value of x: ";
    cin >> x0;
    cout << "Enter the initial value of y: ";
    cin >> y0;
    cout << "Enter the step size h (must be positive): ";
    cin >> h;

    /* Validate step size */
    if(h <= 0)
    {
        cout << "\nStep size must be positive.\n";
        return 1;
    }

    /* ---------------- Choice 1 ---------------- */
    /* Find y at a specific value of x */
    if(choice == 1)
    {
        cout << "\nEnter the value of x at which you want to find y: ";
        cin >> x_final;

        /* Calculate number of steps */
        n = (int)round((x_final - x0) / h);

        /* Validate inputs */
        if(n <= 0 || x_final <= x0)
        {
            cout << "\nInvalid input values.\n";
            return 1;
        }

        vector<double> x(n+1), y(n+1);

        /* Assign initial values */
        x[0] = x0;
        y[0] = y0;

        /* Apply Euler’s Method */
        for(int i = 0; i < n; i++)
        {
            if(y[i] == 0)
            {
                cout << "\nDivision by zero encountered.\n";
                return 1;
            }
            y[i+1] = y[i] + h * f(x[i], y[i]);
            x[i+1] = x[i] + h;
        }

        cout << "\nThe value of y at x = " << x_final
             << " is: " << y[n] << endl;

        /* Percentage error calculation */
        double exact, pcerr;
        cout << "\nEnter the exact value of y at x = "
             << x_final << ": ";
        cin >> exact;

        if(exact != 0)
        {
            pcerr = fabs((exact - y[n]) / exact) * 100;
            cout << "\nPercentage error is: " << pcerr << " %\n";
        }
        else
        {
            cout << "\nExact value is zero, percentage error undefined.\n";
        }
    }

    /* ---------------- Choice 2 ---------------- */
    /* Display y values over a range */
    else if(choice == 2)
    {
        cout << "\nEnter the final value of x: ";
        cin >> x_final;

        n = (int)round((x_final - x0) / h);

        if(n <= 0 || x_final <= x0)
        {
            cout << "\nInvalid input values.\n";
            return 1;
        }

        vector<double> x(n+1), y(n+1);

        x[0] = x0;
        y[0] = y0;

        /* Display table header */
        cout << "\nValues of y at regular intervals:\n";
        cout << left << setw(12) << "x"
             << setw(15) << "y" << endl;
        cout << string(40, '-') << endl;

        /* Euler iteration and output */
        for(int i = 0; i < n; i++)
        {
            cout << left << setw(12) << x[i]
                 << setw(15) << y[i] << endl;

            if(y[i] == 0)
            {
                cout << "\nDivision by zero encountered.\n";
                return 1;
            }

            y[i+1] = y[i] + h * f(x[i], y[i]);
            x[i+1] = x[i] + h;
        }

        /* Print final value */
        cout << left << setw(12) << x[n]
             << setw(15) << y[n] << endl;
    }
    else
    {
        cout << "\nInvalid Choice.\n";
    }

    return 0;
}


