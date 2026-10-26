#include <iostream>
using namespace std;
int main() {
    int T;
    cin >> T;
    while (T--) {
        int participants;
        cin >> participants;

        int leftN = participants / 2;
        int rightN = participants - leftN;
        leftN--;
        rightN--;
        cout << (leftN * (leftN + 1) + rightN * (rightN + 1)) / 2 << endl;
    }
}