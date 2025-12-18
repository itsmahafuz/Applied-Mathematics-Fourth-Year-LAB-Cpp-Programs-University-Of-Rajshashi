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

/*
 Function: f(x, y)
 -----------------
 Defines the given first-order differential equation
     dy/dx = x - 2y
*/
double f(double x, double y)
{
    return x - 2*y;
}

int main()
{
    /* Set fixed precision for numerical output */
    cout << fixed << setprecision(5);

    char check;   // Controls repetition of the program

    do
    {
        int choice;   // Menu choice variable

        /* Display Modified Euler Method menu */
        cout << "\nModified Euler Menu:\n";
        cout << "1. Find the value of y at a specific point.\n";
        cout << "2. Display values of y over a range at regular intervals.\n";
        cout << "Enter your choice (1 or 2): ";
        cin >> choice;

        double x0, y0, x_final, h;

        /* Input initial values and step size */
        cout << "\nEnter the initial value of x: ";
        cin >> x0;
        cout << "\nEnter the initial value of y: ";
        cin >> y0;
        cout << "\nEnter the step size h (positive): ";
        cin >> h;

        /* Validate step size */
        if(h <= 0)
        {
            cout << "\nStep size must be positive.\n";
            return 1;
        }

        /* Input final x depending on selected option */
        if(choice == 1)
        {
            cout << "\nEnter the value of x at which you want to find y: ";
        }
        else if(choice == 2)
        {
            cout << "\nEnter the final value of x: ";
        }
        else
        {
            cout << "\nInvalid Choice.\n";
            return 0;
        }

        cin >> x_final;

        /* Calculate number of steps */
        int n = ceil((x_final - x0) / h);

        /* Validate input range */
        if(n <= 0 || x_final <= x0)
        {
            cout << "\nInvalid input values.\n";
            return 1;
        }

        /* Arrays to store x and y values */
        vector<double> x(n+1), y(n+1);

        /* Assign initial conditions */
        x[0] = x0;
        y[0] = y0;

        /* Modified Euler (Heun’s) Method computation */
        for(int i = 0; i < n; i++)
        {
            /* Predictor step */
            double y_predictor = y[i] + h * f(x[i], y[i]);

            /* Corrector step */
            y[i+1] = y[i] + (h/2) * ( f(x[i], y[i])  + f(x[i] + h, y_predictor) );

            /* Increment x */
            x[i+1] = x[i] + h;
        }

        /* Option 1: Value of y at a specific x */
        if(choice == 1)
        {
            cout << "\nThe value of y at x = " << x_final << " is: " << y[n] << endl;

            double exact;
            cout << "\nEnter the exact value of y at x = "<< x_final << ": ";
            cin >> exact;

            /* Percentage error calculation */
            if(exact != 0)
            {
                double pcerr = fabs((exact - y[n]) / exact) * 100;
                cout << "\nPercentage error is: "<< pcerr << "%.\n";
            }
            else
            {
                cout << "\nExact value is zero, percentage error undefined.\n";
            }
        }

        /* Option 2: Display tabulated values */
        else if(choice == 2)
        {
            cout << "\nValues of y at regular intervals:\n";
            cout << left << setw(12) << "x" << setw(15) << "y" << endl;
            cout << string(40, '-') << endl;

            for(int i = 0; i < n+1; i++)
            {
                cout << left << setw(12) << x[i]<< setw(15) << y[i] << endl;
            }
        }

        /* Ask user whether to repeat the program */
        cout << "\nDo you want to run the program again? (y/n): ";
        cin >> check;

    } while(tolower(check) == 'y');

    return 0;   // Successful termination
}

