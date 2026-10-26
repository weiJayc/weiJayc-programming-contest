#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;


int main() {
    // freopen("ou.txt", "w", stdout);
    int n, d, cs = 1;
    vector< pair<double, double> > islands;
    while (cin >> n >> d, n != 0 && d != 0) {
        islands.clear();
        int x, y;
        bool impossible = false;
        for (int i = 0; i < n; ++i) {
            cin >> x >> y;
            
            if (y > d) {
                impossible = true;
            }
            
            double tmp = sqrt( (d * d) - (y * y));
            double start = x - tmp;
            double end = x + tmp;
            islands.push_back(make_pair(start, end));
        }
        
        if (impossible) {
            cout << "Case " << cs++ << ": -1" << endl;
            continue;
        }
        sort(islands.begin(), islands.end(), [](const pair<double, double> a, const pair<double, double> b) {
            return a.second < b.second;
        });

        int installed = 1;
        double last_installed = islands[0].second;
        for (auto item : islands) {
            if (item.first > last_installed) {
                installed++;
                last_installed = item.second;
            }
        }
        cout << "Case " << cs++ << ": " << installed << endl;
    }
}