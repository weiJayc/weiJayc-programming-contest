#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
#include <cmath>
using namespace std;
struct FordFulkerson {
    struct Edge {
        int to;
        long long residualCapacity;
    };

    vector<Edge> edges;
    vector<vector<int>> adjacency;
    vector<int> visitedRound;
    int currRound = 0;

    FordFulkerson(int nodeCount) : adjacency(nodeCount), visitedRound(nodeCount, 0) {}

    void addEdge(int from, int to, long long capacity, long long reverseCapacity = 0) {
        adjacency[from].push_back(edges.size());
        edges.push_back({to, capacity});
        adjacency[to].push_back(edges.size());
        edges.push_back({from, reverseCapacity});
    }

    long long findAugmentingPath(int node, int sink, long long bottleneck) {
        if (node == sink) return bottleneck;
        visitedRound[node] =  currRound;

        for (int edgeIndex : adjacency[node]) {
            int nextNode = edges[edgeIndex].to;
            long long remaining = edges[edgeIndex].residualCapacity;
            if (visitedRound[nextNode] != currRound && remaining > 0) {
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
            currRound++;
            long long pushed = findAugmentingPath(source, sink, LLONG_MAX);
            if (pushed == 0) break;
            totalFlow += pushed;
        }
        return totalFlow;
    }

    void print() {
        cout << "======== Current State ========" << endl;
        for (int i = 0; i < adjacency.size(); ++i) {
            for (auto next : adjacency[i]) {
                cout << i << "->" << edges[next].to << " with capacity " << edges[next].residualCapacity << endl;
            }
        }
        cout << "===============================\n" << endl;
    }
};

int main() {
    int T;
    int cases = 1;
    cin >> T;
    while (T--) {
        int people, stickerCount;
        cin >> people >> stickerCount;

        FordFulkerson ff(people + stickerCount + 1);
        // ff[0] = bob
        // ff[1 - stickerCount] = stickers
        // ff[stickerCount + 1 - ] = other people
        // ff[lastone] = how many stickers can bob get
        for (int i = 0; i < people; ++i) {
            vector<int> stickers(stickerCount + 1);
            int a;
            cin >> a;

            // input
            int s;
            for (int j = 0; j < a; ++j) {
                cin >> s;
                stickers[s]++;  
            }

            // check and add edge
            if (i == 0) {
                // Bob is the first one
                for (int s = 1; s <= stickerCount; ++s) {
                    ff.addEdge(0, s, stickers[s]);
                }
                
            }
            else {
                // Other people
                for (int s = 1; s <= stickerCount; ++s) {
                    if (stickers[s] == 0) {
                        // he need this sticker
                        ff.addEdge(s, stickerCount + i, 1);
                    }
                    else if (stickers[s] > 1) {
                        // he can exchange this sticker
                        ff.addEdge(stickerCount + i, s, stickers[s] - 1);
                    }
                }
            }
            // ff.print();
        }

        // add Edge to sink node;
        for (int s = 1; s <= stickerCount; ++s) {
            ff.addEdge(s, people + stickerCount, 1);
        }
        
        cout << "Case #" << cases++ << ": " << ff.maxFlow(0, stickerCount + people) << endl;
    }   
}