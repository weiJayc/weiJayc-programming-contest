#include <iostream>
using namespace std;
int main() {
    // freopen("ou.txt", "w", stdout);
    // g[L]: 長度 L 的 SG 值
    int g[21] = {0};
    for (int L = 1; L <= 20; ++L) {
        bool seen[64] = {false};
        for (int k = 1; k <= 2; ++k) {
            for (int i = 0; i + k <= L; ++i) {
                seen[g[i] ^ g[L - i - k]] = true;
            }
        }
        while (seen[g[L]]) g[L]++;
    }

    int T;
    int cases = 1;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        int  a[20];
        for (int i = 0; i < m; ++i) {
            cin >> a[i];
        }
        
        int x = g[(a[0] - 1) + (n - a[m - 1])];
        for (int i = 0; i + 1 < m; ++i) {
            x ^= g[a[i + 1] - a[i] - 1];
        }
        cout << "Case " << cases++ << ": " << (x ? "yes" : "no") << endl;
    }
}