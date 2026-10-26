#include <bits/stdc++.h>
using namespace std;

// ===== Ford-Fulkerson (DFS) =====
// 時度 O(E * maxFlow)，適合最大流很小的題目（例如二分圖匹配）
// 節點 0-ind間複雜exed。無向邊用 addEdge(from, to, capacity, capacity)。
struct FordFulkerson {
    struct Edge {
        int to;
        long long residualCapacity;
    };

    vector<Edge> edges;                  // edges[2k] 是正向邊，edges[2k+1] 是它的反向邊
    vector<vector<int>> adjacency;       // adjacency[node] = 從 node 出發的邊在 edges 中的編號
    vector<int> visitedRound;            // visitedRound[node] = node 最後一次被走過是第幾輪
    int currentRound = 0;

    FordFulkerson(int nodeCount) : adjacency(nodeCount), visitedRound(nodeCount, 0) {}

    void addEdge(int from, int to, long long capacity, long long reverseCapacity = 0) {
        adjacency[from].push_back(edges.size());
        edges.push_back({to, capacity});
        adjacency[to].push_back(edges.size());
        edges.push_back({from, reverseCapacity});
    }

    // 在殘餘圖上找一條 node -> sink 的路並推流，回傳推送量（找不到回傳 0）
    long long findAugmentingPath(int node, int sink, long long bottleneck) {
        if (node == sink) return bottleneck;
        visitedRound[node] = currentRound;
        for (int edgeIndex : adjacency[node]) {
            int nextNode = edges[edgeIndex].to;
            long long remaining = edges[edgeIndex].residualCapacity;
            if (visitedRound[nextNode] != currentRound && remaining > 0) {
                long long pushed = findAugmentingPath(nextNode, sink, min(bottleneck, remaining));
                if (pushed > 0) {
                    edges[edgeIndex].residualCapacity -= pushed;
                    edges[edgeIndex ^ 1].residualCapacity += pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }

    long long maxFlow(int source, int sink) {
        long long totalFlow = 0;
        while (true) {
            currentRound++;
            long long pushed = findAugmentingPath(source, sink, LLONG_MAX);
            if (pushed == 0) break;
            totalFlow += pushed;
        }
        return totalFlow;
    }

    // maxFlow() 之後呼叫：true = node 在最小割的 source 側
    bool isOnSourceSide(int node) { return visitedRound[node] == currentRound; }

    // 第 addOrder 次 addEdge（0-indexed）的邊目前的流量（有向邊）
    long long flowOnEdge(int addOrder) { return edges[2 * addOrder + 1].residualCapacity; }
};
// ===== end =====

int main() {
    // 範例：s=0, a=1, b=2, t=3
    FordFulkerson network(4);
    network.addEdge(0, 1, 10);
    network.addEdge(1, 2, 10);
    network.addEdge(2, 3, 10);
    network.addEdge(0, 2, 10);
    network.addEdge(1, 3, 10);
    cout << network.maxFlow(0, 3) << "\n";                                  // 20
    for (int node = 0; node < 4; node++) cout << network.isOnSourceSide(node); // 1000
    cout << "\n";

    // 無向邊測試：0-1 容量 5、1-2 容量 3，最大流 3
    FordFulkerson undirected(3);
    undirected.addEdge(0, 1, 5, 5);
    undirected.addEdge(1, 2, 3, 3);
    cout << undirected.maxFlow(0, 2) << "\n";                               // 3
}