#include <iostream>
#include <string.h>
#include <queue>
#include <vector>
#include <iomanip>
using namespace std;

const int MAXNODE = 20 * 20 + 10;
const int ALPHABET_SIZE = 62;

int map_idx(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A';
    }
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 26;
    }
    return c - '0' + 26 + 10;
}

struct AC_Autometa {
    int ch[MAXNODE][ALPHABET_SIZE];
    int fail[MAXNODE];
    int match[MAXNODE];
    int next_node_pos;

    void init() {
        memset(ch[0], 0, sizeof(ch[0]));
        next_node_pos = 1;
        match[0] = 0;
    }

    void insert(const string& pattern) {
        int current = 0;
        for (char c : pattern) {
            int cidx = map_idx(c);
            if (!ch[current][cidx]) {
                memset(ch[next_node_pos], 0, sizeof(ch[next_node_pos]));
                match[next_node_pos] = 0;
                ch[current][cidx] = next_node_pos;
            }
            current = ch[current][cidx];
        }
        match[current] = 1;
    }

    void getFail() {
        queue<int> q;
        fail[0] = 0;
        for (int c = 0; c < ALPHABET_SIZE; ++c) {
            int current = ch[0][c];
            if (current) {
                fail[current] = 0;
                q.push(current);
            }
        }

        while (!q.empty()) {
            int current = q.front(); q.pop();

            for (int c = 0; c < ALPHABET_SIZE; ++c) {
                if (!ch[current][c]) {
                    ch[current][c] = ch[ fail[current] ][c];
                    continue;
                }
                q.push(ch[current][c]);
                int f = fail[current];
                while (f && !ch[f][c]) {
                    f = fail[f];
                }
                fail[ ch[current][c] ] = ch[f][c];
                if (match[ch[f][c]]) {
                    match[ch[current][c]] = 1;
                }
            }
        }
    }
};


AC_Autometa ac;
vector<double> prob(ALPHABET_SIZE);
int visited[MAXNODE][100 + 5];
double dp[MAXNODE][100 + 5];

double getProb(int node, int L) {
    if (!L) return 1.0;
    if (visited[node][L]) return dp[node][L];
    visited[node][L] = 1;

    double& ans = dp[node][L];
    for (int c = 0; c < ALPHABET_SIZE; ++c) {
        if (!ac.match[ ac.ch[node][c] ])  {
            ans += ans + getProb(ac.ch[node][c], L - 1);
        }
    }
    return ans;
}

int main() {
    int cases = 1;
    int T; cin >> T;
    while (T--) {
        ac.init();
        fill(prob.begin(), prob.end(), 0.0);

        int K; cin >> K;
        while (K--) {
            string pattern;
            cin >> pattern;
            ac.insert(pattern);
        }

        int N;
        cin >> N;
        while (N--) {
            char c;
            double probability;
            cin >> c >> probability;
            prob[map_idx(c)] = probability;
        }
        int L; cin >> L;
        ac.getFail();
        
        memset(visited, 0, sizeof(visited));
        cout << fixed << setprecision(6) << "Case #" << ": " << cases++ << getProb(0, L);
    }
}