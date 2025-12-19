/*
 Date: September 26th, 2025
 Author: MD MAHAFUZUR RAHMAN
 Roll: 2110428176
 Department of Applied Mathematics
 University Of Rajshahi
 LinkedIn: https://www.linkedin.com/in/itsmahafuz/
 GitHub: https://github.com/itsmahafuz
*/

/*
  Numerical solution of parabolic type PDE
        ?u/?t = c² ?²u/?x²
  using the Explicit Finite Difference Method (FTCS scheme).

  Example (Heat Equation):
        ?u/?t = ?²u/?x²
  Subject to:
        u(x,0) = sin(px)
        u(0,t) = u(1,t) = 0
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <cctype>
using namespace std;

#define pi 3.14159265

// ----------------------------------------------------
// Initial condition function
// Defines u(x,0) at time t = 0
// ----------------------------------------------------
double f(double x)
{
    return sin(pi * x);
}

// ----------------------------------------------------
// Exact analytical solution
// Used for comparison and error calculation
// ----------------------------------------------------
double exactf(double x, double t)
{
    return exp(-(pi * pi) * t) * sin(pi * x);
}

int main()
{
    cout << fixed << setprecision(6);

    // -------------------------------
    // Input: coefficient and domain
    // -------------------------------
    double cc, L, x1, x2;
    cout << "\nEnter the value of c^2:\n";
    cin >> cc;

    cout << "\nEnter the initial value of x:\n";
    cin >> x1;
    cout << "\nEnter the final value of x:\n";
    cin >> x2;

    L = x2 - x1;   // Length of spatial domain

    // -------------------------------
    // Time interval
    // -------------------------------
    double t1 = 0, t2;
    cout << "\nEnter the final simulation time:\n";
    cin >> t2;

    // -------------------------------
    // Step sizes (space & time)
    // -------------------------------
    double h, k;
tryhk:
    cout << "\nEnter the value of h (space step) and k (time step):\n";
    cin >> h >> k;

    // Stability parameter for FTCS scheme
    double alpha = (cc * k) / (h * h);

    // Stability condition check
    if (alpha < 0 || alpha > 0.5)
    {
        cout << "\nStability condition violated (0 = alpha = 0.5 required)!\n";
        cout << "Try again with new values of h and k.\n";
        goto tryhk;
    }

    // -------------------------------
    // Grid size
    // -------------------------------
    int m = round(L / h);          // Number of space intervals
    int n = round((t2 - t1) / k);  // Number of time intervals

    // -------------------------------
    // Solution matrix u[i][j]
    // i ? time index, j ? space index
    // -------------------------------
    vector<vector<double>> u(n + 1, vector<double>(m + 1, 0.0));

    double x, t;

    // -------------------------------
    // Apply initial condition (t = 0)
    // -------------------------------
    for (int j = 0; j <= m; j++)
    {
        x = x1 + j * h;
        u[0][j] = f(x);
    }

    // -------------------------------
    // Apply boundary conditions
    // u(0,t) = 0 and u(L,t) = 0
    // -------------------------------
    for (int i = 0; i <= n; i++)
    {
        u[i][0] = 0.0;
        u[i][m] = 0.0;
    }

    // -------------------------------
    // Time-stepping loop (FTCS scheme)
    // u(i+1,j) = u(i,j) + a[ u(i,j+1) - 2u(i,j) + u(i,j-1) ]
    // -------------------------------
    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j < m; j++)
        {
            u[i + 1][j] =
                u[i][j] + alpha *
                (u[i][j + 1] - 2 * u[i][j] + u[i][j - 1]);
        }
    }

    // -------------------------------
    // Output menu
    // -------------------------------
    int option;
    char choice;
    do
    {
        cout << "\nChoose option how you want the result:\n";
        cout << "Press (1): x, t both vary\n";
        cout << "Press (2): x vary, t constant\n";
        cout << "Press (3): x constant, t vary\n";
        cout << "Press (4): Specific (x,t) value\n";
        cout << "Enter option:\n";
        cin >> option;

        if (option == 1)
        {
            // Case 1: Full solution table
            for (int i = 0; i <= n; i++)
            {
                t = t1 + i * k;
                for (int j = 0; j <= m; j++)
                {
                    x = x1 + j * h;
                    cout << "u(" << x << ", " << t << ") = " << u[i][j] << endl;
                }
            }
        }
        else if (option == 2)
        {
            // Case 2: Space variation at fixed time
            cout << "\nEnter value of t:\n";
            cin >> t;
            int i = round((t - t1) / k);

            if (i < 0 || i > n)
                cout << "Invalid t value!\n";
            else
            {
                for (int j = 0; j <= m; j++)
                {
                    x = x1 + j * h;
                    cout << "u(" << x << ", " << t << ") = " << u[i][j] << endl;
                }
            }
        }
        else if (option == 3)
        {
            // Case 3: Time variation at fixed space
            cout << "\nEnter value of x:\n";
            cin >> x;
            int j = round((x - x1) / h);

            if (j < 0 || j > m)
                cout << "Invalid x value!\n";
            else
            {
                for (int i = 0; i <= n; i++)
                {
                    t = t1 + i * k;
                    cout << "u(" << x << ", " << t << ") = " << u[i][j] << endl;
                }
            }
        }
        else if (option == 4)
        {
            // Case 4: Numerical vs Exact comparison
            cout << "\nEnter value of x:\n";
            cin >> x;
            cout << "\nEnter value of t:\n";
            cin >> t;

            int i = round((t - t1) / k);
            int j = round((x - x1) / h);

            if (i < 0 || i > n || j < 0 || j > m)
                cout << "Invalid (x,t) value!\n";
            else
            {
                cout << "u(" << x << ", " << t << ") = " << u[i][j] << endl;
                cout << "Exact value : " << exactf(x, t) << endl;
                cout << "Error       : " << fabs(exactf(x, t) - u[i][j]) << endl;
            }
        }
        else
        {
            cout << "Invalid option!\n";
        }

        cout << "\nDo you want to try again? (y/n): ";
        cin >> choice;

    } while (tolower(choice) == 'y');

    return 0;
}


