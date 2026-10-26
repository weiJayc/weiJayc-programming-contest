// UVA 1449 - Dominating Patterns
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct TrieNode {
    TrieNode* children[26];
    TrieNode* fail;
    int word_id;
    bool is_leaf;

    TrieNode () {
        is_leaf = false;
        fail = nullptr;
        word_id = -1;
        for (int i = 0; i < 26; ++i) {
            children[i] = nullptr;
        }
    }
};

void build_failure(TrieNode* root) {
    queue<TrieNode*> q;

    for (int i = 0; i < 26; ++i) {
        if (root->children[i]) {
            root->children[i]->fail = root;
            q.push(root->children[i]);
        }
    }

    while(!q.empty()) {
        TrieNode* current = q.front(); q.pop();

        for (int i = 0; i < 26; ++i) {
            if (!current->children[i]) continue;
            TrieNode* child = current->children[i];

            TrieNode* f = current->fail;
            while (f && !f->children[i]) {
                f = f->fail;
            }

            if (f) {
                child->fail = f->children[i];
            }
            else {
                child->fail = root;
            }
            q.push(child);
        }
    }
}

void insert(TrieNode* root, string& key, int id) {
    TrieNode* curr = root;

    for (char c : key) {
        if (curr->children[c - 'a'] == nullptr) {
            curr->children[c - 'a'] = new TrieNode();
        }
        curr = curr->children[c - 'a'];
    }
    curr->is_leaf = true;
    curr->word_id = id;
}

void query(TrieNode* root, string& text, vector<int>& match_count) {
    TrieNode* node = root;

    for (char c : text) {
        int i = c - 'a';

        while (node != root && !node->children[i]) {
            node = node->fail;
        }
        if (node->children[i]) {  // if root doesn't have children[i], then it won't jump into this if condiction (which means stay at root)
            node = node->children[i];
        }

        TrieNode* temp = node;
        while (temp != root && temp != nullptr) {
            if (temp->is_leaf) {
                match_count[temp->word_id]++;
            }
            temp = temp->fail;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    while (cin >> n, n != 0) {
        vector<string> words(n);
        vector<int> match_count(n, 0);
        TrieNode* root = new TrieNode();

        for (int i = 0; i < n; ++i) {
            cin >> words[i];
            insert(root, words[i], i);
        }

        build_failure(root);

        string text;
        cin >> text;
        query(root, text, match_count);

        int max_match = 0;
        for (int cnt : match_count) {
            max_match = max (max_match, cnt);
        }
        cout << max_match << endl;
        for (int i = 0; i < n; ++i) {
            if (match_count[i] == max_match) {
                cout << words[i] << endl;
            }
        }

    }
}