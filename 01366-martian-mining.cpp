#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int Y[505][505] = {0};
int B[505][505] = {0};
int dp[505][505] = {0};

int main() {
    // freopen("ou.txt", "w", stdout);
    int n, m;
    while (cin >> n >> m, n != 0 && m != 0) {
        memset(Y, 0, sizeof(Y));
        memset(B, 0, sizeof(B));
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                cin >> Y[i][j];
                Y[i][j] += Y[i][j - 1];
            }
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                cin >> B[i][j];
                B[i][j] += B[i - 1][j];
            }
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                dp[i][j] = max(dp[i - 1][j] + Y[i][j], dp[i][j - 1] + B[i][j]);
            }
        }
        cout << dp[n][m] << endl;
    }
}