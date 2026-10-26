#include <iostream>
using namespace std;
int main() {
    // freopen("ou.txt", "w", stdout);
    unsigned int n, l, u;
    while (cin >> n >> l >> u) {
        unsigned m = 0, mask = 1;
        mask <<= 31;

        for (int i = 0; i < 32; ++i) {
            if ( (n & mask) == 0 && (m | mask) <= u) {
                m |= mask;
            }
            else if ( (m | mask) <= l) {
                m |= mask;
            }
            mask >>= 1;
        }
        cout << m << endl;
    }
}