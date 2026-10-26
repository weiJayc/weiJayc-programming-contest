#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iomanip>

using namespace std;


struct State {
    vector<int> component;
    
    bool operator==(const State& other) const {
        return this->component == other.component;
    }
    
};

struct StateHash {
    size_t operator()(const State& s) const {
        size_t h = 0;
        for (int i : s.component) {
            h = h * 31 + i;
        }
        return h;
    }
};

vector<int> parent, rnk, component_size;
int n, m;

int find(int n) {
    if (parent[n] != n) {
        parent[n] = find(parent[n]);
    }
    return parent[n];
}

void unite(int a, int b) {
    int p_a = find(a);
    int p_b = find(b);

    if (p_a != p_b) {
        if (rnk[p_a] < rnk[p_b]) {
            swap(p_a, p_b);
        }
        parent[p_b] = p_a;
        component_size[p_a] += component_size[p_b];
        if (rnk[p_a] == rnk[p_b]) {
            rnk[p_a]++;
        }
    }
}

unordered_map<State, double, StateHash> unmap;
double dfs(State& st) {
    if (st.component.size() == 1) return 0;
    
    sort(st.component.begin() + 1, st.component.end());
    
    if (unmap.count(st)) return unmap[st];
    
    int total = n - 1;
    double ans = 1.0;
    for (int i = 1; i < st.component.size(); ++i) {
        double p_i = (double)st.component[i] / total;
        State st_cpy = st;
        st_cpy.component[0] += st_cpy.component[i];
        st_cpy.component.erase(st_cpy.component.begin() + i);
        
        // degubbing
        // cout << "dfs:";
        // for (auto i : st_cpy.component) {
        //     cout << i << " ";
        // }
        // cout << endl;
        // end debugging

        ans += p_i * dfs(st_cpy);
    }
    ans /= 1 - ((double)(st.component[0] - 1) / total);
    unmap[st] = ans;
    return unmap[st];

    // 1. sort
    // 2. check if the state has exist in unmap
    // 3. if yes, return the value
    // 4. if no, start calculating expect value
    // 5. expect = 1 + p_self * expect + sigma(pi * i_size)
    // expect - p_self * expect = 1 + sigma(pi * i_size)
    // expect (1 - p_self) = 1 + sigma(pi * i_size)
    //           = 1 + sigma(pi * i_size) / 1 - p_self
    // p_self = size_self / total - 1
    // p_i =  i_size / total - 1
}

int main() {
    // freopen("ou.txt", "w", stdout);
    int T, Case = 1;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        
        parent.resize(n + 1);
        rnk.resize(n + 1);
        component_size.resize(n + 1);
        
        // initialize
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
            rnk[i] = 0;
            component_size[i] = 1;
        }
        unmap.clear();

        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            unite(a, b);
        }

        int root1 = find(1);
        
        State state;
        for (int i = 1; i <= n; ++i) {
            if (parent[i] == i && root1 == parent[i]) {
                state.component.push_back(component_size[i]);
            }
        }
        for (int i = 1; i <= n; ++i) {
            if (parent[i] == i && root1 != parent[i]) {
                state.component.push_back(component_size[i]);
            }
        }

        // n = 8;
        // vector<int> city = {3, 5};
        // State cityst;
        // cityst.component = city;
        cout << fixed << setprecision(15) << "Case " << Case++ << ": " << dfs(state) << endl;
    }
}