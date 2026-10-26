#include <iostream>
using namespace std;

int dp[12][102][102] = {0};

int main() {
    // freopen("ou.txt", "w", stdout);
    // k = 1
    for (int i = 1; i <= 100; ++i) {
        int s = 0;
        for (int j = i; j <= 100; ++j) {
            s += j;
            dp[1][i][j] = s;
        }
    }

    for (int k = 2; k <= 10; ++k) {
        for (int i = 100; i >= 1; --i) {
            for (int j = i; j <= 100; ++j) {
                int best = 2e9;
                for (int x = i; x <= j; ++x) {
                    int boom = (x - 1 >= i) ? dp[k - 1][i][x - 1] : 0;
                    int safe = (x + 1 <= j) ? dp[k][x + 1][j] : 0;
                    best = min(best, x + max(boom, safe));
                }
                dp[k][i][j] = best;
            }
        }
    }

    int n;
    cin >> n;
    while (n--) {
        int k, m;
        cin >> k >> m;
        cout << dp[k][1][m] << '\n';    
    }
}