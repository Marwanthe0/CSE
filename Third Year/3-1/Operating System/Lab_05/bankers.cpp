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
    int n, m;
    // printf("Enter number of processes and number of resources");
    cin >> n >> m;
    vector<vector<int>> alloc(n, vector<int>(m, 0));
    vector<vector<int>> max(n, vector<int>(m, 0));
    vector<vector<int>> need(n, vector<int>(m, 0));
    vector<int> avail(m, 0);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> alloc[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> max[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    cerr << "Need Mattrix" << endl;
    for (auto &vl : avail)
        cin >> vl;
    for (auto row : need)
    {
        for (auto vl : row)
            cerr << vl << " ";
        cerr << endl;
    }
    int count = 0, prevcount = 0;
    vector<bool> found(n, false);
    vector<int> ans;
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            bool flag = true;
            if (found[i])
                continue;
            for (int j = 0; j < m; j++)
            {
                if (avail[j] < need[i][j])
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                count++;
                found[i] = true;
                ans.push_back(i);
                for (int j = 0; j < m; j++)
                    avail[j] += alloc[i][j];
            }
        }
        if (count == n)
        {
            cout << "All Processes completed successfully." << endl;
            cout << "Process Order:";
            for (auto vl : ans)
                cout << "p" << vl << " ";
            cout << endl;
            return;
        }
        if (count == prevcount)
        {
            printf("Unsafe State occured.");
            return;
        }
        prevcount = count;
    }
}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    marwan();
    return 0;
}