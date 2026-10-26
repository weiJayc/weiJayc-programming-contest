#include <iostream>
#include <cstring>
using namespace std;

int parent[100005];
int sz[100005];

int find(int x) {
    if (x == parent[x]) return x;
    parent[x] = find(parent[x]);
    return parent[x];
}

bool unite(int a, int b) {
    int roota = find(a);
    int rootb = find(b);
    
    if (roota == rootb) return false;

    if (sz[roota] < sz[rootb]) swap(roota, rootb);
    parent[rootb] = roota;
    sz[roota] += sz[rootb];
    return true;
}

int main() {
    // freopen("ou.txt", "w", stdout);

    int a;
    while (cin >> a) {
        memset(sz, 0, sizeof(sz));
        for (int i = 0; i < 100005; ++i) {
            parent[i] = i;
        }
    
        int b;
        int refused = 0;
        while (a != -1) {
            cin >> b;
    
            if (!unite(a, b)) {
                refused++;
            }
            cin >> a;
        }
        cout << refused << '\n';
    }
}