#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>

using namespace std;
const int MAXN = 200 + 1;
int dp[MAXN][MAXN][MAXN] = {0};

int solve(int l, int r, int k, int n, vector<int>& box) {
    if (l > r) {
        return 0;
    }

    if (dp[l][r][k] != -1) {
        return dp[l][r][k];
    }

    int rr = r, kk = k;
    while (r >= 1 && r - 1 >= l && box[r] == box[r - 1]) {
        r--;
        k++;
    }

    int max_point = solve(l, r - 1, 0, n, box) + (k + 1) * (k + 1);
    for (int i = l; i < r; ++i) {
        if (box[i] == box[r]) {
            max_point =  max (max_point, solve(l, i, k + 1, n, box) + solve(i + 1, r - 1, 0, n, box));
        }
    }

    dp[l][rr][kk] = max_point;
    return max_point;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // freopen("ou.txt", "w", stdout);

    int T; cin >> T;
    int cases = 1;
    while (T--) {
        int n;
        cin >> n;
        vector<int> box(n);
        for (int i = 0; i < n; ++i) {
            cin >> box[i];
        }

        memset(dp, -1, sizeof(dp));
        
        cout << "Case " << cases++ << ": " << solve(0, n - 1, 0, n, box) << "\n";
    }
    // fclose(stdout);
}

// pesudo code
// n is the number of box
// vector<int> box(n)
// for i <- 0 to n do:
//     cin >> box[i]

// declare dp[manx][maxn][maxn];
// l <- 0
// r <- n - 1
// k <- 0
// print solve(dp, l, r, k);

// int solve(dp, l, r, k)
//     if l > r:
//         return 0
//
//     if dp[l][r][k] != -1:
//         return dp[l][r][k];
//     maxPoint = solve(l, r - 1, 0) + (k + 1)^2

//     for i <- l to r - 1 do:
//         if box[i] == box[r]:
//           maxPoint = max(maxPoint, solve(l, i, k + 1) + solve(i + 1, r - 1, 0) )
//
//     dp[l][r][k] = maxPoint
//     return maxPoint