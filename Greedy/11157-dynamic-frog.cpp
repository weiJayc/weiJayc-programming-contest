#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int main() {
    // freopen("ou.txt", "w", stdout);
    int T; cin >> T;
    int cs = 1;
    while (T--) {
        vector< pair<char, int> > stone;
        int n, distance;
        cin >> n >> distance;

        stone.push_back(make_pair('B', 0));
        for (int i = 0; i < n; ++i) {
            string str;
            cin >> str;

            int c = str[0];
            int dis = stoi(str.substr(2));
            stone.push_back(make_pair(c, dis));
        }
        stone.push_back(make_pair('B', distance));

        int max_hop1 = 0, max_hop2 = 0;
        int hop1 = 0, hop2 = 0;
        for (int i = 0; i < stone.size(); ++i) {
            int curr_dis = stone[i].second;
            if (stone[i].first == 'S') {
                // hop1 first
                if (hop1 <= hop2) {
                    max_hop1 = max(max_hop1, curr_dis - hop1);
                    hop1 = curr_dis;
                }
                else {
                    max_hop2 = max(max_hop2, curr_dis - hop2);
                    hop2 = curr_dis;
                }
            }
            if (stone[i].first == 'B') {
                max_hop1 = max(max_hop1, curr_dis - hop1);
                max_hop2 = max(max_hop2, curr_dis - hop2);

                hop1 = hop2 = stone[i].second;
            }
        }
        cout << "Case " << cs++ << ": " << max(max_hop1, max_hop2) << endl;
    }
}