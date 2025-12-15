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
 Gauss–Seidel Iterative Method

 Objective:
 ----------
 To solve a system of n linear equations using
 Gauss–Seidel method assuming diagonal dominance.

 Method:
 -------
 1. Check diagonal dominance
 2. Take initial guesses
 3. Apply Gauss–Seidel iteration
 4. Stop when required accuracy is achieved
*/

#include<bits/stdc++.h>
using namespace std;

int main()
{
	cout.precision(5);
	cout.setf(ios::fixed); // set output precision

	int n;
	cout<<"\nEnter the number of variables:\n";
	cin>>n;

	double a[n][n+1], x[n], oldx[n], eps;

	// Input augmented matrix (coefficients + RHS)
	cout<<"\nEnter the augmented matrix(row-wise):\n";
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n+1;j++)
		{
			cin>>a[i][j];
		}
	}

	/* ---------------- Check Diagonal Dominance ---------------- */
	for(int i=0;i<n;i++)
	{
		double sum = 0;
		for(int j=0;j<n;j++)
		{
			if(j != i) sum += fabs(a[i][j]); // sum of non-diagonal elements
		}
		if(fabs(a[i][i]) < sum) // diagonal element must be >= sum of others
		{
			cout << "\nThe system is NOT diagonally dominant.\n";
			cout << "Gauss-Seidel method may not converge.\n";
			cout << "Try again with a different system or by interchanging the positions of the equations.\n";
			return 0;
		}	
	}
	cout<<"\nThe system is diagonally dominant. Hence Gauss-Seidel method is applicable.\n";

	/* ---------------- Input Initial Guesses ---------------- */
	cout<<"\nEnter initial guess values:\n";
	for(int i=0;i<n;i++)
	{
		cout<<"x"<<i+1<<" = ";
		cin>>x[i];
	}

	/* ---------------- Input Tolerance ---------------- */
	cout<<"\nEnter the allowed error (tolerance): \n";
	cin>>eps;

	/* ---------------- Gauss-Seidel Iteration ---------------- */
	int iter = 0;
	while(true)
	{
		iter++;
		for(int i=0;i<n;i++)
			oldx[i] = x[i]; // store old values to check convergence

		for(int i=0;i<n;i++)
		{
			double sum = a[i][n]; // start with RHS
			for(int j=0;j<n;j++)
			{
				if(j != i)
					sum -= a[i][j]*x[j]; // subtract sum of other terms
			}
			x[i] = sum / a[i][i]; // update variable immediately (Gauss-Seidel)
		}

		// Display iteration results
		cout<<"\nIteration "<<iter<<": ";
		for(int i=0;i<n;i++)
			cout<<left<<"x"<<i+1<<" = "<<setw(15)<<x[i];
		cout<<endl;

		// Check if all variables satisfy tolerance
		bool stop = true;
		for(int i=0;i<n;i++)
		{
			if(fabs(x[i] - oldx[i]) > eps)
				stop = false;
		}
		if(stop) break; // if converged, exit loop
	}

	/* ---------------- Final Solution ---------------- */
	cout<<"\nFinal solution after "<<iter<<" iterations:\n";
	for(int i=0;i<n;i++)
	{
		cout<<"x"<<i+1<<" = "<<x[i]<<endl;
	}

	return 0;
}

