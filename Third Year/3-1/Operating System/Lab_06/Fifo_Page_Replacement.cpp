#include <bits/stdc++.h>
using namespace std;
int pagefaults(int n,vector<int> pages, int capacity)
{
    unordered_set<int> s;
    queue<int> q;
    int pf = 0;
    vector<int> faults;
    for (int page : pages)
    {
        if (s.find(page) == s.end())
        {
            pf++;
            faults.push_back(page);

            if (q.size() == capacity)
            {
                int old = q.front();
                q.pop();
                s.erase(old);
            }
            q.push(page);
            s.insert(page);
        }
    }
    
    for(auto vl:faults)
        cerr << vl << " ";
    cerr << endl;
    return pf;
}
void marwan()
{
    int n;
    cin >> n;
    vector<int> v(n);
    for (auto &vl : v)
        cin >> vl;
    int capacity;
    cin >> capacity;
    cout << pagefaults(n, v, capacity) << endl;
}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    marwan();
    return 0;
}