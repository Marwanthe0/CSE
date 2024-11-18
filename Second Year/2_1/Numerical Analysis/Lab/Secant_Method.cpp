#include <bits/stdc++.h>
using namespace std;
double f(double x)
{
    return pow(x, 10) - 1;
}
void secant(double x1, double x2, double tol, int max_ite)
{
    int ite = 0;
    double err = (double)(INT_MAX);
    while (ite < max_ite)
    {
        double fx1 = f(x1);
        double fx2 = f(x2);
        double x3 = x2 - fx2 * (x2 - x1) / (fx2 - fx1);
        err = abs(x3 - x2);
        if (err < tol)
        {
            x2 = x3;
            break;
        }
        x1 = x2;
        x2 = x3;
        ite++;
    }
    cout << "root: " << setprecision(10) << x2 << "\n";
    cout << "iteations: " << ite << "\n";
    cout << "final error: " << setprecision(10) << err << "\n\n";
}
int main()
{
    double x1 = 1.5;
    double x2 = 1.4;
    double tol = 1e-6;
    int max_ite = 1000;
    secant(x1, x2, tol, max_ite);
    return 0;
}
