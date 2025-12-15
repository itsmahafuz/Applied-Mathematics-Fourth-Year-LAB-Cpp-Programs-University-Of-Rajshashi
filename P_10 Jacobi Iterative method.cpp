/*
 Date      : December 15, 2025
 Name      : MD MAHAFUZUR RAHMAN
 Roll      : 2110428176
 Department: Applied Mathematics
 University: University of Rajshahi
 LinkedIn  : https://www.linkedin.com/in/itsmahafuz/
 GitHub    : https://github.com/itsmahafuz
*/

/*
 Program Title:
 --------------
 Solution of System of Linear Equations using
 Jacobi Iterative Method

 Objective:
 ----------
 To solve a system of n linear equations using
 Jacobi Iterative Method assuming diagonal dominance.

 Method:
 -------
 1. Check diagonal dominance
 2. Take initial guesses
 3. Apply Jacobi iteration
 4. Stop when desired accuracy is achieved
*/

#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;

int main()
{
    cout.precision(4);
    cout.setf(ios::fixed);

    int n;
    cout << "\nEnter number of variables: ";
    cin >> n;

    double a[n][n+1];   // Augmented matrix
    double x[n];        // Old values
    double x1[n];       // New values
    double eps;         // Tolerance

    /* Input augmented matrix */
    cout << "\nEnter augmented matrix (coefficients + RHS):\n";
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<=n;j++)
        {
            cin >> a[i][j];
        }
    }

    /* -------- Check Diagonal Dominance -------- */
    for(int i=0;i<n;i++)
    {
        double sum = 0;
        for(int j=0;j<n;j++)
        {
            if(i != j)
                sum += fabs(a[i][j]);
        }

        if(fabs(a[i][i]) < sum)
        {
            cout << "\nThe system is NOT diagonally dominant.\n";
            cout << "Jacobi method may not converge.\n";
		  cout << "Try again with a different system or by interchanging the positions of the equations.\n";
            return 0;
        }
    }

    cout << "\nThe system is diagonally dominant.\n";

    /* Input initial guess */
    cout << "\nEnter initial guess values:\n";
    for(int i=0;i<n;i++)
    {
        cout << "x" << i+1 << " = ";
        cin >> x[i];
    }

    /* Input tolerance */
    cout << "\nEnter allowed error (tolerance): ";
    cin >> eps;

    /* -------- Jacobi Iteration -------- */
    int iter = 0;
    while(true)
    {
        iter++;

        /* Compute new values using only OLD values */
        for(int i=0;i<n;i++)
        {
            double sum = a[i][n]; // RHS
            for(int j=0;j<n;j++)
            {
                if(j != i)
                    sum -= a[i][j] * x[j];
            }
            x1[i] = sum / a[i][i];
        }

        /* Display iteration result */
        cout << "Iteration " << iter << ": ";
        for(int i=0;i<n;i++)
            cout << "x" << i+1 << " = " << x1[i] << "  ";
        cout << endl;

        /* Check convergence */
        bool stop = true;
        for(int i=0;i<n;i++)
        {
            if(fabs(x1[i] - x[i]) > eps)
                stop = false;

            x[i] = x1[i]; // update old values
        }

        if(stop)
            break;
    }

    /* Final solution */
    cout << "\nFinal solution after " << iter << " iterations:\n";
    for(int i=0;i<n;i++)
    {
        cout << "x" << i+1 << " = " << x[i] << endl;
    }

    return 0;
}

