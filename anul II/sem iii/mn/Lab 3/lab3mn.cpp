#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iomanip>
using namespace std;

int control_x(double x[7], int p)
{
    for(int i=0; i<p; i++)
        for(int j=0; j<p; j++)
            if(x[i] == x[j] && i != j)
                return 0;
    return 1;
}
void afisare(double x[],double y[],int n)
{
    cout << "\nValorile introduse sunt: \n\n";
    cout << "X";
    for(int i=0; i<n; i++)
        cout << "\t" << x[i]<<setprecision(6);
    cout << endl;
    cout << "Y";
    for(int i=0; i<n; i++)
        cout << "\t" << y[i]<<setprecision(6);
    cout << endl;
}
void Lagrange(int p, double x[7], double y[7], double a)
{
    int i, j, k;
    double C[7], B[7], A[7], r, y1;
    --p;

    C[0] = 1;
    for(i = 0; i<=p; i++)
    {
        C[i+1] = C[i];
        for(j = i; j>=1; j--)
            C[j] = C[j-1]-C[j]*x[i];
        C[0] = -C[0]*x[i];
    }

    for(i = 0; i<=p; i++)
            A[i] = 0;
    B[p] = C[p+1];

    for(i = 0; i <= p; i++)
    {
        r = 1;
        for(j = 0; j <= p; j++)
            if(i != j)
                r = r*(x[i]-x[j]);
        for(k = p-1; k >= 0; k--)
            B[k] = C[k+1]+x[i]*B[k+1];
        for(k = 0; k <= p; k++)
            A[k] = A[k] + y[i]*B[k]/r;
    }
    cout << "\n 1) Polinomul de interpolare Lagrance Ln este: \nLn(x) = " << A[p] << "X^" << p;
    i = p-1;
    for(k = p-1; k > 0; k--)
    {
        printf(" %+1.4fX^%d", A[k], i);
        if(k == p-4) printf("\n\t");
        i--;
    }
    printf(" %+1.4f", A[0]);

    y1 = A[p];
    for(i = 1; i<=p; i++)
        y1 = a*y1 + A[p-i];

    cout << "\n\n\n 2) Valoarea functiei f(x) in punctul x:" << a << " utilizind \n polinomul de interpolare Lagrange este: f(x) = " << setprecision(5)<<y1;
}


main()
{
    double x[7]={-1.104, -0.986, 0.465, 1.235, 2.476, 3.789, 4.987};
    double y[7]={4.13567, 2.29876, 0.01238, -2.4587, -1.1154, 0.56478, 2.17854};

    int n=7;
    double a;

    if(!control_x(x, n))
    {
        cout <<"Introduceti doar o valoare x";
        system("cls");
        main();
        exit(1);
    }

    cout << "Introduceti valoarea x: ";
    cin >> a;
    afisare(x,y,n);
    cout << "Punctul x1 = " << a;

    cout << "\n\n";
    Lagrange(n, x, y, a);
    cout<<"\n\nCazul m<n :";
    int m=n-3;
    double x1[m],y1[m];
    for(int i=0;i<m;i++)
    {
        x1[i]=x[i];
        y1[i]=y[i];
    }
    afisare(x1,y1,m);
    Lagrange(m,x1,y1,a);

}

