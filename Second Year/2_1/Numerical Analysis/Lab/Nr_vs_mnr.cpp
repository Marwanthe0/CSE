#include <bits/stdc++.h>
using namespace std;
double f(double x)
{
    return pow(x, 10) - 1;
}
double f_prime(double x)
{
    return 10 * pow(x, 9);
}
double f_double_prime(double x)
{
    return 90 * pow(x, 8);
}
void nr(double x0, double tol, int max_iter)
{
    double x = x0;
    int ite = 0;
    double errs = (double)(INT_MAX);
    while (ite < max_iter)
    {
        double fx = f(x);
        double dfx = f_prime(x);
        if (dfx == 0)
        {
            cout << "Derivative is zero. Stopped.\n";
            break;
        }
        double xn = x - fx / dfx;
        double err = abs(xn - x);
        errs = min(err, errs);
        if (err < tol)
            break;
        x = xn;
        ite++;
    }
    cout << "newton raphson method:\n";
    cout << "root: " << x << "\n";
    cout << "iterations: " << ite << "\n";
    if (errs != (double(INT_MAX)))
        cout << "final error: " << errs << endl;
    cout << endl;
}
void modified_nr(double x0, double tol, int max_iter)
{
    double x = x0;
    int ite = 0;
    double errs = (double)(INT_MAX);
    while (ite < max_iter)
    {
        double fx = f(x);
        double dfx = f_prime(x);
        double ddfx = f_double_prime(x);
        if (dfx == 0)
        {
            cout << "derivative is zero stopped.\n";
            break;
        }
        double xn = x - (fx * dfx) / (pow(dfx, 2) - fx * ddfx);
        double err = abs(xn - x);
        errs = min(err, errs);
        if (err < tol)
            break;
        x = xn;
        ite++;
    }
    cout << "modified newton raphson method:\n";
    cout << "root: " << x << "\n";
    cout << "iterations: " << ite << "\n";
    if (errs != INT_MAX)
        cout << "final err: " << errs << "\n";
    cout << endl;
}
int main()
{
    double x0 = 0.9;
    double tol = 1e-6;
    int max_iter = 1000;
    nr(x0, tol, max_iter);
    modified_nr(x0, tol, max_iter);
    return 0;
}
