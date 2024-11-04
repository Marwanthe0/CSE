#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define M 1000000007
#define N 1000000
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
double f(double a)
{
    return ((a * a * a) - (a * a) + 2);
}
double False_Postition(double a, double b, double tolerance)
{
    double c;

    if (f(a) * f(b) > 0)
    {
        cout << "No root found in this Range" << endl;
        return NAN;
    }
    int cnt = 0;
    while (true)
    {
        c = (a * f(b) - b * f(a)) / (f(b) - f(a));

        if (fabs(f(c)) < tolerance)
        {
            cout << "Root is: " << c << "   Using: " << cnt << " Steps.\n";
            return c;
        }

        if (f(a) * f(c) < 0)
        {
            b = c;
        }
        else
        {
            a = c;
        }

        if (fabs(b - a) < tolerance)
        {
            cout << "Root is: " << c << "   Using: " << cnt << " Steps.\n";
            return c;
        }
        cnt++;
    }
}
void marwan()
{
    double a, b;
    cin >> a >> b;
    double tolerance = 0.00001;
    False_Postition(a, b, tolerance);
}
int main()
{
    ios_base::sync_with_stdio(false);
    marwan();
    return 0;
}