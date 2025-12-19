/*
  Program Title : RK4 Method for System of ODEs
  Description   : This program solves a system of first-order ordinary differential 
                  equations (dy/dx = z, dz/dx = -y) using the classical 
                  Runge-Kutta 4th order method. The user can either compute y and z 
                  at a specific value of x or display y and z over a range of x values.
                  The results can also be exported to an Excel-ready CSV file for 
                  further analysis, such as plotting phase portraits.
  Date          : December 18th, 2025
  Author        : MD MAHAFUZUR RAHMAN
  Roll          : 2110428176
  Department    : Applied Mathematics
  University    : University Of Rajshahi
  LinkedIn      : https://www.linkedin.com/in/itsmahafuz/
  GitHub        : https://github.com/itsmahafuz
*/

#include <bits/stdc++.h>
using namespace std;

// Functions representing the system of ODEs
double f(double x, double y, double z) { return z; }   // dy/dx = z
double g(double x, double y, double z) { return -y; } // dz/dx = -y

int main() {
    cout << fixed << setprecision(6); // 6 decimal precision for output
    char again; // variable to control repetition of calculations

    do {
        // ===== Menu =====
        int choice;
        cout << "\nRK-4 Method Menu (System of Equations):\n";
        cout << "1. Find y and z at a specific value of x.\n";
        cout << "2. Display y and z over a range.\n";
        cout << "\nEnter your choice (1 or 2): ";
        cin >> choice;

        // ===== Input initial conditions =====
        double x0, y0, z0, x_final, h;
        cout << "\nEnter the initial value of x: ";
        cin >> x0;
        cout << "Enter the initial value of y: ";
        cin >> y0;
        cout << "Enter the initial value of z: ";
        cin >> z0;
        cout << "Enter step size h (positive): ";
        cin >> h;

        if (choice == 1) {
            cout << "\nEnter the value of x at which you want the value of y and z: ";
            cin >> x_final;
        } else if (choice == 2) {
            cout << "\nEnter the final value of x: ";
            cin >> x_final;
        } else {
            cout << "\nInvalid Choice!\n";
            return 0;
        }

        // ===== Number of steps using ceil() =====
        // ceil ensures that final x[n] >= x_final
        int n = int(ceil((x_final - x0)/h));

        // ===== Initialize vectors for x, y, z =====
        vector<double> x(n + 1), y(n + 1), z(n + 1);
        x[0] = x0;
        y[0] = y0;
        z[0] = z0;

        // ===== RK4 Iteration =====
        double k1, k2, k3, k4, l1, l2, l3, l4;
        for (int i = 0; i < n; i++) {
            k1 = h * f(x[i], y[i], z[i]);
            l1 = h * g(x[i], y[i], z[i]);

            k2 = h * f(x[i] + h/2, y[i] + k1/2, z[i] + l1/2);
            l2 = h * g(x[i] + h/2, y[i] + k1/2, z[i] + l1/2);

            k3 = h * f(x[i] + h/2, y[i] + k2/2, z[i] + l2/2);
            l3 = h * g(x[i] + h/2, y[i] + k2/2, z[i] + l2/2);

            k4 = h * f(x[i] + h, y[i] + k3, z[i] + l3);
            l4 = h * g(x[i] + h, y[i] + k3, z[i] + l3);

            y[i+1] = y[i] + (k1 + 2*k2 + 2*k3 + k4)/6;
            z[i+1] = z[i] + (l1 + 2*l2 + 2*l3 + l4)/6;
            x[i+1] = x[i] + h; // x values incremented by step size
        }

        // ===== Display results =====
        if (choice == 1) {
            cout << "\nAt x = " << x_final << ":\n";
            cout << "y = " << y[n] << ", z = " << z[n] << endl;
        } else if (choice == 2) {
            cout << left << setw(12) << "x" << setw(15) << "y" << setw(15) << "z" << endl;
            cout << string(42, '-') << endl;

            for (int i = 0; i <= n; i++) {
                cout << left << setw(12) << x[i] << setw(15) << y[i] << setw(15) << z[i] << endl;
            }

            // ===== Write CSV for Excel =====
            ofstream file("rk4_output.csv");
            file << "x,y,z\n";
            for (int i = 0; i <= n; i++) {
                file << x[i] << "," << y[i] << "," << z[i] << "\n";
            }
            file.close();
            cout << "\nData saved to rk4_output.csv\n";
        }

        // ===== Ask to continue =====
        cout << "\nDo you want to perform another calculation? (y/Y to continue): ";
        cin >> again;

    } while(tolower(again) == 'y'); // Repeat if user wants

    return 0;
}

