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
int dis[N], par[N];
class ed
{
public:
    int u;
    int v;
    int c;
    ed(int u, int v, int c)
    {
        this->u = u;
        this->v = v;
        this->c = c;
    }
};
void marwan()
{
    int n, e;
    cin >> n >> e;
    vector<ed> v;
    for (int i = 0; i < e; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        v.push_back(ed(a, b, c));
    }
    for (int i = 0; i <= n; i++)
        dis[i] = INT_MAX, par[i] = -1;
    dis[1] = 0;
    int x = -1;
    for (int i = 0; i < n; i++)
    {
        x = -1;
        for (auto ed : v)
        {
            if (dis[ed.u] < INT_MAX && dis[ed.u] + ed.c < dis[ed.v])
            {
                dis[ed.v] = dis[ed.u] + ed.c;
                par[ed.v] = ed.u;
                x = ed.v;
            }
        }
    }
    // cout << x << endl;
    // for (int i = 1; i <= n; i++)
    //     cout << i << "->" << par[i] << endl;
    // cout << endl;
    if (x == -1)
    {
        cout << "Cycle Nai\n";
        
    }
    else
    {
        cout << "Cycle Ase\n";
        for (int i = 1; i <= n; i++)
            x = par[x];
        vector<int> a;
        int z = 0;
        for (int v = x; z < 100; v = par[v])
        {
            cout << v << " ";
            z++;
            // a.push_back(v);
            // if (v == x && a.size() > 1)
            //     break;
        }
        reverse(all(a));
        for (auto vl : a)
            cout << vl << " ";
        cout << endl;
    }
}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    marwan();
    return 0;
}