/*
 Date      : December 13, 2025
 Name      : MD MAHAFUZUR RAHMAN
 Roll      : 2110428176
 Department: Applied Mathematics
 University: University of Rajshahi
 LinkedIn  : https://www.linkedin.com/in/itsmahafuz/
 GitHub    : https://github.com/itsmahafuz
*/

/*
 Program:
 --------
 This program solves a system of two nonlinear equations
 using the Newton–Raphson iterative method.

 Given system:
  f(x,y) = x^2 - y^2 - 3 = 0
  g(x,y) = x^2 + y^2 - 13 = 0

 The method uses Jacobian matrix and continues iteration
 until the desired accuracy is achieved.
*/

#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

/* Definition of the given nonlinear equations */
double f(double x, double y)
{
    return x*x - y*y - 3;
}

double g(double x, double y)
{
    return x*x + y*y - 13;
}

/* Partial derivatives of f and g */
double fx(double x, double y) { return 2*x; }
double fy(double x, double y) { return -2*y; }
double gx(double x, double y) { return 2*x; }
double gy(double x, double y) { return 2*y; }

/*
 Function: newtonRaphson
 -----------------------
 Solves the system using Newton–Raphson method
 x0, y0 : initial approximations
 tol    : desired accuracy
*/
void newtonRaphson(double x0, double y0, double tol)
{
    double x = x0, y = y0;
    double h, k, d;
    int iter = 0;

    cout << "\n-------------------------------------------------------------\n";
    cout << " Newton–Raphson Method for System of Nonlinear Equations\n";
    cout << "-------------------------------------------------------------\n";
    cout << "Iter        x            y           f(x,y)        g(x,y)\n";
    cout << "-------------------------------------------------------------\n";

    while(true)
    {
        /* Jacobian determinant */
        d = fx(x,y)*gy(x,y) - fy(x,y)*gx(x,y);

        /* Check for singular Jacobian */
        if(fabs(d) < 1e-9)
        {
            cout << "\nJacobian determinant is nearly zero.\n";
            cout << "Method fails for the chosen initial values.\n";
            return;
        }

        /* Newton–Raphson correction terms */
        h = (-f(x,y)*gy(x,y) + fy(x,y)*g(x,y)) / d;
        k = (-fx(x,y)*g(x,y) + f(x,y)*gx(x,y)) / d;

        /* Update the solution */
        x = x + h;
        y = y + k;
        iter++;

        /* Display iteration results */
        cout << setw(3) << iter << "   "
             << setw(12) << x << "   "
             << setw(12) << y << "   "
             << setw(12) << f(x,y) << "   "
             << setw(12) << g(x,y) << endl;

        /* Convergence check */
        if(fabs(f(x,y)) < tol && fabs(g(x,y)) < tol)
        {
            cout << "-------------------------------------------------------------\n";
            cout << " Convergence achieved successfully.\n";
            cout << " Approximate solution:\n";
            cout << " x = " << x << ",  y = " << y << endl;
            cout << "-------------------------------------------------------------\n";
            return;
        }

        /* Safety check for maximum iterations */
        if(iter > 100)
        {
            cout << "\nMaximum number of iterations exceeded.\n";
            cout << "The method may not converge.\n";
            return;
        }
    }
}

int main()
{
    cout.precision(6);
    cout.setf(ios::fixed);

    char choice;
    do
    {
        double x, y, acc;

        cout << "\nEnter initial approximations for x and y: ";
        cin >> x >> y;

        cout << "Enter the required accuracy (tolerance): ";
        cin >> acc;

        newtonRaphson(x, y, acc);

        cout << "\nDo you want to try different initial values? (y/n): ";
        cin >> choice;

    } while(tolower(choice) == 'y');

    return 0;
}

