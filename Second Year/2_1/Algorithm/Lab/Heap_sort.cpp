#include <bits/stdc++.h>
using namespace std;
#define int long long
#define M 1000000007
#define N 1000000
#define endl "\n"
#define all(v) v.begin(), v.end()
#define forn for (int i = 0; i < n; i++)
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
void heapify(vector<int> &v, int n, int i)
{
    int mx = i;
    int l = (2 * i) + 1, r = (2 * i) + 2;
    if (l < n && v[l] > v[mx])
    {
        mx = l;
    }
    if (r < n && v[r] > v[mx])
        mx = r;
    if (mx != i)
    {
        swap(v[mx], v[i]);
        heapify(v, n, mx);
    }
}
void marwan()
{
    int n;
    cin >> n;
    vector<int> v(n);
    for (auto &vl : v)
        cin >> vl;
    for (int i = (n / 2) - 1; i >= 0; i--)
    {
        heapify(v, n, i);
    }
    for (auto vl : v)
        cout << vl << " ";
    cout << endl;
    for (int i = n - 1; i > 0; --i)
    {
        swap(v[0], v[i]);
        heapify(v, i, 0);
        // for (int j = 0; j < i; j++)
        //     cout << v[j] << " ";
        // cout<<
        for (int j = i; j < n; j++)
            cout << v[j] << " ";
        cout << endl;
    }
    cout << "Final Array\n";
    for (auto &vl : v)
        cout << vl << " ";
    cout << endl;
}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    marwan();
    return 0;
}