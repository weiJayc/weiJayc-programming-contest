#include <iostream>
#include <cmath>
#define MAXN 1000 + 5
using namespace std;

bool is_pal(const string& str, int r, int l) {
    while (l <= r) {
        if (str[l] != str[r]) {
            return false;
        }
        l++;
        r--;
    }
    return true;
}

int main() {
    // freopen("ou.txt", "w", stdout);
    int T; cin >> T;
    while (T--) {
        string str;
        cin >> str;
        
        int dp[MAXN] = {0};
        for (int i = 0; i < str.size(); ++i) {
            dp[i] = i + 1;
            for (int j = 0; j <= i; ++j) {
                if (is_pal(str, i, j)) {
                    if (j == 0) dp[i] = 1;
                    dp[i] = min(dp[i], dp[j - 1] + 1);
                }
            }
        }
        cout << dp[str.size() - 1] << endl;
    }
}

