/*
 Date: May 15th, 2025
 MD MAHAFUZUR RAHMAN
 Roll: 2110428176
 Department of Applied Mathematics
 University Of Rajshahi
 LinkedIn:https://www.linkedin.com/in/itsmahafuz/
 GitHub: https://github.com/itsmahafuz
*/

/*
Program to solve a system of nonlinear equations (two variables only)
 using the Newton-Raphson method.
*/

#include <iostream>
#include <cmath>
using namespace std;

// Function f(x, y) represents the first nonlinear equation
double f(double x, double y) {
    return x * x + y * y - 1; // Circle equation: x^2 + y^2 = 1
}

// Function g(x, y) represents the second nonlinear equation
double g(double x, double y) {
    return y - x * x; // Parabola equation: y = x^2
}

// Partial derivative of f(x, y) with respect to x
double fx(double x, double y) {
    return 2 * x;
}

// Partial derivative of f(x, y) with respect to y
double fy(double x, double y) {
    return 2 * y;
}

// Partial derivative of g(x, y) with respect to x
double gx(double x, double y) {
    return -2 * x;
}

// Partial derivative of g(x, y) with respect to y
double gy(double x, double y) {
    return 1.0;
}

/*
This function implements the Newton-Raphson method to find the roots of
two nonlinear equations f(x, y) = 0 and g(x, y) = 0. 
Parameters:
- x0, y0: Initial approximations for x and y.
- tol: The tolerance level to determine convergence.
*/
void newtonRaphson(double x0, double y0, double tol) {
    double x = x0, y = y0; // Initialize x and y with the initial guesses
    double h, k, d;        // h and k represent corrections for x and y
    int iteration = 0;     // Counter for the number of iterations

    while (true) {
        // Compute the determinant of the Jacobian matrix
        d = fx(x, y) * gy(x, y) - fy(x, y) * gx(x, y);

        // If the determinant is too small, convergence is not possible
        if (fabs(d) < 1e-9) {
            cout << "Jacobian determinant is too small. The system doesn't converge for this initial guess.\n";
            return;
        }

        // Compute corrections h and k for x and y
        h = (-f(x, y) * gy(x, y) + g(x, y) * fy(x, y)) / d;
        k = (-fx(x, y) * g(x, y) + f(x, y) * gx(x, y)) / d;

        // Update x and y using the computed corrections
        x += h;
        y += k;

        iteration++; // Increment the iteration count

        // Check if the current solution is within the tolerance
        if (fabs(f(x, y)) < tol && fabs(g(x, y)) < tol) {
            break; // Convergence achieved, exit the loop
        }

        // Optional safeguard to prevent infinite loops
        if (iteration > 100) {
            cout << "Exceeded maximum iterations. The system may not converge.\n";
            return;
        }
    }

    // Display the final result
    cout << "\nRoot of the equations: x = " << x << ", y = " << y << endl;
    cout << "Number of iterations: " << iteration << endl;
}

int main() {
    // Set output precision for displaying results
    cout.precision(6);
    cout.setf(ios::fixed);

    double x0, y0, tol; // Variables for initial guesses and tolerance
    char check;         // Variable to allow the user to run the program multiple times

    do {
        // Prompt the user for initial guesses and tolerance
        cout << "Enter the initial approximation of x and y:\n";
        cin >> x0 >> y0;

        cout << "Enter the tolerance:\n";
        cin >> tol;

        // Call the Newton-Raphson function to find the roots
        newtonRaphson(x0, y0, tol);

        // Ask the user if they want to run the program again
        cout << "\nIf you want to run the program again, press y/Y. Otherwise, press n/N:\n";
        cin >> check;

    } while (tolower(check) == 'y'); // Repeat if the user inputs 'y' or 'Y'

    return 0; // Exit the program
}
