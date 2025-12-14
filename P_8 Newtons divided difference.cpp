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
 Newton's Divided Difference Interpolation

 Objective:
 ----------
 To evaluate the value of a function at a given point using
 Newton's Divided Difference method. This method is applicable
 for unequally spaced data points.

 Additional Features:
 --------------------
 - Generation of divided difference table
 - Identification of interpolation or extrapolation point
 - Percentage error calculation (if exact value is known)
*/

#include<bits/stdc++.h>
using namespace std;

int main()
{
    /* Set fixed precision for numerical output */
    cout.precision(5);
    cout.setf(ios::fixed);

    int n;

    /* Input number of data points */
    cout<<"\nEnter the number of data points: ";
    cin>>n;

    /* Declare arrays for x values and divided difference table */
    double x[n], y[n][n];

    /* Input x values */
    cout<<"\nEnter the values of x:\n";
    for(int i=0; i<n; i++)
        cin>>x[i];

    /* Input corresponding y values */
    cout<<"\nEnter the values of y:\n";
    for(int i=0; i<n; i++)
        cin>>y[i][0];

    /* Construction of divided difference table */
    for(int j=1; j<n; j++)
    {
        for(int i=0; i<n-j; i++)
        {
            y[i][j] = (y[i+1][j-1] - y[i][j-1]) / (x[i+j] - x[i]);
        }
    }

    /* Display divided difference table */
    cout<<"\nThe divided difference table is as follows:\n";
    cout<<left<<setw(12)<<"x"<<setw(15)<<"y";
    for(int i=1; i<n; i++)
        cout<<setw(15)<<"d"+to_string(i)+"y";

    cout<<"\n"<<string(15*(n+1), '-')<<endl;

    for(int i=0; i<n; i++)
    {
        cout<<left<<setw(12)<<x[i];
        for(int j=0; j<n-i; j++)
        {
            cout<<left<<setw(15)<<y[i][j];
        }
        cout<<endl;
    }

    /* Loop for interpolation / extrapolation calculation */
    while(true)
    {
        double xn, sum = y[0][0], temp = 1;

        /* Input the point at which function value is required */
        cout<<"\nEnter the value of x at which y is to be calculated:\n";
        cin>>xn;

        /* Check whether the point is interpolation or extrapolation */
        if(xn >= x[0] && xn <= x[n-1])
            cout<<"\nThis is an INTERPOLATION point.\n";
        else
            cout<<"\nThis is an EXTRAPOLATION point.\n";

        /* Newton's divided difference interpolation formula */
        for(int j=1; j<n; j++)
        {
            temp = temp * (xn - x[j-1]);
            sum  = sum + temp * y[0][j];
        }

        /* Display calculated value */
        cout<<"\nThe value of y at x = "<<xn<<" is: "<<sum<<endl;

        /* Percentage error calculation (optional) */
        char exc;
        cout<<"\nDo you know the exact value of y at x = "<<xn<<" ? (y/n):\n";
        cin>>exc;

        if(tolower(exc)=='y')
        {
            double exact;
            cout<<"\nEnter the exact value:\n";
            cin>>exact;

            double pcerr = fabs((exact - sum) / exact) * 100;
            cout<<"\nPercentage error: "<<pcerr<<" %\n";
        }

        /* Option to continue calculation */
        int ck;
        cout<<"\nDo you want to calculate for another value of x?\n";
        cout<<"Press 1 for yes otherwise 0: ";
        cin>>ck;

        if(ck != 1)
            break;
    }

    return 0;
}

