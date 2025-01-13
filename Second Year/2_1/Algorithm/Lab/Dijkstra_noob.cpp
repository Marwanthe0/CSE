#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define M 1000000007
#define N 1000000
#define endl "\n"
#define all(v) v.begin(), v.end()
#define forn for (int i = 0; i < n; i++)
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
// class cmp
// {
// public:
//     bool operator()(pair<int, pair<int, char>> a, pair<int, pair<int, char>> b)
//     {
//         return a.first > b.first;
//     }
// };
void marwan()
{
    int n;
    cin >> n;
    priority_queue<pair<int, pair<int, char>>, vector<pair<int, pair<int, char>>>, greater<pair<int, pair<int, int>>>> pq;
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        char c;
        cin >> c;
        pq.push({a, {b, c}});
    }
    while (!pq.empty())
    {
        pair<int, pair<int, char>> tmp = pq.top();
        pq.pop();
        cout << tmp.first << " " << tmp.second.first << " " << tmp.second.second << endl;
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
    marwan();
    return 0;
}