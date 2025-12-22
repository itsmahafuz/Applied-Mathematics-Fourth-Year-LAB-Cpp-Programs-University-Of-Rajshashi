#include<bits/stdc++.h>
using namespace std;

int main()
{
	cout<<fixed<<setprecision(5);
	
	int N;//number of data points
	cout<<"\nEnter the number of data points: ";
	cin>>N;

	vector<double>x(N),y(N);
	cout<<"\nEnter the x values:\n ";
	for(int i=0;i<N;i++)
	{
		cin>>x[i];
	}
	
	cout<<"\nEnter the y values:\n ";
	for(int i=0;i<N;i++)
	{
		cin>>y[i];
	}
	int degree;
	cout<<"\nEnter the degree of polynomial to fit: ";
	cin>>degree;
	
	int n =degree+1; //number of co-efficients
	vector<double> a(n), C(n),X(2*degree +1,0.0);
	 //a(n)->Coefficient matrix | C(n)->RHS vector of normal equations | X(2*degree +1) ->stores sum of powers
	vector<vector<double>>B(n,vector<double>(n+1, 0.0));
	//X[i] = {x^i
	for(int i=0;i<2*n-1;i++)
	{
		for(int j=0;j<N;j++)
		{
			X[i] = X[i] + pow(x[j],i);
		}
	}
	
	//Normal matrix
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			B[i][j] = X[i+j];
		}
	}
	
	//RHS vector
	for(int i=0;i<n;i++)
	{
		C[i] = 0.0;
		for(int k=0;k<N;k++)
		{
			C[i] = C[i] + pow(x[k], i)*y[k];
		}
		
		//Store RHS in augmented matrix
		B[i][n] = C[i];
	}
	
	//pivotisation
	for(int i=0;i<n;i++)
	{
		for(int k=i+1;k<n;k++)
		{
			if(fabs(B[i][i])< fabs(B[k][i]))
			{
				for(int j=0;j<n+1;j++)
				{
					swap(B[i][j],B[k][j]);
				}
			}
		}
	}
	//Gaussian elimination
	for(int i=0;i<n;i++)
	{
		for(int k=i+1;k<n;k++)
		{
			double t =B[k][i]/B[i][i];
			for(int j=0;j<n+1;j++)
			{
				B[k][j] -= t*B[i][j];
			}
		}
	}
	
	//Backsubstitution
	for(int i =n-1;i>=0;i--)
	{
		a[i] = B[i][n];
		for(int j=i+1;j<n;j++)
		{
			a[i] = a[i] - B[i][j]*a[j]; 
		}
		a[i] = a[i]/B[i][i];
	}
	cout<<"\nCo-efficients:\n";
	for(int i=0;i<n;i++)
	{
		cout<<"a"<<i<<" = "<<a[i]<<endl;
	}
	
	cout<<"\nFitted polynonial y = ";
	for(int i=0;i<n;i++)
	{
		cout<<"("<<a[i]<<")x^"<<i<<(i<n-1? "+" : "");
	}
	cout<<"\n";
	
}
