/*
 Date      : August 25th, 2025
 Author    : MD MAHAFUZUR RAHMAN
 Roll      : 2110428176
 Department: Applied Mathematics
 University: University of Rajshahi
 LinkedIn  : https://www.linkedin.com/in/itsmahafuz/
 GitHub    : https://github.com/itsmahafuz
*/

/*
 ------------------------------------------------------------------------
 Numerical solution of the 1D wave equation

     u_tt = c^2 u_xx

 using the explicit finite difference (central difference) scheme.

 Initial conditions:
     u(x,0)  = sin(px)
     u_t(x,0)= 0

 Boundary conditions (Dirichlet):
     u(x_i,t) = u_i
     u(x_f,t) = u_f

 Stability condition (CFL condition):
     alpha = (c * k) / h = 1

 Exact solution (for c = 1 and zero boundaries):
     u(x,t) = cos(pt) sin(px)
 ------------------------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

#define pi 3.14159

// Initial displacement function u(x,0)
double f(double x)
{
    return sin(pi * x);
}

// Exact analytical solution (valid for c = 1)
double exactf(double x, double t)
{
    return cos(pi * t) * sin(pi * x);
}

int main()
{
    cout << fixed << setprecision(6);

    // ---------------- Variable Declarations ----------------
    double c, alpha;        // wave speed and CFL number
    double h, k;            // spatial and temporal step sizes
    double x, t;            // space and time variables
    double x_i, x_f;        // spatial domain limits
    double t_i = 0.0, t_f;  // time domain limits
    double u_i, u_f;        // boundary values

    int m, n;               // number of spatial and temporal grid points

    // ---------------- Input Section ----------------
    cout << "\nEnter value of c: ";
    cin >> c;

    cout << "\nEnter initial x and corresponding u (left boundary): ";
    cin >> x_i >> u_i;

    cout << "\nEnter final x and corresponding u (right boundary): ";
    cin >> x_f >> u_f;

    cout << "\nEnter the final simulation time: ";
    cin >> t_f;

    // ---------------- CFL Condition Check ----------------
tryhk:
    cout << "\nEnter the value of h (space step) and k (time step): ";
    cin >> h >> k;

    alpha = (c * k) / h;

    if (alpha > 1.0)
    {
        cout << "\nCFL condition violated (alpha > 1). Try again.\n";
        goto tryhk;
    }

    // ---------------- Grid Size Calculation ----------------
    // ceil() ensures the full domain is covered
    m = ceil((x_f - x_i) / h);   // number of spatial steps
    n = ceil((t_f - t_i) / k);   // number of time steps

    // ---------------- Memory Allocation ----------------
    // u[i][j] ˜ u(x_j, t_i)
    vector<vector<double>> u(n + 1, vector<double>(m + 1, 0.0));

    // ---------------- Boundary Conditions ----------------
    for (int i = 0; i <= n; i++)
    {
        u[i][0] = u_i;   // left boundary
        u[i][m] = u_f;   // right boundary
    }

    // ---------------- Initial Displacement ----------------
    for (int j = 1; j < m; j++)
    {
        x = x_i + j * h;
        u[0][j] = f(x);
    }

    // ---------------- First Time Step (Zero Initial Velocity) ----------------
    for (int j = 1; j < m; j++)
    {
        u[1][j] = u[0][j]
                + 0.5 * alpha * alpha
                * (u[0][j + 1] - 2 * u[0][j] + u[0][j - 1]);
    }

    // ---------------- Time Marching Scheme ----------------
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < m; j++)
        {
            u[i + 1][j] =
                2 * u[i][j] - u[i - 1][j]
                + alpha * alpha
                * (u[i][j + 1] - 2 * u[i][j] + u[i][j - 1]);
        }
    }

    // ---------------- Menu Driven Output ----------------
    int option;
    char check;

    do
    {
        cout << "\nChoose option:\n";
        cout << "1. x and t both vary\n";
        cout << "2. x constant, t vary\n";
        cout << "3. x vary, t constant\n";
        cout << "4. Specific (x, t) value\n";
        cout << "Enter option no: ";
        cin >> option;

        if (option == 1)
        {
            for (int i = 0; i <= n; i++)
            {
                t = t_i + i * k;
                for (int j = 0; j <= m; j++)
                {
                    x = x_i + j * h;
                    cout << "u(" << x << ", " << t << ") = " << u[i][j] << endl;
                }
            }
        }
        else if (option == 2)
        {
            cout << "\nEnter the value of x: ";
            cin >> x;

            int j = ceil((x - x_i) / h);

            if (j < 0 || j > m)
                cout << "\nInvalid x value.\n";
            else
            {
                for (int i = 0; i <= n; i++)
                {
                    t = t_i + i * k;
                    cout << "u(" << x << ", " << t << ") = " << u[i][j] << endl;
                }
            }
        }
        else if (option == 3)
        {
            cout << "\nEnter the value of t: ";
            cin >> t;

            int i = ceil((t - t_i) / k);

            if (i < 0 || i > n)
                cout << "\nInvalid t value.\n";
            else
            {
                for (int j = 0; j <= m; j++)
                {
                    x = x_i + j * h;
                    cout << "u(" << x << ", " << t << ") = " << u[i][j] << endl;
                }
            }
        }
        else if (option == 4)
        {
            cout << "\nEnter x: ";
            cin >> x;
            cout << "Enter t: ";
            cin >> t;

            int i = ceil((t - t_i) / k);
            int j = ceil((x - x_i) / h);

            if (i < 0 || i > n || j < 0 || j > m)
                cout << "\nInvalid x or t value.\n";
            else
            {
                cout << "Numerical u(" << x << ", " << t << ") = " << u[i][j] << endl;
                cout << "Exact u(" << x << ", " << t << ") = " << exactf(x, t) << endl;
                cout << "Absolute Error = "
                     << fabs(exactf(x, t) - u[i][j]) << endl;
            }
        }

        cout << "\nDo you want the menu again? (y/n): ";
        cin >> check;

    } while (tolower(check) == 'y');

    return 0;
}

