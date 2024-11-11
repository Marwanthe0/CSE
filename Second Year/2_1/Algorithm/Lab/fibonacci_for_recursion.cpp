#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define M 1000000007
#define N 1000000
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
ll fib(int n)
{
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}
void marwan()
{
    int n;
    cin >> n;
    cout << fib(n);
}
int main()
{
    ios_base::sync_with_stdio(false);
    marwan();
    return 0;
}