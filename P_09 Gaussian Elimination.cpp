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
 Gaussian Elimination Method with Partial Pivoting

 Objective:
 ----------
 To solve a system of n linear equations in n unknowns
 using Gaussian Elimination technique and allow the user
 to repeat the process for different systems.

 Method Used:
 ------------
 1. Partial Pivoting (to reduce numerical error)
 2. Forward Elimination
 3. Back Substitution
*/

#include<bits/stdc++.h>
using namespace std;

int main()
{
    /* Set output format to fixed with 5 decimal places */
    cout.precision(5);
    cout.setf(ios::fixed);

    char choice;   // Variable to control repetition of the program

    /* ----------- Repeat program using do-while loop ----------- */
    do
    {
        int n;

        /* Input number of equations */
        cout<<"\nEnter the number of equations: \n";
        cin>>n;

        /* Declare augmented matrix and solution vector */
        double a[n][n+1], x[n];

        /* Input augmented matrix row-wise */
        cout<<"\nEnter the elements of the augmented matrix (row-wise):\n";
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n+1;j++)
            {
                cin>>a[i][j];
            }
        }

        /* ---------------- Partial Pivoting ---------------- */
        /* Rearrange rows so that the largest pivot element
           appears on the diagonal position */
        for(int i=0;i<n;i++)
        {
            for(int k=i+1;k<n;k++)
            {
                if(fabs(a[i][i]) < fabs(a[k][i]))
                {
                    for(int j=0;j<n+1;j++)
                    {
                        double temp = a[i][j];
                        a[i][j] = a[k][j];
                        a[k][j] = temp;
                    }
                }
            }
        }

        /* Display augmented matrix after pivotisation */
        cout<<"\nThe augmented matrix after pivotisation is:\n";
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n+1;j++)
            {
                cout<<setw(10)<<a[i][j];
            }
            cout<<"\n";
        }

        /* ---------------- Gaussian Elimination ---------------- */
        /* Convert the augmented matrix into upper triangular form */
        for(int i=0;i<n;i++)
        {
            for(int k=i+1;k<n;k++)
            {
                double t = a[k][i]/a[i][i];
                for(int j=0;j<n+1;j++)
                {
                    a[k][j] = a[k][j] - t*a[i][j];
                }
            }
        }

        /* Display matrix after forward elimination */
        cout<<"\nThe augmented matrix after Gaussian Elimination is:\n";
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n+1;j++)
            {
                cout<<setw(10)<<a[i][j];
            }
            cout<<"\n";
        }

        /* ---------------- Back Substitution ---------------- */
        /* Compute the solution starting from the last equation */
        for(int i=n-1;i>=0;i--)
        {
            /* Check for zero pivot (system has no unique solution) */
            if(fabs(a[i][i]) == 0)
            {
                cout<<"\nThe system is inconsistent.\n";
                return 0;
            }
            else
            {
                x[i] = a[i][n];
                for(int j = i+1;j<n;j++)
                {
                    x[i] = x[i] - a[i][j]*x[j];
                }
                x[i] = x[i]/a[i][i];
            }
        }

        /* Display the computed solution */
        cout<<"\nThe values of the variables are as follows:\n";
        for(int i =0;i<n;i++)
        {
            cout<<"x"<<i+1<<" = "<<x[i]<<endl;
        }

        /* Ask user whether to repeat the program */
        cout<<"\nDo you want to run the program again? (y/n):\n";
        cin>>choice;

    } while(tolower(choice) == 'y');   // Repeat if user enters 'y'

    return 0;
}

