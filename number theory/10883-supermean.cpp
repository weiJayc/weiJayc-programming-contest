#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("ou.txt", "w", stdout);
    int T; cin >> T;
    int cases = 1;
    
    while (T--) {
        int N;
        long double res = 0, a, c = 0;
        cin >> N;

        for (int i = 0; i < N; ++i) {
            cin >> a;
            long double sum = log2(fabs(a));

            if (i > 0) {
                c += log2( (long double)(N - i) / i);
                sum += c;
            }

            if (a < 0) {
                res -= pow(2, sum - (N - 1));
            }
            else {
                res += pow(2, sum - (N - 1));
            }
        }
        printf("Case #%d: %.3Lf\n", cases++, res);
    }
}