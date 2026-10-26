#include <iostream>
#define MAXN 1000 + 5
using namespace std;

int main() {
    // freopen("ou.txt", "w", stdout);
    int T; cin >> T;
    int coins[MAXN] = {0};
    while (T--) {
        int n; cin >> n;

        for (int i = 0; i < n; ++i) {
            cin >> coins[i];
        }
        
        int sum = coins[0];
        int pick = 1;
        for (int i = 1; i < n - 1; ++i) {
            if (sum + coins[i] >= coins[i + 1]) {
                continue;
            }
            sum += coins[i];
            pick++;
        }
        cout << pick + 1 << endl;
    }
}
