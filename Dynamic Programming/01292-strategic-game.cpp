#include <bits/stdc++.h>
const int maxn = 1500 + 5;
using namespace std;

int dp[maxn][2] = {0};
vector<int> g[maxn];

void dfs(int u, int parent) {
    dp[u][0] = 0;
    dp[u][1] = 1;

    for (int v : g[u]) {
        if (v == parent) continue;
        dfs(v, u);

        dp[u][0] += dp[v][1];
        dp[u][1] += min(dp[v][1], dp[v][0]);
    }
}

int main() {
    freopen("ou.txt", "w", stdout);
    int N;
    while (cin >> N) {
        // init
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < N; ++i) g[i].clear();

        // insert node
        int node, edge;
        for (int i = 0; i < N; ++i) {
            scanf("%d:(%d)", &node, &edge);

            int neighbor;
            for (int j = 0; j < edge; ++j) {
                cin >> neighbor;
                g[node].push_back(neighbor);
                g[neighbor].push_back(node);
            }
        }

        dfs(0, -1);

        cout << min(dp[0][0], dp[0][1]) << endl;

    }
}