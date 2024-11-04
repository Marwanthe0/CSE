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
void bisection(double a, double b, double tolerance)
{
    if (f(a) * f(b) > 0)
    {
        cout << "No Root Found in this Range.\n";
        return;
    }
    double c = a;
    int count = 0;
    while (abs(a - b) > tolerance)
    {
        c = (a + b) / 2;
        if (f(c) == 0.00)
        {
            break;
        }
        if ((f(c) * f(a)) > 0)
        {
            a = c;
        }
        else
            b = c;
        count++;
    }
    cout << "Root is: " << c << "   Using: " << count << " Steps.\n"
         << endl;
}
void marwan()
{
    double a, b;
    cin >> a >> b;
    double tolerance = 0.01;
    bisection(a, b, tolerance);
}
int main()
{
    ios_base::sync_with_stdio(false);
    marwan();
    return 0;
}