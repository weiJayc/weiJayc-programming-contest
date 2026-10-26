// I have been practive this for two times
// 1. I forgot it..
// 2. 2026/06/19
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 200000 + 10;
int n, query;

struct Fenwick {
    vector<int> bit;
    int n;

    Fenwick(int n) {
        this->n = n;
        bit.resize(n + 1, 0);
    }

    void add(int i, int val) {
        while (i <= n) {
            bit[i] += val;
            i += i & -i;
        }
    }

    int sum(int i) {
        int ret = 0;
        while (i > 0) {
            ret += bit[i];
            i -= i & -i;
        }
        return ret;
    }

};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T; 
    cin >> T;
    while (T--) {
        cin >> n >> query;
        Fenwick fwtree(n + query);

        int nextTop = query;
        vector<int> pos(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            pos[i] = query + i;
            fwtree.add(pos[i], 1);
        }
        for (int i = 0; i < query; ++i) {
            int id; cin >> id;
            cout << fwtree.sum(pos[id] - 1);
            if (i != query - 1) cout << " ";

            fwtree.add(pos[id], -1);
            pos[id] = nextTop--;
            fwtree.add(pos[id], 1);
        }
        cout << endl;
    }
}