#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define M 1000000007
#define N 1000000
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
int parent[N];
int groupSize[N];
int dsu_find(int n)
{
    if (parent[n] == -1)
        return n;
    return parent[n] = dsu_find(parent[n]);
}
void dsu_union(int a, int b)
{
    int A_er_leader = dsu_find(a);
    int B_er_leader = dsu_find(b);
    if (groupSize[A_er_leader] > groupSize[B_er_leader])
    {
        parent[B_er_leader] = A_er_leader;
        groupSize[A_er_leader] += groupSize[B_er_leader];
    }
    else
    {
        parent[A_er_leader] = B_er_leader;
        groupSize[B_er_leader] += groupSize[A_er_leader];
    }
}
void marwan()
{
    
    memset(parent, -1, sizeof(parent));
    memset(groupSize, 1, sizeof(groupSize));
    int n, e;
    cin >> e;
    vector<pair<int, int>> v;
    while (e--)
    {
        int a, b;
        cin >> a >> b;
        v.push_back({a, b});
    }
    for (auto [a, b] : v)
    {
        cout << a << " " << b << endl;
        int A_er_Leader = dsu_find(a);
        int B_er_Leader = dsu_find(b);
        if (A_er_Leader == B_er_Leader)
        {
            printf("সাইকেল পাওয়া গেছে.\n");
            return;
        }
        else
            dsu_union(a, b);
    }
    printf("এখানে কোন সাইকেল নেই\n");
}
int main()
{
    ios_base::sync_with_stdio(false);
    marwan();
    return 0;
}