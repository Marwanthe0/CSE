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

    struct P
{
    int id;
    int at;
    int bt;
    int rt;
    int ct;
    int wt;
    int tat;
};
int32_t main()
{
    int n;
    if (!(cin >> n))
        return 0;
    vector<P> p(n);
    for (int i = 0; i < n; i++)
    {
        p[i].id = i;
        cin >> p[i].at >> p[i].bt;
        p[i].rt = p[i].bt;
        p[i].ct = 0;
        p[i].wt = 0;
        p[i].tat = 0;
    }
    sort(p.begin(), p.end(), [](const P &a, const P &b)
         {if(a.at == b.at) return a.id < b.id;
            return a.at<b.at; });
    set<tuple<int, int, int>> rd;
    int t = p[0].at;
    int i = 0;
    int dn = 0;
    while (dn < n)
    {
        while (i < n && p[i].at <= t)
        {
            rd.insert({p[i].bt, p[i].at, i});
            i++;
        }
        if (rd.empty())
        {
            t++;
            continue;
        }
        auto it = rd.begin();
        auto [burst, arr, idx] = *it;
        rd.erase(it);
        t += p[idx].rt;
        p[idx].rt = 0;
        p[idx].ct = t;
        p[idx].wt = p[idx].ct - p[idx].at - p[idx].bt;
        p[idx].tat = p[idx].ct - p[idx].at;
        dn++;
        while (i < n && p[i].at <= t)
        {
            rd.insert({p[i].bt, p[i].at, i});
            i++;
        }
    }
    vector<P> res = p;
    sort(res.begin(), res.end(), [](const P &a, const P &b)
         { return a.id < b.id; });
    double total_wt = 0;
    double total_tat = 0;
    cout << "Process\tWaiting\tTurnaround\n";
    for (auto &pr : res)
    {
        cout << pr.id + 1 << "\t" << pr.wt << "\t" << pr.tat << "\n";
        total_wt += pr.wt;
        total_tat += pr.tat;
    }
    cout << "Average waiting time = " << (total_wt / n) << "\n";
    cout << "Average turnaround time = " << (total_tat / n) << "\n";
    return 0;
}
