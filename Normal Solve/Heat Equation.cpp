/*
 Date: August 11th, 2025
 Author: MD MAHAFUZUR RAHMAN
 Roll: 2110428176
 Department of Applied Mathematics
 University Of Rajshahi
 LinkedIn: https://www.linkedin.com/in/itsmahafuz/
 GitHub: https://github.com/itsmahafuz
*/

/*
  Numerical solutions of parabolic type PDE (∂u/∂t) = c^2 (∂²u/∂x²)
  by finite difference formula.

Example:
Let’s consider the heat equation problem:
    ∂u/∂t = ∂²u/∂x²
Subject to the conditions:
    u(x, 0) = sin(πx), 0 ≤ x ≤ 1
    u(0, t) = u(1, t) = 0
*/

#include <iostream>
#include <cmath>
#include<vector>
#include <iomanip>
using namespace std;

#define pi 3.14159265

// Initial condition function u(x,0)
double f(double x) {
    return sin(pi * x);
}

// Exact solution for reference (not used in main computation)
double exactf(double x,double t) {
    return exp(-pi * pi*t) * sin(pi * x);
}

int main() {
    cout.precision(6);
    cout.setf(ios::fixed);

    double cc, L, x1, x2;
    cout << "\nEnter the value of c^2:\n";
    cin >> cc;

    cout << "\nEnter the initial value of x:\n";
    cin >> x1;
    cout << "\nEnter the final value of x:\n";
    cin >> x2;
    L = x2 - x1; // domain length

    double t1 = 0, t2; // initial simulation time is t1 = 0
    cout << "\nEnter the final simulation time:\n";
    cin >> t2;

    double h, k;
tryhk:
    cout << "\nEnter the value of h and k respectively:\n";
    cin >> h >> k;

    double alpha = (cc * k) / (h * h); // stability parameter

    // Stability condition check
    if (alpha < 0 || alpha > 0.5) {
        cout << "\nStability condition violated (0 <= alpha <= 0.5 required)!\n";
        cout << "\nTry with new values of h and k..\n";
        goto tryhk;
    }

    // Number of space and time divisions
    int m = L / h;
    int n = (t2 - t1) / k;

    // 2D array for solution u[time][space]
    // double u[n+1][m+1];
    // // Initialize all values to zero
    // for (int i = 0; i <= n; i++) {
    //     for (int j = 0; j <= m; j++) {
    //         u[i][j] = 0;
    //     }
    // }
       vector<vector<double>>u(n+1,vector<double>(m+1,0.0)); // 2D vector for u(x,t)
    /*Replacing static array with vector for safety and flexibility
     vector automatically allocates memory on the heap, avoiding stack overflow for large n and m
     All elements are initialized to 0.0*/

    double x, t;

    // Initial condition: u(x,0) = sin(pi * x) → i = 0 row
    for (int j = 0; j <= m; j++) {
        x = x1 + j * h;
        u[0][j] = f(x);
    }

    // Boundary conditions for all times: u(0,t) = 0, u(L,t) = 0
    for (int i = 0; i <= n; i++) {
        u[i][0] = 0;     // left boundary
        u[i][m] = 0;     // right boundary
    }

    // Time stepping loop (explicit FTCS method)
    for (int i = 0; i <= n - 1; i++) {
        for (int j = 1; j <= m - 1; j++) {
            u[i + 1][j] = u[i][j] + alpha * (u[i][j + 1] - 2 * u[i][j] + u[i][j - 1]);
        }
    }

    int option;
    char choice;
    do {
        cout << "\nChoose option how you want the result:\n";
        cout << "Press (1): x, t both vary\n";
        cout << "Press (2): x vary, t constant\n";
        cout << "Press (3): x constant, t vary\n";
        cout << "Press (4): Specific (x,t) value\n";
        cout << "Enter option:\n";
        cin >> option;

        if (option == 1) { // Print all u(x,t) values
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
            for (int i = 0; i <= n; i++) {
                t = t1 + i * k;
                for (int j = 0; j <= m; j++) {
                    x = x1 + j * h;
                    cout << "u(" << x << ", " << t << ") = " << u[i][j] << endl;
                }
            }
            cout << "\nIf you wanna try again then press Y/y otherwise press any other key:\n";
            cin >> choice;
        }
        else if (option == 2) { // x varies, t fixed
            cout << "\nEnter value of t:\n";
            cin >> t;
            int i = (t - t1) / k;
            for (int j = 0; j <= m; j++) {
                x = x1 + j * h;
                cout << "u(" << x << ", " << t << ") = " << u[i][j] << endl;
            }
            cout << "\nIf you wanna try again then press Y/y otherwise press any other key:\n";
            cin >> choice;
        }
        else if (option == 3) { // t varies, x fixed
            cout << "\nEnter the value of x:\n";
            cin >> x;
            int j = (x - x1) / h;
            for (int i = 0; i <= n; i++) {
                t = t1 + i * k;
                cout << "u(" << x << ", " << t << ") = " << u[i][j] << endl;
            }
            cout << "\nIf you wanna try again then press Y/y otherwise press any other key:\n";
            cin >> choice;
        }
        else if (option == 4) { // specific (x,t)
            cout << "\nEnter the value of x:\n";
            cin >> x;
            cout << "\nEnter the value of t:\n";
            cin >> t;
            int i = (t - t1) / k;
            int j = (x - x1) / h;
            cout << "u(" << x << ", " << t << ") = " << u[i][j] << endl;
            cout<<"\nExact value : "<<exactf(x,t)<<endl;
            cout<<"\nError : "<<fabs(exactf(x,t)-u[i][j])<<endl;
            cout << "\nIf you wanna try again then press Y/y otherwise press any other key:\n";
            cin >> choice;
        }
        else {
            cout << "\nInvalid option!\n";
            cout << "\nIf you wanna try again then press Y/y otherwise press any other key:\n";
            cin >> choice;
        }
    } while (tolower(choice) == 'y');
}
 
