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
int dis[N] = {INT_MAX};
void marwan()
{
    int n, e;
    cin >> n >> e;
    int adj[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            if (i == j)
                adj[i][j] = 0;
            else
                adj[i][j] = INT_MAX;
    }
    while (e--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a][b] = c;
    }
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (adj[i][k] + adj[k][j] < adj[i][j])
                {
                    adj[i][j] = adj[i][k] + adj[k][j];
                }
            }
        }
    }
    bool flag = false;
    for (int i = 0; i < n; i++)
    {
        if (adj[i][i] < 0)
        {
            flag = true;
            break;
        }
    }
    if (flag)
        cout << "Cycle Found\n";
    else
        cout << "Cycle Not found\n";
}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    marwan();
    return 0;
}