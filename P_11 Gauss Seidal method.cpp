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
 1. Read augmented matrix
 2. Apply pivotisation (row interchange)
 3. Check diagonal dominance
 4. Take initial guess values
 5. Apply Gauss–Seidel iteration
 6. Stop when required accuracy is achieved
*/

#include<bits/stdc++.h>
using namespace std;

int main()
{
    /* Set output precision */
	cout.precision(5);
	cout.setf(ios::fixed);

	/* Number of variables */
	int n;
	cout<<"\nEnter the number of variables:\n";
	cin>>n;

	/* Augmented matrix, solution array and tolerance */
	double a[n][n+1], x[n], oldx[n], eps;

	/* ---------------- Input Augmented Matrix ---------------- */
	cout<<"\nEnter the augmented matrix (row-wise):\n";
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n+1;j++)
		{
			cin>>a[i][j];
		}
	}

	/* ---------------- Pivotisation ---------------- */
	/* Row interchange to improve diagonal dominance */
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

	/* ---------------- Check Diagonal Dominance ---------------- */
	for(int i=0;i<n;i++)
	{
		double sum = 0;
		for(int j=0;j<n;j++)
		{
			if(j != i)
				sum += fabs(a[i][j]);   // sum of non-diagonal elements
		}

		/* If diagonal element is smaller, method may diverge */
		if(fabs(a[i][i]) < sum)
		{
			cout << "\nThe system is NOT diagonally dominant.\n";
			cout << "Gauss-Seidel method may not converge.\n";
			cout << "Try again with a different system or by interchanging the equations.\n";
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

	/* ---------------- Initial Guess ---------------- */
	cout<<"\nEnter initial guess values:\n";
	for(int i=0;i<n;i++)
	{
		cout<<"x"<<i+1<<" = ";
		cin>>x[i];
	}

	/* ---------------- Input Tolerance ---------------- */
	cout<<"\nEnter the allowed error (tolerance): \n";
	cin>>eps;

	/* ---------------- Gauss–Seidel Iteration ---------------- */
	int iter = 0;
	while(true)
	{
		iter++;

		/* Store old values for convergence check */
		for(int i=0;i<n;i++)
			oldx[i] = x[i];

		/* Update values using Gauss–Seidel formula */
		for(int i=0;i<n;i++)
		{
			double sum = a[i][n];   // RHS
			for(int j=0;j<n;j++)
			{
				if(j != i)
					sum -= a[i][j] * x[j];
			}
			x[i] = sum / a[i][i];  // immediate update
		}

		/* Display iteration result */
		cout<<"\nIteration "<<iter<<": ";
		for(int i=0;i<n;i++)
			cout<<"x"<<i+1<<" = "<<setw(15)<<x[i];
		cout<<endl;

		/* Convergence check */
		bool stop = true;
		for(int i=0;i<n;i++)
		{
			if(fabs(x[i] - oldx[i]) > eps)
				stop = false;
		}

		if(stop) break;  // stop if converged
	}

	/* ---------------- Final Result ---------------- */
	cout<<"\nFinal solution after "<<iter<<" iterations:\n";
	for(int i=0;i<n;i++)
	{
		cout<<"x"<<i+1<<" = "<<x[i]<<endl;
	}

	return 0;
}
