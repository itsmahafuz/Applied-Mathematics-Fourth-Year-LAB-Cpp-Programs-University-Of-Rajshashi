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
 Numerical Integration using Trapezoidal Rule

 Objective:
 ----------
 To approximate the value of a definite integral
 using the Trapezoidal Rule.

 Method:
 -------
 1. Divide the interval [a, b] into n equal subintervals
 2. Evaluate f(x) at each point
 3. Apply the trapezoidal formula
 4. (Optional) Calculate percentage error if exact value is known
*/

#include<bits/stdc++.h>
using namespace std;

/* ---------------- Function Definition ---------------- */
// Function whose integral is to be evaluated
double f(double x)
{
	return x*x;   // f(x) = x^2
}

int main()
{
	cout.precision(5);
	cout.setf(ios::fixed); // set fixed decimal precision
	
	cout << "\nNumerical Integration by Trapezoidal Rule\n\n";
	
	char check;
	do
	{
		int n;
		double a, b;

		/* ---------------- Input Limits ---------------- */
		cout<<"\nEnter the lower and upper limits of the integral:\n";
		cin>>a>>b;

		/* ---------------- Input Number of Subdivisions ---------------- */
		cout<<"\nEnter the number of divisions:\n";
		cin>>n;

		/* ---------------- Step Size Calculation ---------------- */
		double h = (b - a) / n;  // width of each subinterval

		/* ---------------- Arrays for x and f(x) ---------------- */
		double x[n+1], y[n+1];

		// Compute x and f(x) values
		for(int i=0; i<n+1; i++)
		{
			x[i] = a + i * h;  // x values
			y[i] = f(x[i]);   // corresponding f(x) values
		}

		/* ---------------- Display Table ---------------- */
		cout<<"\nThe values of f(x) at each subdivision are:\n";
		cout<<left<<setw(12)<<"x"<<setw(15)<<"y"<<endl;
		cout<<string(40,'-')<<endl;

		for(int i=0; i<n+1; i++)
		{
			cout<<left<<setw(12)<<x[i]<<setw(15)<<y[i]<<endl;
		}

		/* ---------------- Trapezoidal Rule Formula ---------------- */
		double sum = y[0] + y[n]; // first and last terms

		for(int i=1; i<n; i++)
		{
			sum = sum + 2 * y[i];  // middle terms multiplied by 2
		}

		double result = (h / 2.0) * sum; // final integral value

		cout<<"\nThe value of the integral is: "<<result<<endl;

		/* ---------------- Percentage Error (Optional) ---------------- */
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

		/* ---------------- Repeat Program ---------------- */
		cout << "\nDo you want to run the program again? "
		     << "(Press 'Y' or 'y' to continue, or any other key to exit): ";
		cin >> check;

	} while(tolower(check) == 'y');

	return 0;
}

