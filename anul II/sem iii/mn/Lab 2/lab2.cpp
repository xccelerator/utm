#include <iostream>
#include <math.h>
#include <conio.h>
using namespace std;

float deter(float a[10][10], int k);
int Allo(int lung);
int simetric(int lung);
void factor(int lung);
void trans(int lung);
void determinare(int lung);
void Cholesky(int lung);
void Iacobi(int lung, float Eps);
void Gauss_Seidel(int lung, float Eps);
int DiagDom(float a[10][10], int lung);
float l[10][10] = {0};
float a[10][10], b[10], c[10][10], d[10];
int lung;
int main()
{
    
    int lung, p, menu;
    cout << " 1. Metoda lui Cholesky\n";
    cout << " 2. Metoda Jacobi\n";
    cout << " 3. Metoda Gauss-Seidel\n";
    cout << " 0. Exit";
    cout << endl
         << endl
         << " >>> ";
    cin >> menu;
    switch (menu)
    {
    case 1:
        
        cout << "Numarul liniilor: ";
        cin >> lung;
        cout << "\nIntroduceti tabloul A\n";
        for (int i = 0; i < lung; i++)
            for (int j = 0; j < lung; j++)
            {
                cin >> a[i][j];
                c[i][j] = a[i][j];
            }
        cout << "\nTabloul b\n";
        for (int i = 0; i < lung; i++)
        {
            cin >> b[i];
            d[i] = b[i];
        }

        cout << endl
             << endl
             << " Rezultatele";

        cout << "\n Metoda Cholesky\n\n";
        Cholesky(lung);
        cout << endl
             << endl;
        
        main();
        exit(1);
        break;
    case 2:
        
        cout << "Numarul liniilor: ";
        cin >> lung;
        cout << "\nIntroduceti tabloul A\n";
        for (int i = 0; i < lung; i++)
            for (int j = 0; j < lung; j++)
            {
                cin >> a[i][j];
                c[i][j] = a[i][j];
            }
        cout << "\nTabloul b\n";
        for (int i = 0; i < lung; i++)
        {
            cin >> b[i];
            d[i] = b[i];
        }
        cout << "\n Metoda Jacobi (Eroarea = 0.001)\n";
        Iacobi(lung, 0.001);
        cout << endl;
        cout << "\n Metoda Jacobi (Eroarea = 0.00001)\n";
        Iacobi(lung, 0.00001);
        cout << endl;
        
        main();
        exit(1);
        break;
    case 3:
        
        cout << "Numarul liniilor: ";
        cin >> lung;
        cout << "\nIntroduceti tabloul A\n";
        for (int i = 0; i < lung; i++)
            for (int j = 0; j < lung; j++)
            {
                cin >> a[i][j];
                c[i][j] = a[i][j];
            }
        cout << "\nTabloul b\n";
        for (int i = 0; i < lung; i++)
        {
            cin >> b[i];
            d[i] = b[i];
        }

        cout << "\n Metoda Gauss-Seidel (Eroarea = 0.001)\n";
        Gauss_Seidel(lung, 0.001);
        cout << endl;
        
        main();
        exit(1);
        break;
    default:
        cout << "Optiune gresita!";
        break;
    case 0:
        return 0;
    }
}
void Cholesky(int lung)
{
    if (!Allo(lung))
    {
        cout << "\nAceasta matricea nu este pozitiv definita!\n";
         main();
        exit(1);
        goto E;
    }
    if (!simetric(lung))
    {
        cout << "\nAceasta matricea nu este simetrica !\n";
        
        main();
        exit(1);
    }
    determinare(lung);
E:;
}
//------------------------------------------
float deter(float a[10][10], int k)
{
    if (k == 1)
        return a[0][0];
    if (k == 2)
        return a[0][0] * a[1][1] - a[0][1] * a[1][0];
    float s = 0;
    float t[10][10] = {0};
    for (int i = 0; i < k; i++)
    {
        int x = 0;
        for (int l = 0; l < k; l++)
        {
            if (l != i)
            {
                for (int m = 1; m < k; m++)
                    t[x][m - 1] = a[l][m];
                x++;
            }
        }
        if (i % 2 == 0)
            s += a[i][0] * deter(t, k - 1);
        else
            s -= a[i][0] * deter(t, k - 1);
    }
    return s;
}
//------------------------------------------
int Allo(int lung)
{
    for (int i = 0; i < lung; i++)
        if (a[i][i] <= 0 || deter(a, i + 1) <= 0)
            return 0;
    return 1;
}
//------------------------------------------
int simetric(int lung)
{
    for (int i = 0; i < lung; i++)
        for (int j = 0; j < lung; j++)
            if (a[i][j] != a[j][i])
                return 0;
    return 1;
}
//------------------------------------------
void factor(int lung)
{
    l[0][0] = (float)sqrt(a[0][0]);
    for (int i = 0; i < lung; i++)
        l[i][0] = a[i][0] / l[0][0];
    for (int i = 1; i < lung; i++)
    {
        float t = 0;
        for (int j = 0; j < i; j++)
            t += l[i][j] * l[i][j];
        l[i][i] = (float)sqrt(a[i][i] - t);
        for (int j = i; j < lung; j++)
        {
            float t1 = 0;
            for (int k = 0; k < i; k++)
                t1 += l[j][k] * l[i][k];
            l[j][i] = (a[j][i] - t1) / l[i][i];
        }
    }
}
//------------------------------------------
void trans(int lung)
{
    float t = 0;
    for (int i = 0; i < lung; i++)
        for (int j = 0; j < i; j++)
        {
            t = l[i][j];
            l[i][j] = l[j][i];
            l[j][i] = t;
        }
}
//------------------------------------------
void determinare(int lung)
{
    factor(lung);
    float y[10], x[10];
    y[0] = b[0] / l[0][0];
    for (int i = 0; i < lung; i++)
    {
        float t = 0;
        for (int j = 0; j < i; j++)
            t += l[i][j] * y[j];
        y[i] = (b[i] - t) / l[i][i];
    }
    trans(lung);

    cout << "Matricea triughiular superioara:\n";
    for (int i = 0; i < lung; i++)
    {
        for (int j = 0; j < lung; j++)
        {
            cout << l[i][j] << "\t";
        }
        cout << endl;
    }
    x[lung - 1] = y[lung - 1] / l[lung - 1][lung - 1];
    float t;
    for (int i = lung - 2; i >= 0; i--)
    {
        t = 0;
        for (int j = i + 1; j < lung; j++)
            t += l[i][j] * x[j];
        x[i] = (y[i] - t) / l[i][i];
    }
    cout << "\nRezultatele x:\n";
    for (int i = 0; i < lung; i++)
        cout << " x" << i + 1 << " = " << x[i] << '\n';

    cout << "\nRezultatele y:\n";
    for (int i = 0; i < lung; i++)
        cout << " y" << i + 1 << " = " << y[i] << "\n";
}
//-------------------------------------
void Iacobi(int lung, float Eps)
{
    float x[10], x1[10], q[10][10] = {0}, d[10], t, max;
    int ni = 0;
    for (int i = 0; i < lung; i++)
        for (int j = 0; j < lung; j++)
            if (i != j)
                q[i][j] = -(a[i][j] / a[i][i]);
            else
                q[i][j] = 0;
    if (!DiagDom(a, lung))
    {
        cout << "Aceasta matricea nu este diagonal dominata\n";
        
        main();
        exit(1);
        goto E;
    }
    for (int i = 0; i < lung; i++)
        d[i] = b[i] / a[i][i];
    for (int i = 0; i < lung; i++)
        x[i] = d[i];
    do
    {
        for (int i = 0; i < lung; i++)
            x1[i] = x[i];
        for (int i = 0; i < lung; i++)
        {
            t = 0;
            for (int j = 0; j < lung; j++)
                t += q[i][j] * x1[j]; // Jakobi
            x[i] = t + d[i];
        }
        max = (float)fabs(x[0] - x1[0]);
        for (int i = 1; i < lung; i++)
            if ((float)fabs(x[i] - x1[i]) > max)
                max = (float)fabs(x[i] - x1[i]);
        ni++;
    } while (max > Eps);
    cout << "\nRezultatele x:\n";
    for (int i = 0; i < lung; i++)
        cout << "x" << i + 1 << " = " << x[i] << endl;
    cout << "\nNumarul iteratiilor = " << ni << endl;
E:;
}
//-------------------------------------
int DiagDom(float a[10][10], int lung)
{
    float s;
    for (int i = 0; i < lung; i++)
    {
        s = 0;
        for (int j = 0; j < lung; j++)
            if (i != j)
                s += a[i][j];
        if (a[i][i] < s)
            return 0;
        if (a[i][i] == 0)
            return 0;
    }
    return 1;
}
//-----------------------------
void Gauss_Seidel(int lung, float Eps)
{
    float x[10], x1[10], q[10][10] = {0}, d[10], t, max;
    int ni = 0;
    for (int i = 0; i < lung; i++)
        for (int j = 0; j < lung; j++)
            if (i != j)
                q[i][j] = -(a[i][j] / a[i][i]);
            else
                q[i][j] = 0;
    if (!DiagDom(a, lung))
    {
        cout << "Aceasta matricea nu este diagonal dominata\n";
        
        main();
        exit(1);
        goto E;
    }
    for (int i = 0; i < lung; i++)
        d[i] = b[i] / a[i][i];
    for (int i = 0; i < lung; i++)
        x[i] = d[i];
    do
    {
        for (int i = 0; i < lung; i++)
            x1[i] = x[i];
        for (int i = 0; i < lung; i++)
        {
            t = 0;
            for (int j = 0; j < lung; j++)
                t += q[i][j] * x[j]; // Gauss - Seidel
            x[i] = t + d[i];
        }
        max = (float)fabs(x[0] - x1[0]);
        for (int i = 1; i < lung; i++)
            if ((float)fabs(x[i] - x1[i]) > max)
                max = (float)fabs(x[i] - x1[i]);
        ni++;
    } while (max > Eps);
    cout << "\nRezultatele x:\n";
    for (int i = 0; i < lung; i++)
        cout << "x" << i + 1 << " = " << x[i] << endl;
    cout << "\nNumarul iteratiilor = " << ni << endl;
E:;
}
