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
void marwan()
{
    cout << "Enter Number of processes:";
    int n;
    cin >> n;
    cout << "Enter Number of Memories";
    int m;
    cin >> m;
    vector<vector<int>> alloc(n, vector<int>(m)), mx(n, vector<int>(m)), need(n, vector<int>(m));
    cout << "Enter allocation mattrix" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> alloc[i][j];
        }
    }
    cout << "Enter Max mattrix" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> mx[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = mx[i][j] - alloc[i][j];
        }
    }
    vector<int> available(m);
    cout << "Enter available memories:" << endl;
    for (int i = 0; i < m; i++)
    {
        cin >> available[i];
    }
    vector<int> vis(n + 1, 0), ss;
    int count = 0;
    while (count < n)
    {
        int tcount = count;
        for (int i = 0; i < n; i++)
        {
            if (vis[i])
                continue;
            bool flag = true;
            for (int j = 0; j < m; j++)
            {
                if (need[i][j] > available[j])
                {
                    flag = false;
                }
            }
            if (flag)
            {
                vis[i] = 1;
                ss.push_back(i);
                for (int j = 0; j < m; j++)
                    available[j] += alloc[i][j];
                count++;
            }
        }
        if (count == tcount)
        {
            cout << "Sequence Not Possible" << endl;
            return;
        }
    }
    cout << "Safe Sequence:";
    for (auto vl : ss)
        cout << "p" << vl << " ";
    cout << endl;
}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    marwan();
    return 0;
}