#include <iostream>
#include <vector>
#include <cstring>
#define MAXN 1000 + 5

using namespace std;

// adjacency list
vector<int> graph[MAXN], nodes[MAXN];
int parents[MAXN];
int n, k;
bool covered[MAXN];

// do dfs from server, and maintain "nodes[]".
// nodes[i] contains all the nodes that is "i" distance away form the server
void dfs1(int curr, int p, int distance) {
    // 1. set parent
    parents[curr] = p;
    int list_size = graph[curr].size();

    // 2. if current node is leaf node, and
    // if the distance of current node is > k, push it into "nodes[]"
    if (graph[curr].size() == 1 && distance > k) {
        nodes[distance].push_back(curr);
    }

    // 3. loop the list, get all nodes that is connected to the curr
    for (int i = 0 ; i < list_size; ++i) {
        // if the node is not parent of current node, dfs them
        int u = graph[curr][i];
        if (u != p) {
            dfs1(u, curr, distance + 1);
        }
    }
    
}

// additional server will cover more nodes which distance is less than k from additional server
void dfs2(int curr, int p, int distance) {
    covered[curr] = true;
    int list_size = graph[curr].size();

    // loop all the nodes tha is connected to current node
    for (int i = 0; i < list_size; ++i) {
        int u = graph[curr][i];
        
        if (u != p && distance < k) {
            dfs2(u, curr, distance +  1);
        }
    }
}

// From "nodes[]" pick farest nodes first, start put additional server
int solve() {
    
    // init
    int add_server = 0;
    memset(covered, false, sizeof(covered));

    // 1. start from the most farest node
    for (int dist = n; dist > 0; dist--) {

        // 2. check every nodes in nodes[i]
        for (int i = 0; i < nodes[dist].size(); ++i) {
            int u = nodes[dist][i];

            if (covered[u]) continue;

            // hop k distance from uncovered nodes and put the server
            int v = u;
            for (int j = 0; j < k; ++j) {
                v = parents[v];
            }
            
            // now v is k distance away from u
            // put a server here and do dfs from this node
            dfs2(v, -1, 0);
            add_server++;
        }
    }
    return add_server;
}

int main() {
    // freopen("ou.txt", "w", stdout);
    int T; cin >> T;
    while (T--) {
        int server;
        cin >> n >> server >> k;

        // init
        for (int i = 1; i <= n; ++i) {
            graph[i].clear();
            nodes[i].clear();
        }

        // build the graph
        for (int i = 0; i < n - 1; ++i) {
            int a, b; cin >> a >> b;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }

        // do dfs from server, the node which distance from server is > k
        // will be added to the node array
        dfs1(server, -1, 0);

        cout << solve() << endl;
    }
}