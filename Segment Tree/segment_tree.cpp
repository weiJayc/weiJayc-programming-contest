#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
long long arr[N];
long long seg[4*N];
long long lazy[4*N];

// 建樹
void build(int node, int node_left, int node_right) {
    if (node_left == node_right) {
        seg[node] = arr[node_left];
        return;
    }
    int mid = (node_left + node_right) / 2;
    build(node * 2, node_left, mid);
    build(node * 2 + 1, mid + 1, node_right);
    seg[node] = seg[node*2] + seg[node*2+1];
}

// 把懶標記往下推（如果有需要）
void pushDown(int node, int node_left, int node_right) {
    if (lazy[node] != 0) {
        // 把累積的加值套用到目前節點
        seg[node] += (node_right - node_left + 1) * lazy[node];

        // 若不是葉節點，傳給子節點
        if (node_left != node_right) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }

        // 清空當前節點的懶標記
        lazy[node] = 0;
    }
}

// 區間加值更新
void updateRange(int node, int node_left, int node_right, int query_left, int query_right, long long val) {
    pushDown(node, node_left, node_right);

    // 不重疊
    if (query_right < node_left || node_right < query_left) return;

    // 完全覆蓋
    if (query_left <= node_left && node_right <= query_right) {
        lazy[node] += val;
        pushDown(node, node_left, node_right);
        return;
    }

    // 部分重疊
    int mid = (node_left + node_right) / 2;
    updateRange(node * 2, node_left, mid, query_left, query_right, val);
    updateRange(node * 2 + 1, mid + 1, node_right, query_left, query_right, val);
    seg[node] = seg[node*2] + seg[node*2+1];
}

// 區間和查詢
long long queryRange(int node, int node_left, int node_right, int query_left, int query_right) {
    pushDown(node, node_left, node_right);

    // 不重疊
    if (query_right < node_left || node_right < query_left) return 0;

    // 完全覆蓋
    if (query_left <= node_left && node_right <= query_right) return seg[node];

    // 部分重疊
    int mid = (node_left + node_right) / 2;
    return queryRange(node * 2, node_left, mid, query_left, query_right) +
           queryRange(node * 2 + 1, mid + 1, node_right, query_left, query_right);
}

int main() {
    int n = 6;
    long long A[] = {1, 3, 5, 7, 9, 11};
    for (int i=0; i<n; i++) arr[i] = A[i];

    build(1, 0, n-1);

    cout << "Sum [1,4] = " << queryRange(1, 0, n-1, 1, 4) << endl; // 24

    // 把 [1,3] 區間都加 2
    updateRange(1, 0, n-1, 1, 3, 2);

    cout << "After update +2 to [1,3], Sum [1,4] = "
         << queryRange(1, 0, n-1, 1, 4) << endl; // (3+2)+(5+2)+(7+2)+9 = 30
}
