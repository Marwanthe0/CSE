#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define M 1000000007
#define N 1000000
#define endl "\n"
#define all(v) v.begin(), v.end()
#define forn for (ll i = 0; i < n; i++)
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
ll dp[N];
ll fib(ll n)
{
    if (n <= 1)
        return dp[n] = n;
    else if (dp[n] != -1)
        return dp[n];
    else
        return dp[n] = fib(n - 1) + fib(n - 2);
}
ll fib2(ll n)
{
    dp[0] = 0;
    dp[1] = 1;
    for (ll i = 2; i <= n; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}
void marwan()
{
    ll n;
    cin >> n;
    memset(dp, -1, sizeof(dp));
    cout << fib2(n) << endl;
    // cout << endl;
}
int main()
{
    ios_base::sync_with_stdio(false);
    marwan();
    return 0;
}