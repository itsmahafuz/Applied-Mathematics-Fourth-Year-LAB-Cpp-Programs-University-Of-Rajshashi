/*
 Date      : December 13, 2025
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
 Interpolation using Newton’s Backward Difference Formula

 Objective:
 ----------
 To compute the value of a function at a given point using
 Newton’s backward interpolation formula based on equally
 spaced tabulated data.

 Theory (Brief):
 ---------------
 Newton’s backward interpolation formula is used when the
 value to be interpolated lies near the end of the data table.
 The backward difference table is constructed and the formula

     y(x) = y_n + p?y_n + p(p+1)/2! ?²y_n + ...

 is applied, where
     p = (x - x_n) / h
     h = common difference between x values.
*/

#include<iostream>
#include<cmath>
#include<string>
#include<iomanip>
using namespace std;

int main()
{
    /* Set output format */
    cout.precision(6);
    cout.setf(ios::fixed);

    char choice;
    do
    {
        int n;

        /* Input number of data points */
        cout << "\nEnter the number of values to be entered:\n";
        cin >> n;

        /* Arrays to store x values and backward difference table */
        double x[n], y[n][n];

        /* Input x values */
        cout << "\nEnter the values of x:\n";
        for(int i = 0; i < n; i++)
        {
            cin >> x[i];
        }

        /* Input corresponding y values */
        cout << "\nEnter the values of y:\n";
        for(int i = 0; i < n; i++)
        {
            cin >> y[i][0];
        }

        /* Construction of backward difference table */
        for(int j = 1; j < n; j++)
        {
            for(int i = n - 1; i >= j; i--)
            {
                y[i][j] = y[i][j-1] - y[i-1][j-1];
            }
        }

        /* Display the backward difference table */
        cout << "\nThe backward difference table is as follows:\n\n";
        cout << left << setw(12) << "x" << setw(15) << "y";

        /* Print column headings for differences */
        for(int i = 1; i < n; i++)
        {
            cout << left << setw(15) << "d" + to_string(i) + "y";
        }

        cout << "\n" << string(15*(n+1), '-') << endl;

        /* Print the backward difference table values */
        for(int i = 0; i < n; i++)
        {
            cout << left << setw(12) << x[i];
            for(int j = 0; j <= i; j++)
            {
                cout << left << setw(15) << y[i][j];
            }
            cout << endl;
        }

        bool CA = true;
        while(CA)
        {
            double xn, h, p, sum = y[n-1][0], temp = 1;

            /* Step size (assuming equal spacing) */
            h = x[1] - x[0];

            /* Input the value at which interpolation is required */
            cout << "\nEnter the value of x at which y is to be calculated:\n";
            cin >> xn;

            /* Compute p for Newton’s backward formula */
            p = (xn - x[n-1]) / h;

            /* Apply Newton’s backward interpolation formula */
            for(int j = 1; j < n; j++)
            {
                temp = temp * (p + (j - 1)) / j;
                sum = sum + temp * y[n-1][j];
            }

            /* Display the interpolated value */
            cout << "\nThe value of y at x = " << xn << " is: " << sum << endl;

            /* Ask user to evaluate another x using same data */
            int subchoice;
            cout << "\nWould you like to calculate y for another value of x ? ";
            cout << "Press 1 for Yes or 0 for No: ";
            cin >> subchoice;

            CA = (subchoice == 1);
        }

        /* Option to restart program with new dataset */
        cout << "\nDo you want to restart the program with new data points? ";
        cout << "Press Y/y for Yes or any other key to exit:\n";
        cin >> choice;

    } while(tolower(choice) == 'y');

    return 0;
}


