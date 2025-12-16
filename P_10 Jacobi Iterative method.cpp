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
 1. Read augmented matrix
 2. Apply pivotisation to improve diagonal dominance
 3. Check diagonal dominance condition
 4. Take initial guess values
 5. Apply Jacobi iteration using old values
 6. Stop when desired accuracy is achieved
*/

#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;

int main()
{
    /* Set output precision */
    cout.precision(4);
    cout.setf(ios::fixed);

    int n;
    cout << "\nEnter number of variables: ";
    cin >> n;

    /* Declaration of variables */
    double a[n][n+1];   // Augmented matrix
    double x[n];        // Old iteration values
    double x1[n];       // New iteration values
    double eps;         // Tolerance

    /* -------- Input Augmented Matrix -------- */
    cout << "\nEnter augmented matrix (coefficients + RHS):\n";
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<=n;j++)
        {
            cin >> a[i][j];
        }
    }

    /* -------- Pivotisation (Row Interchange) -------- */
    /* Helps to improve diagonal dominance */
    for(int i=0;i<n;i++)
    {
        for(int k=i+1;k<n;k++)
        {
            if(fabs(a[i][i]) < fabs(a[k][i]))
            {
                for(int j=0;j<=n;j++)
                {
                    double t = a[i][j];
                    a[i][j] = a[k][j];
                    a[k][j] = t;
                }
            }
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
            return 0;
        }
    }

    /* Display diagonally dominant system */
    cout << "\nThe diagonally dominant system is:\n";
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<=n;j++)
            cout << setw(15) << a[i][j];
        cout << endl;
    }

    /* -------- Input Initial Guess -------- */
    cout << "\nEnter initial guess values:\n";
    for(int i=0;i<n;i++)
    {
        cout << "x" << i+1 << " = ";
        cin >> x[i];
    }

    /* Input tolerance */
    cout << "\nEnter allowed error (tolerance): ";
    cin >> eps;

    /* -------- Jacobi Iteration Process -------- */
    int iter = 0;
    while(true)
    {
        iter++;

        /* Compute new values using ONLY old values */
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

        /* Display current iteration */
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

            x[i] = x1[i]; // Update old values
        }

        if(stop)
            break;
    }

    /* -------- Final Solution -------- */
    cout << "\nFinal solution after " << iter << " iterations:\n";
    for(int i=0;i<n;i++)
    {
        cout << "x" << i+1 << " = " << x[i] << endl;
    }

    return 0;
}
