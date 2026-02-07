#include <bits/stdc++.h>
using namespace std;
void marwan()
{
    cout << "Enter Number of processes:";
    int n;
    cin >> n;
    queue < pair<int, pair<int, int>> q;
    for (int i = 0; i < n; i++)
    {
        cout << "Enter process arriving time and burst time";
        int a, b;
        cin >> a >> b;
        q.push({i, {a, b}});
    }
    while (!q.empty())
    {
        pair<int, pair<int, int>> p = q.front();
        q.pop();
        cout << "Process number being executed:" << p.first << endl;
    }
    cout << endl;
}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    marwan();
    return 0;
}
