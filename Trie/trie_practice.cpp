#include <iostream>
#include <vector>
using namespace std;

struct TrieNode {
    TrieNode* children[26];
    bool is_leaf;

    TrieNode () {
        is_leaf = false;
        for (int i = 0; i < 26; ++i) {
            children[i] = nullptr;
        }
    }
};

void insert(TrieNode* root, string key) {
    TrieNode* curr = root;

    for (char c : key) {
        if (curr->children[c - 'a'] == nullptr) {
            curr->children[c - 'a'] = new TrieNode();
        }
        curr = curr->children[c - 'a'];
    }
    curr->is_leaf = true;
}

bool search(TrieNode* root, string key) {
    TrieNode* curr = root;

    if (curr == nullptr) return false;
    for (char c : key) {
        if (curr->children[c - 'a'] == nullptr) {
            return false;
        }
        curr = curr->children[c - 'a'];
    }
    return curr->is_leaf;
}

bool isPrefix(TrieNode* root, string key) {
    TrieNode* curr = root;

    if (curr == nullptr) return false;
    for (char c : key) {
        if (curr->children[c - 'a'] == nullptr) {
            return false;
        }
        curr = curr->children[c - 'a'];
    }
    return true;
}

int main()
{

    // Create am example Trie
    TrieNode *root = new TrieNode();
    vector<string> arr = {"and", "ant", "do", "dad"};
    for (const string &s : arr)
    {
        insert(root, s);
    }

    // One by one search strings
    vector<string> searchKeys = {"do", "gee", "bat"};
    for (string &s : searchKeys){
        
        if(search(root, s))
            cout << "true ";
        else
            cout << "false ";
    } 
    cout<<"\n";

    // One by one search for prefixes
    vector<string> prefixKeys = {"ge", "ba", "do", "de", "an"};
    for (string &s : prefixKeys){
        
        if (isPrefix(root, s))
            cout << "true ";
        else
            cout << "false ";
    }

    return 0;
}