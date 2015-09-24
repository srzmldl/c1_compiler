#include <bits/stdc++.h>

using namespace std;

int main()
{
    string st;
    int base;
    cin >> st;
    cin >> base;
    cout << strtol(st.c_str(), 0, base) << endl;
    return 0;
}