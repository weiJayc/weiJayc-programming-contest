#include <bits/stdc++.h>
using namespace std;

const int MAXX = 100000;

struct Node {
    int maxH;     // 區間最高高度
    int lazy;   // 若整段等高，儲存該高度；否則為 -1
}seg_tree[MAXX * 4];

struct Buildings {
    int l, r, h;
}building[MAXX];

int overlap = 0;

void push_down(int node) {
    if (seg_tree[node].lazy != 0) {
        seg_tree[node * 2].lazy = seg_tree[node * 2].maxH = seg_tree[node].lazy;
        seg_tree[node * 2 + 1].lazy = seg_tree[node * 2 + 1].maxH = seg_tree[node].lazy;
        seg_tree[node].lazy = 0;
    }
}

void push_up(int node) {
    seg_tree[node].maxH = max(seg_tree[node * 2].maxH, seg_tree[node * 2 + 1].maxH);
}

void build(int node, int left, int right) {
    seg_tree[node].maxH = 0;
    seg_tree[node].lazy = -1;
    if (left == right) return;
    int mid = (left + right) / 2;
    build(node * 2, left, mid);
    build(node * 2 + 1, mid + 1, right);
}

void update(int left, int right, int h, int node_left, int node_right, int node) {
    // Case 1: 整段等高且已比 h 高 -> 不影響重疊
    if (seg_tree[node].maxH >= h && seg_tree[node].lazy != 0) return;
    
    // Case 2: 整段被完全覆蓋，且最高高度 <= h → 整段覆蓋
    if (left <= node_left && right <= node_right) {
        if (seg_tree[node].maxH < h) {
            seg_tree[node].lazy = seg_tree[node].maxH = h;
            overlap += node_right - node_left + 1;
            return;
        }
    }

    // Case 3: 到葉節點 → 結束
    if (node_left == node_right) return;

    // Case 4: 不相交 → 結束
    if (right < node_left || node_right < left) return;
    
    // Case 5: 部分重疊，需往下細分
    push_down(node);
    int mid = (node_left + node_right) / 2;
    if (left <= mid) {
        update(left, right, h, node_left, mid, node * 2);
    }
    if (mid < right) {
        update(left, right, h, mid + 1, node_right, node * 2 + 1);
    }
    push_up(node);
}

int main() {
    // freopen("4108.in", "r", stdin);
    // freopen("4108me.out", "w", stdout);
    int t;
    while (cin >> t, t != 0) {
        // memset(seg_tree, 0, sizeof(seg_tree));
        while (t--) {
            int n;
            cin >> n;
            
            int datamaxx = 0;
            overlap = 0;
            for (int i = 0; i < n; ++i) {
                int l, r, h;
                cin >> l >> r >> h;
                building[i] = {l, r, h};
                datamaxx = max(datamaxx, r);
            }
            build(1, 0, datamaxx);
            for (int i = 0; i < n; ++i) {
                update(building[i].l, building[i].r - 1, building[i].h, 1, datamaxx, 1);
            }
            cout << overlap << endl;
        }
    }
}