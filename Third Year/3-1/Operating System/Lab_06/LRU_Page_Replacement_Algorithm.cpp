#include <bits/stdc++.h>
using namespace std;
int pagefaults(int n, vector<int> pages, int capacity)
{
    list<int> l;
    unordered_map<int, list<int>::iterator> mp;
    int pf = 0;
    vector<int> faults;
    for (int page : pages)
    {
        if (mp.find(page) == mp.end())
        {
            pf++;
            faults.push_back(page);

            if (l.size() == capacity)
            {
                int lru = l.front();
                l.pop_front();
                mp.erase(lru);
            }
        }
        else
        {
            l.erase(mp[page]);
        }
        
        l.push_back(page);
        mp[page] = --l.end();
    }
    for (auto vl : faults)
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