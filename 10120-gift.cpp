#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool bfs(int n, int gift) {
    queue< pair<int, int> >q;
    q.push({0, 1});
    while (!q.empty()) {
        auto curr = q.front();
        q.pop();
        if (curr.first == gift) return true;

        int left = curr.first - curr.second;
        int right = curr.first + curr.second;
        if (left > 0) q.push({left, curr.second + 2});
        if (right <= n) q.push({right, curr.second + 2});
    }
    return false;
}

int main() {
    int n, gift;
    // freopen("ou.txt", "w", stdout);
    while (cin >> n >> gift, n != 0 && gift != 0) {
        if (n >= 49 || bfs(n, gift)) {
            cout << "Let me try!" << endl;
        }
        else {
            cout << "Don't make fun of me!" << endl;
        }
    }
}