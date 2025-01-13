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
void marwan()
{
    ll n, k;
    cin >> n >> k;
    vector<ll> v(k), t, pf = {0};
    for (auto &vl : v)
        cin >> vl;
    sort(all(v));
    for (ll i = k - 1; i >= 0; i--)
    {
        t.push_back(n - v[i]);
    }
    for (auto vl : t)
        pf.push_back(pf.back() + vl);
    // for (auto &vl : v)
    //     cout << vl << " ";
    // cout << endl;
    // for (auto &vl : pf)
    //     cout << vl << " ";
    ll mx = INT_MIN, ans = 0;
    auto it = v.begin();
    for (ll i = 1; i <= n; i++)
    {
        v.pop_back(), ans++;
        it = upper_bound(it, v.end(), pf[i]);
        if (it == v.end())
        {
            break;
        }
    }
    // cout << endl;
    cout << ans << endl;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll t;
    cin >> t;
    while (t--)
    {
        marwan();
    }
    return 0;
}