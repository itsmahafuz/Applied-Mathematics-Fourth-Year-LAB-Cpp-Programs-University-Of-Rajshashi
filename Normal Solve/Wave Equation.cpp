/*
 Date: August 25th, 2025
 Author: MD MAHAFUZUR RAHMAN
 Roll: 2110428176
 Department of Applied Mathematics
 University Of Rajshahi
 LinkedIn: https://www.linkedin.com/in/itsmahafuz/
 GitHub: https://github.com/itsmahafuz
*/

/*
  Numerical solution of the 1D wave equation:
      u_tt = c^2 * u_xx
  using the explicit central-difference finite difference scheme.

  Notes:
  - CFL number: alpha = c * k / h
      (must satisfy alpha <= 1 for stability)
  - Initial displacement: u(x,0) = sin^3(πx)
  - Initial velocity:     u_t(x,0) = 0
  - Boundary conditions:  Dirichlet type
      u(x_i, t) = u_i, u(x_f, t) = u_f
*/

#include <iostream>
#include <cmath>
#include<vector>
#include <iomanip>
#define pi 3.14159
using namespace std;

// Function for initial displacement u(x,0)
double f(double x)
{
    return pow(sin(pi * x), 3);
}

int main()
{
    cout.precision(6);
    cout.setf(ios::fixed);

    // Declare variables
    double c, alpha, h, k, x, t; // wave speed, CFL number, space/time steps, coordinates
    double x_i, x_f, t_i, t_f;   // spatial and temporal limits
    double u_i, u_f;             // boundary values at x_i and x_f
    int m, n;                    // number of spatial and temporal steps

    cout << "\n================ 1D Wave Equation Solver (Finite Difference) ================\n\n";

    // Input wave speed
    cout << "Enter the wave speed (c): ";
    cin >> c;

    // Input spatial boundaries and corresponding boundary values
    cout << "Enter initial x and corresponding u (left boundary condition): ";
    cin >> x_i >> u_i;

    cout << "Enter final x and corresponding u (right boundary condition): ";
    cin >> x_f >> u_f;

    t_i = 0; // initial time
    cout << "Enter the final simulation time: ";
    cin >> t_f;

    // Input spatial and temporal steps with CFL condition check
check1:
    cout << "Enter the spatial step size (h) and time step size (k), separated by space: ";
    cin >> h >> k;
    alpha = c * (k / h); // CFL number
    if (alpha > 1.0)
    {
        cout << "CFL condition violated (alpha > 1). Please enter new values of h and k.\n";
        goto check1;
    }

    // Calculate number of spatial (m) and temporal (n) divisions
    m = (int)round((x_f - x_i) / h);
    n = (int)round((t_f - t_i) / k);

    // 2D array for storing u(x,t)
    // Rows: time index i = 0..n
    // Columns: space index j = 0..m
    // double u[n+1][m+1]; 

    vector<vector<double>>u(n+1,vector<double>(m+1,0.0)); // 2D vector for u(x,t)
    /*Replacing static array with vector for safety and flexibility
     vector automatically allocates memory on the heap, avoiding stack overflow for large n and m
     All elements are initialized to 0.0*/
    

    // Set Dirichlet boundary conditions for all time levels
    for (int i = 0; i <= n; ++i)
    {
        u[i][0] = u_i; // left boundary
        u[i][m] = u_f; // right boundary
    }

    // Set initial displacement (time level i=0)
    for (int j = 1; j <= m - 1; ++j)
    {
        x = x_i + j * h; // compute spatial position
        u[0][j] = f(x);  // initial displacement
    }

    // Compute first time level (i=1) using zero initial velocity
    for (int j = 1; j <= m - 1; ++j)
    {
        u[1][j] = u[0][j] + 0.5 * (alpha * alpha) *(u[0][j + 1] - 2 * u[0][j] + u[0][j - 1]);
    }

    // Advance in time using central-difference in space and time
    for (int i = 1; i <= n - 1; ++i)
    {
        for (int j = 1; j <= m - 1; ++j)
        {
            u[i + 1][j] = 2 * u[i][j] - u[i - 1][j] + (alpha * alpha) * (u[i][j + 1] - 2 * u[i][j] + u[i][j - 1]);
        }
    }

    // Menu-driven output
    int option;
    char cont; // variable to check if user wants to continue
    do
    {
        cout << "\n====================== Display Options ======================\n";
        cout << "1. Display u(x,t) for all x and all t\n";
        cout << "2. Display u(x) for all x at a specific time t\n";
        cout << "3. Display u(t) for all t at a specific position x\n";
        cout << "4. Display u at a single point (x,t)\n";
        cout << "============================================================\n";
        cout << "Enter your choice (1-4): ";
        cin >> option;

        if (option == 1)
        {
            /*
------------------ Exam Note ------------------
Purpose: Even if the simulation grid is very fine (e.g., h = k = 0.01, 0.001, 0.0001),
         we want to display u(x,t) only at selected coarse points:
             x = 0, 0.2, 0.4, ..., 1.0
             t = 0, 0.2, 0.4, ..., 1.0

Method: Calculate step sizes dynamically based on the fine grid:
         double output_step = 0.2;                  // coarse output step in x and t
         int i_step = (int)round(output_step / k);  // number of fine time steps to skip
         int j_step = (int)round(output_step / h);  // number of fine space steps to skip
         // or generally put i_step = 20 / 200 etc.

Usage: In the for-loops, increment by i_step and j_step to print only these coarse points.
       Example:
           for (int i = 0; i <= n; i += i_step) {
               for (int j = 0; j <= m; j += j_step) {
                   cout << u[i][j] << '\n';
               }
           }

Note: The same approach (using i_step and j_step) can also be applied
      in option 2 (x varies, t constant) and option 3 (x constant, t varies)  
      to print values only at the selected coarse points.
*/


            cout << "\n------------------- u(x,t) for all x and t -------------------\n";
            for (int i = 0; i <= n; i++)
            {
                t = t_i + i * k;
                for (int j = 0; j <= m; j++)
                {
                    x = x_i + j * h;
                    cout << "u(" << x << ", " << t << ") = " << u[i][j] << '\n';
                }
            }
        }
        else if (option == 2)
        {
            cout << "\nEnter the time t where you want to find u(x): ";
            cin >> t;
            int i = (int)round((t - t_i) / k);
            if (i < 0 || i > n)
            {
                cout << "Time t is out of range.\n";
                continue;
            }
            cout << "\n------------------- u(x) at t = " << t << " -------------------\n";
            for (int j = 0; j <= m; ++j)
            {
                x = x_i + j * h;
                cout << "u(" << x << ", " << t << ") = " << u[i][j] << '\n';
            }
        }
        else if (option == 3)
        {
            cout << "\nEnter the position x where you want to find u(t): ";
            cin >> x;
            int j = (int)round((x - x_i) / h);
            if (j < 0 || j > m)
            {
                cout << "Position x is out of range.\n";
                continue;
            }
            cout << "\n------------------- u(t) at x = " << x << " -------------------\n";
            for (int i = 0; i <= n; ++i)
            {
                t = t_i + i * k;
                cout << "u(" << x << ", " << t << ") = " << u[i][j] << '\n';
            }
        }
        else if (option == 4)
        {
            cout << "\nEnter the position x where you want to find u: ";
            cin >> x;
            cout << "Enter the time t where you want to find u: ";
            cin >> t;
            int i = (int)round((t - t_i) / k);
            int j = (int)round((x - x_i) / h);
            if (i < 0 || i > n || j < 0 || j > m)
            {
                cout << "x or t is out of range.\n";
                continue;
            }
            cout << "\nValue at (x,t) = (" << x << ", " << t << ") : u = " << u[i][j] << '\n';
        }
        else
        {
            cout << "Invalid option. Please choose a number between 1 and 4.\n";
        }

        cout << "\nDo you want to choose another option? Press y/Y for yes or n/N for no: ";
        cin >> cont;

    } while (cont == 'y' || cont == 'Y');
}
