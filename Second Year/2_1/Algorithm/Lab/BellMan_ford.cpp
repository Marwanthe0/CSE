#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int dis[N];
int main()
{
    int n, e;
    cin >> n >> e;
    map<pair<int, int>, int> m;
    while (e--)
    {
        int u, v, c;
        cin >> u >> v >> c;
        m[{u, v}] = c;
        m[{v, u}] = c;
    }
    for (int i = 0; i < n; i++)
    {
        dis[i] = INT_MAX;
    }
    dis[0] = 0;
    for (int i = 1; i <= n - 1; i++)
    {
        for (auto vl : m)
        {
            int u, v, c;
            u = vl.first.first;
            v = vl.first.second;
            c = vl.second;
            if (dis[u] < INT_MAX && dis[u] + c < dis[v])
            {
                dis[v] = dis[u] + c;
            }
        }
    }
    for (auto vl : m)
    {
        int u, v, c;
        u = vl.first.first;
        v = vl.first.second;
        c = vl.second;
        if (dis[u] < INT_MAX && dis[u] + c < dis[v])
        {
            cout << "Cycle Found\n";
            return 0;
        }
    }
    cout << "No Cycle Found.\n";
    for (int i = 0; i < n; i++)
        cout << i << " -> " << dis[i] << endl;
    return 0;
}