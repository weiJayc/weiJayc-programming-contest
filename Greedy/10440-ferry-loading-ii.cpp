#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // freopen("ou.txt", "w", stdout);

    int T; cin >> T;
    while (T--) {
        int capability, travel, n;
        cin >> capability >> travel >> n;

        vector<int> car(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> car[i];
        }

        
        int arrival_time = 0;
        int r = n % capability;
        int ptr = r;
        // car[] starts from 1, if the remain is 0, means we can use full capability of the ferry at the first time 
        if (ptr == 0) ptr = capability; 
        
        while (ptr <= n) {
            int delay = 0;
            if (arrival_time > car[ptr]) {
                delay = arrival_time - car[ptr];
            }

            arrival_time = car[ptr] + delay + 2 * travel;
            ptr += capability;
        }
        arrival_time -= travel;
        int times = ceil((float)n / (float)capability);
        cout << arrival_time << " " << times << "\n";
    }

    // fclose(stdout);
}