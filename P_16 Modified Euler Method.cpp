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
 Solution of Ordinary Differential Equation using
 Modified Euler (Heun’s) Method

 Objective:
 ----------
 To approximate the solution of a first-order
 differential equation dy/dx = f(x,y)
 using Modified Euler Method.

 Method:
 -------
 1. Take initial values (x0, y0)
 2. Choose step size h
 3. Use predictor formula
 4. Apply corrector formula
 5. Repeat until required point is reached
*/

#include<bits/stdc++.h>
using namespace std;

/* Differential equation dy/dx = f(x,y) */
double f(double x, double y)
{
    return 1 + 2*y;
}

int main()
{
    cout << fixed << setprecision(6);   // set output precision

    int choice, n;

    /* Menu for user choice */
    cout << "\nModified Euler Method Menu:\n";
    cout << "\n1. Find the value of y at a specific point.\n";
    cout << "\n2. Display values of y over a range at regular intervals.\n";
    cout << "\nEnter your choice (1 or 2): ";
    cin >> choice;

    double x0, y0, x_final, h;

    /* Input initial conditions and step size */
    cout << "\nEnter the initial value of x: ";
    cin >> x0;
    cout << "\nEnter the initial value of y: ";
    cin >> y0;
    cout << "\nEnter the step size h (positive): ";
    cin >> h;

    /* Step size validation */
    if(h <= 0)
    {
        cout << "\nStep size must be positive.\n";
        return 1;
    }

    /* ---------- Case 1: Value at a specific point ---------- */
    if(choice == 1)
    {
        cout << "\nEnter the value of x at which you want to find y: ";
        cin >> x_final;

        /* Number of steps */
        n = (int)round((x_final - x0) / h);

        if(n <= 0 || x_final <= x0)
        {
            cout << "\nInvalid input values.\n";
            return 1;
        }

        vector<double> x(n+1), y(n+1);

        /* Initial conditions */
        x[0] = x0;
        y[0] = y0;

        /* Modified Euler Iteration */
        for(int i = 0; i < n; i++)
        {
            double predictor = y[i] + h * f(x[i], y[i]);   // Predictor
            y[i+1] = y[i] + (h/2.0) *
                     (f(x[i], y[i]) + f(x[i] + h, predictor)); // Corrector
            x[i+1] = x[i] + h;
        }

        cout << "\nThe value of y at x = " << x_final << " is: " << y[n] << endl;

        /* Percentage error calculation */
        double exact, pcerr;
        cout << "\nEnter the exact value: ";
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

    /* ---------- Case 2: Tabular form over a range ---------- */
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

        /* Initial conditions */
        x[0] = x0;
        y[0] = y0;

        /* Display table header */
        cout << "\nValues of y at regular intervals:\n";
        cout << left << setw(12) << "x" << setw(15) << "y" << endl;
        cout << string(40, '-') << endl;

        /* Modified Euler Iteration */
        for(int i = 0; i < n; i++)
        {
            cout << left << setw(12) << x[i] << setw(15) << y[i] << endl;

            double predictor = y[i] + h * f(x[i], y[i]);
            y[i+1] = y[i] + (h/2.0) *
                     (f(x[i], y[i]) + f(x[i] + h, predictor));
            x[i+1] = x[i] + h;
        }

        /* Final point */
        cout << left << setw(12) << x[n] << setw(15) << y[n] << endl;
    }

    return 0;
}

