/*
 Date      : December 16, 2025
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
 Numerical Integration using Simpson's 3/8 Rule

 Objective:
 ----------
 To evaluate a definite integral numerically using
 Simpson’s 3/8 rule for a given function f(x).

 Method:
 -------
 1. Divide the interval [a, b] into n subintervals (n must be a multiple of 3)
 2. Compute step size h = (b - a)/n
 3. Apply Simpson’s 3/8 formula
 4. Compute approximate value of the integral
 5. Calculate percentage error if exact value is known
*/

#include<bits/stdc++.h>
using namespace std;

/* Define the integrand function f(x) */
double f(double x)
{
	return 1/(1 + x*x);
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

		/* Input limits of integration */
		cout<<"\nEnter the lower and upper limit of the integral:\n";
		cin>>a>>b;
		
		/* Ensure n is a multiple of 3 */
		W:
		cout<<"\nEnter the number of divisions:\n";
		cin>>n;
		if(n%3 != 0)
		{
			cout<<"\nThe number of divisions must be a multiple of 3 for this method.\n";
			cout<<"\nTry again..\n";
			goto W;
		}
		
		/* Step size */
		double h = (b - a) / n;

		/* Arrays to store x and f(x) values */
		double x[n+1], y[n+1];

		for(int i=0;i<=n;i++)
		{
			x[i] = a + i*h;
			y[i] = f(x[i]);
		}

		/* Display table of values */
		cout<<"\nThe values of f(x) at each subdivision are:\n";
		cout<<left<<setw(12)<<"x"<<setw(15)<<"y"<<endl;
		cout<<string(30,'-')<<endl;
		for(int i=0;i<=n;i++)
		{
			cout<<left<<setw(12)<<x[i]<<setw(15)<<y[i]<<endl;
		}
		
		/* Simpson's 3/8 Rule Calculation */
		double sum = y[0] + y[n];
		for(int i=1;i<n;i++)
		{
			if(i%3 == 0)
				sum += 2*y[i];   // coefficient 2
			else
				sum += 3*y[i];   // coefficient 3
		}

		double result = (3*h*sum)/8;
		cout<<"\nThe value of the integral is: "<<result<<endl;
		
		/* Percentage Error (Optional) */
		char cc;
		double exact;
		cout<<"\nDo you know the exact value? (y/n): \n";
		cin>>cc;
		if(tolower(cc)=='y')
		{
			cout<<"\nEnter the exact value:\n";
			cin>>exact;
			
			double pcerr = fabs((exact - result)/exact)*100;
			cout<<"\nPercentage error is "<<pcerr<<" %\n";
		}
		
		/* Repeat program */
		cout<<"\nDo you want to run the program again? (y/n):\n";
		cin>>check;

	}while(tolower(check)=='y');
	
	return 0;
}

