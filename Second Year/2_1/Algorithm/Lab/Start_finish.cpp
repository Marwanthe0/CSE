#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define M 1000000007
#define N 1000000
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
bool cmp(pair<int, int> a, pair<int, int> b) { return a.second < b.second; }
void marwan()
{
    int n;
    cin >> n;
    vector<pair<int, int>> v(n);
    for (auto &vl : v)
        cin >> vl.first >> vl.second;
    sort(v.begin(), v.end(), cmp);
    vector<int> ans;
    int last = v[0].second;
    ans.push_back(1);
    for (int i = 1; i < n; i++)
    {
        if (v[i].first > last)
        {
            ans.push_back(i + 1);
            last = v[i].second;
        }
    }
    cout << ans.size() << endl;
    for (auto vl : ans)
        cout << vl << " ";
    cout << endl;
}
int main()
{
    ios_base::sync_with_stdio(false);
    marwan();
    return 0;
}