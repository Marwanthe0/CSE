#include <bits/stdc++.h>
using namespace std;
#define int long long
#define M 1000000007
#define N 1000005
#define INF 1e17
#define endl "\n"
#define all(v) v.begin(), v.end()
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
#define minus cout << "-1" << endl
#define zero cout << "0" << endl
#define make_unique(x) \
    sort(all((x)));    \
    (x).erase(unique(all((x))), (x).end())
int n;
vector<set<int>> g;
vector<int> parent, dist;
void dfs(int u, int p, int d) {
    dist[u] = d;
    for (auto v : g[u]) {
        if (v != p) {
            parent[v] = u;
            dfs(v, u, d + 1);
        }
    }
}
set<int> marked;
void dfs2(int u, int p, int d, bool flag = true) {
    if (marked.count(u) == 0) {
        dist[u] = d;
    }
    for (auto v : g[u]) {
        if (v == p)
            continue;
        if (flag) {
            if (marked.count(v) == 0 && (u == 1 || d != -1))
                dfs2(v, u, d + 1, flag);
            else
                dfs2(v, u, d, flag);
        } else {
            if (marked.count(v) == 0)
                dfs2(v, u, d + 1, flag);
            else
                dfs2(v, u, d, flag);
        }
    }
}
void marwan(int cs) {
    cin >> n;
    g.assign(n + 1, set<int>());
    marked.clear();
    parent.assign(n + 1, -1);
    dist.assign(n + 1, 0);
    for (int i = 0; i + 1 < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].insert(v);
        g[v].insert(u);
    }
    dfs(1, 0, 0);
    int mx1 = 1;
    for (int i = 1; i <= n; i++) {
        if (dist[i] > dist[mx1])
            mx1 = i;
    }
    // cerr << mx1 << " ";
    while (parent[mx1] != -1) {
        int u = parent[mx1], v = mx1;
        marked.insert(u);
        marked.insert(v);
        mx1 = parent[mx1];
    }
    if (g[1].size() != 1) {
        dist.assign(n + 1, -1);
        dfs2(1, 0, -1);
        mx1 = 1;
        for (int i = 1; i <= n; i++) {
            // cerr << i << " " << dist[i] << endl;
            if (dist[i] >= 0 && dist[i] > dist[mx1])
                mx1 = i;
        }
        while (parent[mx1] != -1) {
            int u = parent[mx1], v = mx1;
            marked.insert(u);
            marked.insert(v);
            mx1 = parent[mx1];
        }
    }
    // cerr << mx1 << endl;
    dist.assign(n + 1, -1);
    dfs2(1, 0, -1, 0);
    mx1 = 1;
    for (int i = 1; i <= n; i++) {
        // cerr << i << " " << dist[i] << endl;
        if (dist[i] >= 0 && dist[i] > dist[mx1])
            mx1 = i;
    }
    cout << n - (dist[mx1] + 1) << endl;
}
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        // cout << "Case " << i << ": ";
        marwan(i);
    }
    return 0;
}
