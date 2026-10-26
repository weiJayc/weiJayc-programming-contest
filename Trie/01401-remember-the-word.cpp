#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

const int maxnode = 4000 * 100 + 5;
const int MOD = 20071027;

struct Trie {
    int ch[maxnode][26];
    int str_end_id[maxnode];
    int next_node_pos;
    vector<string> keywords;

    void init() {
        memset(ch[1], 0, sizeof(ch[1]));
        str_end_id[1] = 0;
        keywords.clear();
        keywords.resize(1);
        next_node_pos = 2;
    }

    void insert(const char* str, int id) {
        int current = 1;
        for (int i = 0; str[i]; ++i) {
            int c = str[i] - 'a';
            if (!ch[current][c]) {

                // init new node
                memset(ch[next_node_pos], 0, sizeof(ch[next_node_pos]));
                str_end_id[next_node_pos] = 0;
                
                ch[current][c] = next_node_pos++;
            }
            current = ch[current][c];
        }
        str_end_id[current] = id;
    }

    void find_prefix(const char* str, vector<int>& match_id) {
        int current = 1;
        for (int i = 0; str[i]; ++i) {
            int cidx = str[i] - 'a';
            if (!ch[current][cidx]) {
                break;
            }
            current = ch[current][cidx];
            if (str_end_id[current]) {
                match_id.push_back(str_end_id[current]);
            }
        }
    }
};

Trie trie;
int main() {
    string text;
    int cases = 1;
    while (cin >> text) {
        trie.init();

        int N; cin >> N;
        for (int id = 1; id <= N; ++id) {
            string keyword; cin >> keyword;
            trie.keywords.push_back(keyword);
            trie.insert(keyword.c_str(), id);
        }

        int textlen = text.size();
        vector<int> dp(textlen + 1, 0);
        dp[textlen] = 1;
        for (int i = textlen - 1; i >= 0; i--) {
            vector<int> match_id;
            trie.find_prefix(text.c_str() + i, match_id);
            for (int j = 0; j < match_id.size(); ++j) {
                dp[i] = (dp[i] + dp[i + trie.keywords[ match_id[j] ].size() ] ) % MOD;
            }
        }
        cout << "Case " << cases++ << ": " << dp[0] << endl;
    }
}