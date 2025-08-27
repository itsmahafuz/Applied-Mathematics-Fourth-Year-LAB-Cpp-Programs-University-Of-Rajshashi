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
Curve fitting of the form y = a + bx + cx^2 + dx^3 using Gauss elimination
Numerical method: Normal equations for 3rd degree polynomial
*/

#include<iostream>
#include<iomanip>
#include<cmath>
#include<vector>
using namespace std;

int main()
{
    cout.precision(4);
    cout.setf(ios::fixed);
    char choice;
    do{
        // -------------------- Input --------------------
    int m; // number of data points
    cout << "\nEnter the number of points to be entered: ";
    cin >> m;

    if(m < 4) { // For 3rd degree polynomial, need at least 4 points
        cout << "Need at least 4 points for 3rd degree polynomial.\n";
        return 0;
    }

    vector<double> x(m), y(m); // vectors to store x and y coordinates
    int degree = 3;
    int n = degree + 1; // number of unknown coefficients: a, b, c, d

    // Augmented matrix for normal equations: size n x (n+1)
    // vector<vector<double>> automatically allocates memory on heap
    // All elements initialized to 0.0
    vector<vector<double>> a(n, vector<double>(n + 1, 0.0));

    cout << "\nEnter data points (x, y):\n";
    for(int i = 0; i < m; i++) {
        cin >> x[i] >> y[i];
    }

    // -------------------- Compute sums for normal equations --------------------
    double sx=0, sx2=0, sx3=0, sx4=0, sx5=0, sx6=0;
    double sy=0, sxy=0, sx2y=0, sx3y=0;
    for(int i = 0; i < m; i++)
    {
        sx   += x[i];
        sx2  += x[i]*x[i];
        sx3  += x[i]*x[i]*x[i];
        sx4  += x[i]*x[i]*x[i]*x[i];
        sx5  += x[i]*x[i]*x[i]*x[i]*x[i];
        sx6  += x[i]*x[i]*x[i]*x[i]*x[i]*x[i];

        sy   += y[i];
        sxy  += x[i]*y[i];
        sx2y += x[i]*x[i]*y[i];
        sx3y += x[i]*x[i]*x[i]*y[i];
    }

    // -------------------- Setup Normal Equations --------------------
    // 4x5 augmented matrix for 3rd degree polynomial
    a = {
        {(double)m, sx, sx2, sx3, sy},
        {sx, sx2, sx3, sx4, sxy},
        {sx2, sx3, sx4, sx5, sx2y},
        {sx3, sx4, sx5, sx6, sx3y}
    };

    // -------------------- Pivotisation --------------------
    for(int i = 0; i < n; i++)
    {
        for(int k = i + 1; k < n; k++)
        {
            if(fabs(a[i][i]) < fabs(a[k][i]))
            {
                for(int j = 0; j < n+1; j++)
                    swap(a[i][j], a[k][j]);
            }
        }
    }

    // -------------------- Gauss Elimination --------------------
    for(int i = 0; i < n; i++)
    {
        for(int k = i + 1; k < n; k++)
        {
            double t = a[k][i] / a[i][i];
            for(int j = 0; j < n+1; j++)
                a[k][j] -= t * a[i][j];
        }
    }

    // -------------------- Back Substitution --------------------
    double c[n]; // coefficients a, b, c, d
    for(int i = n-1; i >= 0; i--)
    {
        if(fabs(a[i][i]) < 1e-12)
        {
            cout << "\nThe system is inconsistent..\n";
            return 0;
        }
        c[i] = a[i][n];
        for(int j = i+1; j < n; j++)
            c[i] -= a[i][j] * c[j];
        c[i] /= a[i][i];
    }

    // -------------------- Output --------------------
    cout << "\nThe fitted polynomial:\ny = " << c[0];
    for(int i = 1; i <= degree; i++)
    {
        if(c[i] >= 0)
            cout << " + " << c[i] << "x";
        else
            cout << " - " << fabs(c[i]) << "x";
        if(i > 1) cout << "^" << i;
    }
    cout << "\n";

    /*
    -------------------- Notes --------------------
    1. vector<vector<double>> a(n, vector<double>(n+1,0.0)) creates a 2D vector
       automatically initialized to 0.0. This avoids manual initialization loops.
    2. Pivotisation improves stability for Gaussian elimination.
    3. Back substitution solves for coefficients from the upper-triangular matrix.
    4. Polynomial is printed in standard format with proper handling of + and - signs.
    5. Code can be extended for higher-degree polynomials by increasing n.
    */

    cout << "\nDo you want to fit another curve? (y/Y for yes, any other key to exit): ";
    cin>>choice;
    }while(tolower(choice)=='y');
    
}
