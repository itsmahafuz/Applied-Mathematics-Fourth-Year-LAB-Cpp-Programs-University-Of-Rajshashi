/*
 Date: June 28th, 2025
 MD MAHAFUZUR RAHMAN
 Roll: 2110428176
 Department of Applied Mathematics
 University Of Rajshahi
 LinkedIn: https://www.linkedin.com/in/itsmahafuz/
 GitHub: https://github.com/itsmahafuz
*/

/* Gaussian Elimination */

#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;
int main()
{
    cout.precision(3);
    cout.setf(ios::fixed);

    int n;
    cout<<"Enter the number of equations :\n";
    cin>>n;

    double a[n][n+1] ,x[n];
    cout<<"\nEnter the elements of the augmented matrix row-wise :\n";
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n+1;j++)
        {
            cin>>a[i][j];
        }
    }

    //pivotisation
    for(int i=0;i<n;i++)
    {
        for(int k=i+1;k<n;k++)
        {
            if(abs(a[i][i])<abs(a[k][i]))
            {
                for(int j=0;j<n+1;j++)
                {
                    double temp=a[i][j];
                    a[i][j]=a[k][j];
                    a[k][j]=temp;
                }
            }
        }
    }
    cout<<"\nThe augmented matrix after pivotisation is :\n";
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n+1;j++)
        {
            cout<<setw(7)<<a[i][j];
        }
        cout<<endl;
    }

    //Loop to perform the Gauss elimination
    for(int i=0;i<n;i++)
    {
        for(int k=i+1;k<n;k++)
        {
            double t=a[k][i]/a[i][i];
            for(int j=0;j<n+1;j++)
            {
                a[k][j]=a[k][j]-t*a[i][j];
            }
        }
    }
     cout<<"\nThe augmented matrix after Gaussian elimination is :\n";
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<setw(7)<<a[i][j];
        }
        cout<<endl;
    }

    //Back substitution
    for(int i=n-1;i>=0;i--)
    {
        if(a[i][i]==0)
        {
            cout<<"\nThe system is inconsistent.\n";
            return 0;
        }
        else 
        {
            x[i]=a[i][n];
            for(int j=i+1;j<n;j++)
            {
                x[i]=x[i]-a[i][j]*x[j];
            }
            x[i]=x[i]/a[i][i];
        }
    }
    cout<<"\nThe values of the variables are as follows :\n";
    for(int i=0;i<n;i++)
        cout<<"x"<<i+1<<" = "<<x[i]<<endl;
    
    return 0;
}