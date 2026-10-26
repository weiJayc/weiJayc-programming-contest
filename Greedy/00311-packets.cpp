#include <iostream>
#include <cmath>
using namespace std;
int main() {
    // freopen("ou.txt", "w", stdout);
    int a1, a2, a3, a4, a5, a6;
    while (cin >> a1 >> a2 >> a3 >> a4 >> a5 >> a6) {
        if (a1 + a2 + a3 + a4 + a5 + a6 == 0) break;

        int total_parcels = 0;

        // 6 x 6
        total_parcels += a6;
        
        // 5 x 5
        total_parcels += a5;
        a1 -= min(a1, a5 * 11);

        // 4 x 4
        total_parcels += a4;
        int use_of_2 = min(a2, a4 * 5);
        a2 -= use_of_2;
        if (a2 == 0) {
            int space_left_for_1 = 4 * ((a4 * 5) - use_of_2);
            a1 -= min(a1, space_left_for_1);
        }
        
        // 3 x 3
        total_parcels += a3 / 4;
        int remain_of_3 = a3 % 4;
        if (remain_of_3 != 0) {
            total_parcels++;
        }
        if (remain_of_3 == 1) {
            int use_of_2 = min(a2, 5);
            a2 -= use_of_2;
            int space_left_for_1 = 27 - (4 * use_of_2);
            a1 -= min(a1, space_left_for_1);
        }
        else if (remain_of_3 == 2) {
            int use_of_2 = min(a2, 3);
            a2 -= use_of_2;
            int space_left_for_1 = 18 - (4 * use_of_2);
            a1 -= min(a1, space_left_for_1);
        }
        else if (remain_of_3 == 3) {
            int use_of_2 = min(a2, 1);
            a2 -= use_of_2;
            int space_left_for_1 = 9 - (4 * use_of_2);
            a1 -= min(a1, space_left_for_1);
        }

        // 2 x 2
        if (a2 > 0) {
            int box2 = (a2 + 8) / 9;           // ceil(a2 / 9)
            total_parcels += box2;

            int free_slots = box2 * 9 - a2;    // space for box2(multiples of 9) - number of box2 = remaining space
            int space_left_for_1 = free_slots * 4;
            a1 -= min(a1, space_left_for_1);
        }

        // 1 x 1
        total_parcels += (a1 + 35) / 36;

        cout << total_parcels << endl;
    }
}