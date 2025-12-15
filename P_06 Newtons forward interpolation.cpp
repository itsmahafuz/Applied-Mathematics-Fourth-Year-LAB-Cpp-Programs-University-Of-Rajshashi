/*
 Date      : December 14, 2025
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
 Interpolation using Newton’s Forward Difference Formula

 Objective:
 ----------
 To compute the value of a function at a given point using
 Newton’s Forward interpolation formula based on equally
 spaced tabulated data.

 Theory (Brief):
 ---------------
 Newton’s Forward interpolation formula is used when the
 value to be interpolated lies near the start of the data table.
 The Forward difference table is constructed and the formula

     y(x) = y_0 + p*dy_0 + p(p-1)/2! * d²y_0 + ...

 is applied, where
     p = (x - x_0) / h
     h = common difference between x values.
*/
#include<iostream>
#include<cmath>
#include<string>
#include<iomanip>
using namespace std;

int main()
{
    /* Set output precision and fixed-point notation */
    cout.precision(6);
    cout.setf(ios::fixed);

    char choice;
    do
    {
        int n;

        /* Input number of tabulated data points */
        cout << "\nEnter the number of values to be entered:\n";
        cin >> n;

        /* Arrays to store x values and forward difference table */
        double x[n], y[n][n];

        /* Input x values */
        cout << "\nEnter the values of x:\n";
        for(int i = 0; i < n; i++)
            cin >> x[i];

        /* Input corresponding y values */
        cout << "\nEnter the values of y:\n";
        for(int i = 0; i < n; i++)
            cin >> y[i][0];

        /* Construction of forward difference table */
        for(int j = 1; j < n; j++)
        {
            for(int i = 0; i < n - j; i++)
            {
                y[i][j] = y[i+1][j-1] - y[i][j-1];
            }
        }

        /* Display the forward difference table */
        cout << "\nThe forward difference table is as follows:\n";
        cout << left << setw(12) << "x"
             << setw(15) << "y";

        /* Print column headings for forward differences */
        for(int i = 1; i < n; i++)
        {
            cout << left << setw(15) << "d" + to_string(i) + "y";
        }

        /* Print separator line */
        cout << "\n" << string(15*(n+1), '-') << endl;

        /* Print the forward difference table values */
        for(int i = 0; i < n; i++)
        {
            cout << left << setw(12) << x[i];
            for(int j = 0; j < n - i; j++)
            {
                cout << left << setw(15) << y[i][j];
            }
            cout << "\n";
        }

        bool CA = true;
        while(CA)
        {
            double p, h, xn, sum = y[0][0], temp = 1;

            /* Step size assuming equal interval */
            h = x[1] - x[0];

            /* Input the value of x for interpolation */
            cout << "\nEnter the value at which y is to be calculated:\n";
            cin >> xn;

            /* Compute p for Newton’s forward formula */
            p = (xn - x[0]) / h;

            /* Apply Newton’s Forward interpolation formula */
            for(int j = 1; j < n; j++)
            {
                temp = temp * (p - j + 1) / j;
                sum = sum + temp * y[0][j];
            }

            /* Display interpolated value */
            cout << "\nThe value of y at x = " << xn << " is  : " << sum << endl;

            /* Option to calculate y for another x using same data */
            int subchoice;
            cout << "\nWould you like to calculate the value of y for another value of x?\n";
            cout << "\nPress 1 for yes otherwise press 0 : ";
            cin >> subchoice;

            if(subchoice != 1)
                CA = false;
        }

        /* Option to restart program with new dataset */
        cout << "\nDo you want to restart the program with new data points? ";
        cout << "Press Y/y for Yes or any other key to exit:\n";
        cin >> choice;

    } while(tolower(choice) == 'y');

    return 0;
}

