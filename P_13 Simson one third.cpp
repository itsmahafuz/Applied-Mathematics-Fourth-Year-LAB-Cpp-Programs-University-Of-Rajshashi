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
 Numerical Integration using Simpson's 1/3 Rule

 Objective:
 ----------
 To evaluate a definite integral numerically using
 Simpson’s 1/3 Rule for a given function.

 Method:
 -------
 1. Divide the interval [a, b] into n equal subintervals
 2. Ensure n is even (requirement of Simpson’s 1/3 Rule)
 3. Apply Simpson’s 1/3 formula
 4. Compute percentage error if exact value is known
*/

#include<bits/stdc++.h>
using namespace std;

/* Function to be integrated */
double f(double x)
{
	return 1/(1+x);
}

int main()
{
	/* Set output precision */
	cout.precision(5);
	cout.setf(ios::fixed);
	
	char check;
	do
	{
		int n;
		double a,b;

		/* Input integration limits */
		cout<<"\nEnter the lower and upper limits of the integral:\n";
		cin>>a>>b;
		
		/* Input number of subintervals */
		W:
		cout<<"\nEnter the number of divisions:\n";
		cin>>n;

		/* Simpson's 1/3 rule requires even number of divisions */
		if(n%2 != 0)
		{
			cout<<"\nThe number of divisions must be even for this method.\n";
			cout<<"\nTry again...\n";
			goto W;
		}
		
		/* Step size */
		double h = (b-a)/n;

		/* Arrays to store x and f(x) values */
		double x[n+1],y[n+1];

		for(int i=0;i<=n;i++)
		{
			x[i] = a + i*h;
			y[i] = f(x[i]);
		}
		
		/* Display tabulated values */
		cout<<"\nThe values of f(x) at each subdivision are:\n";
		cout<<left<<setw(12)<<"x"<<setw(15)<<"y"<<endl;
		cout<<string(40,'-')<<endl;

		for(int i=0;i<=n;i++)
		{
			cout<<left<<setw(12)<<x[i]<<setw(15)<<y[i]<<endl;
		}
		
		/* -------- Simpson's 1/3 Rule Implementation -------- */
		double sum = y[0] + y[n];

		for(int i=1;i<n;i++)
		{
			if(i%2 == 0)
				sum += 2*y[i];
			else
				sum += 4*y[i];
		}

		double result = sum*(h/3);
		cout<<"\nThe value of the integral is: "<<result<<endl;

		/* -------- Percentage Error Calculation (Optional) -------- */
		double exact;
		char cc;

		cout<<"\nDo you know the exact value of the integral? (y/n):\n";
		cin>>cc;

		if(tolower(cc) == 'y')
		{
			cout<<"\nEnter the exact value:\n";
			cin>>exact;

			double pcerr = fabs((exact - result) / exact) * 100;
			cout<<"\nPercentage error: "<<pcerr<<" %\n";
		}

		/* Repeat program option */
		cout << "\nDo you want to run the program again? "
		     << "(Press 'Y' or 'y' to continue, or any other key to exit): ";
		cin >> check;

	}while(tolower(check)=='y');
}

