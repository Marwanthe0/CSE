#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define M 1000000007
#define N 1000000
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
class cow
{
public:
    void sound()
    {
        cout << "Moo Moo" << endl;
    }
    string sound(char c)
    {
        return "Moo Moo\n";
    }
    int sound(int a)
    {
        return 100100;
    }
    string sound(string s)
    {
        return "Hamba Hamba\n";
    }
};
int main()
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
    {
        cow *ob = new cow();
        string s;
        cin >> s;
        if (s.size() == 1)
        {
            if (s[0] >= '0' && s[0] <= '9')
                cout << ob->sound(s[0] - '0') << endl;
            else
                cout << ob->sound(s[0]);
        }
        else if (s.size() > 1)
            cout << ob->sound(s);
        else
            ob->sound();
    }
    return 0;
}