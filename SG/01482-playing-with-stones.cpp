#include <bits/stdc++.h>
using namespace std;
long long SG(long long x) {
    return (x % 2 == 0) ? x / 2 : SG(x / 2);
}

int main() {
    freopen("ou.txt", "w", stdout);
    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        long long a, v = 0;
        for (int i = 0; i < n; ++i) {
            cin >> a;
            v ^= SG(a);
        }

        if (v) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
    }
}