#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define M 1000000007
#define N 1000000kkk

double f(double x)
{
    return (x * x * x * x * x * x) - (x * x * x) - 1;
}

double g(double x)
{
    return pow((x * x * x) + 1, 1.0 / 6);
}

double f_prime(double x)
{
    return 6 * (x * x * x * x * x) - 3 * (x * x);
}

pair<double, double> Bracket(double a, double b, double tol, double iteration)
{
    if (f(a) * f(b) > 0)
    {
        printf("No Root Found in this interval Using Bracketing Method.\n");
        return {NAN, NAN};
    }
    double c = a, count = 0;
    while (abs(a - b) > tol)
    {
        c = (a + b) / 2;
        if (f(c) == 0.0)
        {
            return {c, count};
        }
        if (f(c) * f(a) > 0)
        {
            a = c;
        }
        else
        {
            b = c;
        }
        count++;
        if (count > iteration)
            break;
    }
    return {c, count};
}

pair<double, double> False_Position(double a, double b, double tol, double ite)
{
    if (f(a) * f(b) > 0)
    {
        printf("No Root Found in this interval Using False Position Method.\n");
        return {NAN, NAN};
    }
    double c = a, count = 0;
    while (abs(a - b) > tol)
    {
        c = (a * f(b) - b * f(a)) / (f(b) - f(a));
        if (f(c) == 0.0)
        {
            return {c, count};
        }
        if (f(c) * f(a) > 0)
        {
            a = c;
        }
        else
        {
            b = c;
        }
        count++;
        if (count > ite)
            break;
    }
    return {c, count};
}
pair<double, double> fixed_point(double a, double tolerance, int maxite)
{
    int count = 0;
    while (count < maxite)
    {
        double c = g(a);
        count++;
        if (fabs(c - a) < tolerance)
        {
            return {c, count};
        }
        a = c;
    }
    return {a, count};
}
pair<double, double> newton_raphson(double a, double tolerance, int maxIte)
{
    int iteration = 0;
    while (iteration < maxIte)
    {
        if (fabs(f(a)) < tolerance)
        {
            cout << "Derivative is too small for Newton Raphson Method." << endl;
            break;
        }
        double c = a - (f(a) / f_prime(a));
        iteration++;
        if (fabs(c - a) < tolerance)
        {
            return {c, iteration};
        }
        a = c;
    }
    return make_pair(a, iteration);
}

int main()
{
    ios_base::sync_with_stdio(false);
    double a, b, tolerance = 0.0001, ite = 10000;
    cin >> a >> b;

    pair<double, double> br, rf, fp, nr;
    br = Bracket(a, b, tolerance, ite);
    rf = False_Position(a, b, tolerance, ite);
    fp = fixed_point(a, tolerance, ite);
    nr = newton_raphson(a, tolerance, ite);

    auto calculate_error = [](double root) -> double
    {
        return fabs((f(root) / root) * 100);
    };
    printf("Using Bracketing Method:\n");
    cout << " Root = " << br.first << " \nSteps = " << br.second << " \nAnd error = " << calculate_error(br.first) << "%\n"
         << endl;

    printf("Using Regular Falsi Method:\n");
    cout << " Root = " << rf.first << " \nSteps = " << rf.second << " \nAnd error = " << calculate_error(rf.first) << "%\n"
         << endl;

    printf("Using Fixed point Method:\n");
    cout << " Root = " << fp.first << " \nSteps = " << fp.second << " \nAnd error = " << calculate_error(fp.first) << "%\n"
         << endl;

    printf("Using Newton Raphson Method:\n");
    cout << " Root = " << nr.first << " \nSteps = " << nr.second << " \nAnd error = " << calculate_error(nr.first) << "%\n"
         << endl;

    return 0;
}
