/*
 Date: August 26th, 2025
 Author: MD MAHAFUZUR RAHMAN
 Roll: 2110428176
 Department of Applied Mathematics
 University Of Rajshahi
 LinkedIn: https://www.linkedin.com/in/itsmahafuz/
 GitHub: https://github.com/itsmahafuz
*/

/*
Curve fitting of the form y = a + bx + cx^2 using Gauss elimination
Numerical method: Normal equations for 2nd degree polynomial
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
using namespace std;

int main()
{
    cout.precision(6);
    cout.setf(ios::fixed);

    char choice;
    do
    {
        // -------------------- Input --------------------
        int m; // number of data points
        cout << "\nEnter the number of points to be entered: ";
        cin >> m;

        if (m < 3)
        { // For 2nd degree polynomial, need at least 3 points
            cout << "Need at least 3 points for 2nd degree polynomial.\n";
            return 0;
        }

        vector<double> x(m), y(m); // vectors to store x and y coordinates
        int degree = 2;
        int n = degree + 1; // number of unknown coefficients: a, b, c

        // Augmented matrix for normal equations: size n x (n+1)
        // vector<vector<double>> automatically allocates memory on heap
        // All elements initialized to 0.0
        vector<vector<double>> a(n, vector<double>(n + 1, 0.0));

        cout << "\nEnter data points (x, y):\n";
        for (int i = 0; i < m; i++)
        {
            cin >> x[i] >> y[i];
        }

        // -------------------- Compute sums for normal equations --------------------
        double sx = 0, sx2 = 0, sx3 = 0, sx4 = 0, sy = 0, sxy = 0, sx2y = 0;
        for (int i = 0; i < m; i++)
        {
            sx += x[i];
            sx2 += x[i] * x[i];
            sx3 += x[i] * x[i] * x[i];
            sx4 += x[i] * x[i] * x[i] * x[i];

            sy += y[i];
            sxy += x[i] * y[i];
            sx2y += x[i] * x[i] * y[i];
        }

        // -------------------- Setup Normal Equations --------------------
        // 3x4 augmented matrix for 2nd degree polynomial
        a = {
            {(double)m, sx, sx2, sy},
            {sx, sx2, sx3, sxy},
            {sx2, sx3, sx4, sx2y}};

        // -------------------- Pivotisation --------------------
        // Improve numerical stability by swapping rows if necessary
        for (int i = 0; i < n; i++)
        {
            for (int k = i + 1; k < n; k++)
            {
                if (fabs(a[i][i]) < fabs(a[k][i]))
                {
                    for (int j = 0; j < n + 1; j++)
                        swap(a[i][j], a[k][j]);
                }
            }
        }

        // -------------------- Gauss Elimination --------------------
        for (int i = 0; i < n; i++)
        {
            for (int k = i + 1; k < n; k++)
            {
                double t = a[k][i] / a[i][i];
                for (int j = 0; j < n + 1; j++)
                    a[k][j] -= t * a[i][j];
            }
        }

        // -------------------- Back Substitution --------------------
        double c[n]; // coefficients a, b, c
        for (int i = n - 1; i >= 0; i--)
        {
            if (fabs(a[i][i]) < 1e-12) // check for near-zero diagonal (numerical stability)
            {
                cout << "\nThe system is inconsistent..\n";
                return 0;
            }
            c[i] = a[i][n]; // start with augmented value
            for (int j = i + 1; j < n; j++)
                c[i] -= a[i][j] * c[j]; // subtract known contributions
            c[i] /= a[i][i];            // divide by pivot element
        }

        // -------------------- Output --------------------
        cout << "\nThe fitted polynomial: \n";
        cout << "\ny = " << c[0] << " + " << c[1] << "x + " << c[2] << "x^2\n";

        /*
        -------------------- Notes --------------------
        1. vector<vector<double>> a(n, vector<double>(n+1,0.0)) creates a 2D vector
           automatically initialized to 0.0. This avoids manual initialization loops.
        2. Pivotisation improves stability for Gaussian elimination.
        3. Back substitution solves for coefficients from the upper-triangular matrix.
        4. This code can be extended for higher-degree polynomials by increasing n.
        */
        cout << "\nDo you want to fit another curve? (y/Y for yes, any other key to exit): ";
        cin >> choice;
    } while (tolower(choice) == 'y');
}
