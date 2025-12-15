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
 ----------------
 Lagrange Interpolation and Extrapolation

 Objective:
 ------------
 To find the value of a function at a given point using
 Lagrange interpolation formula and to identify whether
 the point is interpolation or extrapolation.
 If the exact value is known, percentage error is also calculated.

 Theory (Brief):
 ----------------
 Lagrange interpolation formula is given by

     f(x) = S [ y_j * L_j(x) ]

 where,
     L_j(x) = ? (x - x_i) / (x_j - x_i),  i ? j

 This formula does not require equally spaced data points.
*/

#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;

int main()
{
	/* Set fixed precision for output */
	cout.precision(6);
	cout.setf(ios::fixed);
	
	int n;
	
	/* Input number of data points */
	cout<<"\nLagrange Interpolation / Extrapolation.\n";
	cout<<"\nEnter number of data points: ";
	cin>>n;
	
	double x[n],y[n];
	
	/* Input x values */
	cout<<"\nEnter values of x:\n";
	for(int i=0; i<n; i++)
		cin>>x[i];
	
	/* Input corresponding y values */
	cout<<"\nEnter corresponding values of y:\n";
	for(int i=0; i<n; i++)
		cin>>y[i];
	
	char choice;
	do
	{
		double xn;
		
		/* Input the point where function value is required */
		cout<<"\nEnter the value of x:\n";
		cin>>xn;
		
		/* Lagrange interpolation computation */
		double fx = 0;
		for(int j=0; j<n; j++)
		{
			double term = 1;
			for(int i=0; i<n; i++)
			{
				if(i != j)
				{
					term = term*((xn - x[i])/(x[j] - x[i]));
				}
			}
			fx = fx + term * y[j];
		}
		
		/* Display computed function value */
		cout<<"\nThe value of f("<<xn<< ") = "<<fx<<endl;
		
		/* Check whether the point is interpolation or extrapolation */
		if(xn >= x[0]  && xn <= x[n-1])
			cout<<"\nThis is an INTERPOLATION point.\n";
		else
			cout<<"\nThis is an EXTRAPOLATION point.\n";
		
		/* Percentage error calculation (if exact value is known) */
		char errchoice;
		cout<<"\nDo you know the exact value ? (y/n):\n";
		cin>>errchoice;
		
		if(tolower(errchoice)=='y')
		{
			double exact;
			cout<<"\nEnter exact value: ";
			cin>>exact;
			
			/* Formula for percentage error */
			double error = fabs((exact - fx)/exact) * 100;
			cout<<"\nPercentage Error = "<<error<<" %\n";
		}
		
		/* Option to evaluate for another x value */
		cout<<"\nDo you want to calculate for another x? (y/n): ";
		cin>>choice;
		
	}while(tolower(choice) == 'y');
	
	return 0;
}

