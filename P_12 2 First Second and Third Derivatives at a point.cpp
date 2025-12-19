/*
 Date: September 30th, 2025
 Author: MD MAHAFUZUR RAHMAN
 Roll: 2110428176
 Department of Applied Mathematics
 University Of Rajshahi
 LinkedIn: https://www.linkedin.com/in/itsmahafuz/
 GitHub: https://github.com/itsmahafuz
*/

/*
 -------------------------------------------------------------------------
 Program Name : Least Squares Polynomial Curve Fitting with Derivatives

 Purpose:
 --------
 This program fits a polynomial of given degree to a set of data points
 using the Method of Least Squares.

 Steps involved:
 1. Read given data points (x_i, y_i)
 2. Form normal equations using least squares method
 3. Solve the system using Gaussian elimination
 4. Obtain polynomial coefficients
 5. Evaluate the polynomial and its 1st, 2nd and 3rd derivatives
    at a given value of x

 Mathematical Model:
 -------------------
 Fitted polynomial:
     y = a0 + a1 x + a2 x^2 + ... + an x^n
 -------------------------------------------------------------------------
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
using namespace std;

int main() 
{
    // Fix output up to 3 decimal places
    cout << fixed << setprecision(3);

    // -------------------- Input Data --------------------
    int N;   // Number of data points
    cout << "Enter the number of data points: ";
    cin >> N;

    // Vectors to store x and y values
    vector<double> x(N), y(N);

    cout << "Enter the x-axis values: ";
    for (int i = 0; i < N; i++)
        cin >> x[i];

    cout << "Enter the y-axis values: ";
    for (int i = 0; i < N; i++)
        cin >> y[i];

    // ---------------- Polynomial Degree -----------------
    int degree;   // Degree of polynomial to be fitted
    cout << "Enter the degree of the polynomial to fit: ";
    cin >> degree;

    // Number of unknown coefficients = degree + 1
    int n = degree + 1;

    // ---------------- Memory Allocation -----------------
    // a[]  : Polynomial coefficients
    // C[]  : Right-hand side vector of normal equations
    // X[]  : Stores sum of powers of x (Sx^i)
    vector<double> a(n), C(n), X(2 * degree + 1, 0.0);

    // Augmented matrix B for normal equations
    vector<vector<double>> B(n, vector<double>(n + 1, 0.0));

    // ---------------- Compute Sx^i ---------------------
    // X[i] = x1^i + x2^i + ... + xN^i
    for (int i = 0; i < 2 * n - 1; i++) 
    {
        for (int j = 0; j < N; j++)
            X[i] += pow(x[j], i);
    }

    // ---------------- Normal Matrix ---------------------
    // B[i][j] = Sx^(i+j)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            B[i][j] = X[i + j];

    // ---------------- RHS Vector ------------------------
    // C[i] = S(x^i * y)
    for (int i = 0; i < n; i++) 
    {
        C[i] = 0.0;
        for (int k = 0; k < N; k++)
            C[i] += pow(x[k], i) * y[k];

        // Store RHS in augmented matrix
        B[i][n] = C[i];
    }

    // ---------------- Pivoting --------------------------
    // Partial pivoting for numerical stability
    for (int i = 0; i < n; i++)
        for (int k = i + 1; k < n; k++)
            if (abs(B[i][i]) < abs(B[k][i]))
                swap(B[i], B[k]);

    // ---------------- Gaussian Elimination --------------
    // Convert matrix into upper triangular form
    for (int i = 0; i < n - 1; i++)
        for (int k = i + 1; k < n; k++) 
        {
            double t = B[k][i] / B[i][i];
            for (int j = i; j <= n; j++)
                B[k][j] -= t * B[i][j];
        }

    // ---------------- Back Substitution -----------------
    // Solve for polynomial coefficients a[i]
    for (int i = n - 1; i >= 0; i--) 
    {
        a[i] = B[i][n];
        for (int j = i + 1; j < n; j++)
            a[i] -= B[i][j] * a[j];
        a[i] /= B[i][i];
    }

    // ---------------- Print Coefficients ----------------
    cout << "\nCoefficients:\n";
    for (int i = 0; i < n; i++)
        cout << "a" << i << " = " << a[i] << endl;

    // ---------------- Print Polynomial ------------------
    cout << "\nFitted Polynomial: y = ";
    for (int i = 0; i < n; i++)
        cout << "(" << a[i] << ")x^" << i 
             << (i < n - 1 ? " + " : "");
    cout << "\n";

    // ---------------- Function Evaluation ----------------
    double t;
    cout << "\nEnter the value of x to compute function and derivatives: ";
    cin >> t;

    // Functional value y(t)
    double fv = 0.0;
    for (int i = 0; i < n; i++)
        fv += a[i] * pow(t, i);
    cout << "Functional Value y(" << t << ") = " << fv << endl;

    // ---------------- First Derivative ------------------
    double d1 = 0.0;
    for (int i = 1; i < n; i++)
        d1 += i * a[i] * pow(t, i - 1);
    cout << "1st Derivative y'(" << t << ") = " << d1 << endl;

    // ---------------- Second Derivative -----------------
    double d2 = 0.0;
    for (int i = 2; i < n; i++)
        d2 += i * (i - 1) * a[i] * pow(t, i - 2);
    cout << "2nd Derivative y''(" << t << ") = " << d2 << endl;

    // ---------------- Third Derivative ------------------
    double d3 = 0.0;
    for (int i = 3; i < n; i++)
        d3 += i * (i - 1) * (i - 2) * a[i] * pow(t, i - 3);
    cout << "3rd Derivative y'''(" << t << ") = " << d3 << endl;

    return 0;
}
