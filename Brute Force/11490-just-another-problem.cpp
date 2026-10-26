#include <iostream>
#include <cmath>

using namespace std;

const int MOD = 100000007;

// x: side length of each missing square
// a: uniform thickness of the rectangular border
// s = (3a + 2x) * (2a + x) - x^2
//   = (6a^2) + 7ax
// x = (s - 6a^2) / 7a
// brute force a -> calculate x -> check whether s is correct

int main() {
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);

    long long s;

    while (cin >> s, s != 0) {
        bool found_sol = false;

        for (long long a = 1; 6 * a * a < s; ++a) {
            
            // Notes: x = (s - 6a^2) / 7a
            long long numerator = s - 6 * a * a;
            long long remain = numerator % (7 * a);
            if (remain == 0) {
                long long x = numerator / (7 * a) % MOD;
                cout << "Possible Missing Soldiers = " << (2 * x * x) % MOD << endl;
                found_sol = true;
            }
        }

        if (!found_sol) {
            cout << "No Solution Possible" << endl;
        }
        cout << endl;
    }
    // fclose(stdout);
}