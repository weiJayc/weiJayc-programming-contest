#include <iostream>
#include <cmath>
#define MAXN 4000 + 5
using namespace std;

int main() {
    // freopen("ou.txt", "w", stdout);
    int T;
    int train[MAXN] = {0}, LIS[MAXN] = {0};
    cin >> T;
    while (T--) {
        int n;
        cin >> n;

        // input
        for (int i = 0; i < n; ++i) {
            cin >> train[n + i];
            train[n - i - 1] = train[n + i];
        }

        // compute lis
        n <<= 1; // multiply n by 2
        int max_sequence = 0;
        LIS[0] = 1;
        for (int i = 1; i < n; ++i) {
            LIS[i] = 1;     // there is one train in the sequence if we only pick the train at train[i]
            for (int j = 0; j < i; ++j) {
                if (train[j] < train[i]) {
                    LIS[i] = max(LIS[i], LIS[j] + 1);
                }
            }
            max_sequence = max(max_sequence, LIS[i]);
        }
        cout << max_sequence << endl;
    } 
}