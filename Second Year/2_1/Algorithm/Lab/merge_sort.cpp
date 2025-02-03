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
void merge(vector<int> &v, int low, int mid, int high)
{
    int left = mid - low + 1, right = high - mid, k = low, l = 0, r = 0;
    vector<int> lv(left), rv(right);
    for (int i = 0; i < left; i++)
    {
        lv[i] = v[low + i]++;
    }
    for (int i = 0; i < right; i++)
    {
        rv[i] = v[mid + 1 + i]++;
    }
    while (l < left && r < right)
    {
        if (lv[l] <= rv[r])
        {
            v[k] = lv[l++];
        }
        else
            v[k] = rv[r++];
        k++;
    }
    while (l < left)
        v[k++] = lv[l++];
    while (r < right)
    {
        v[k++] = rv[r++];
    }
}
void merge_sort(vector<int> &v, int start, int end)
{
    if (start >= end)
        return;
    int mid = start + (end - start) / 2;
    merge_sort(v, start, mid);
    merge_sort(v, mid + 1, end);
    merge(v, start, mid, end);
}
void marwan()
{
    int n;
    cin >> n;
    vector<int> v(n);
    for (auto &vl : v)
        cin >> vl;
    for (auto vl : v)
        cout << vl << " ";
    cout << endl;
    merge_sort(v, 0, n - 1);
    for (auto vl : v)
        cout << vl << " ";
}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    marwan();
    return 0;
}