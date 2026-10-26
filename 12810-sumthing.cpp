#include <iostream>
using namespace std;

const long long MOD = 1e9 + 9;

long long fast_pow(long long a, long long n) {
    long long result = 1;
    a %= MOD;
    while (n > 0) {
        if (n & 1) {
            result = result * a % MOD;
        }
        a = a * a % MOD;
        n >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("ou.txt", "w", stdout);
    long long inv2 = fast_pow(2, MOD - 2);
    
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        
        long long X = 1;
        for (int i = 0; i < n; ++i) {
            long long a;
            cin >> a;
            X = X * ((1 + 2 * a) % MOD) % MOD;
        }
        X -= 1; // now p = 2 * phi
        X += MOD; // To prevent X - 1 < 0, make sure X is always positive

        cout << X * inv2 % MOD << endl;
    }
}