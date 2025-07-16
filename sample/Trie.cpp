#include <iostream>
#include <array>
#include <string>
using namespace std;

const int ALPHABET_SIZE = 26;
const int MAX_NODES = 1000000; // Sửa tùy theo bài toán

struct TrieNode
{
    bool isEnd = false;
    array<TrieNode *, ALPHABET_SIZE> children{};

    void reset()
    {
        isEnd = false;
        children.fill(nullptr);
    }
};

class Trie
{
private:
    TrieNode pool[MAX_NODES];
    int poolIndex = 0;
    TrieNode *root;

    TrieNode *newNode()
    {
        TrieNode *node = &pool[poolIndex++];
        node->reset();
        return node;
    }

public:
    Trie()
    {
        root = newNode();
    }

    void insert(const string &word)
    {
        TrieNode *node = root;
        for (char c : word)
        {
            int idx = c - 'a';
            if (!node->children[idx])
                node->children[idx] = newNode();
            node = node->children[idx];
        }
        node->isEnd = true;
    }

    bool search(const string &word) const
    {
        TrieNode *node = root;
        for (char c : word)
        {
            int idx = c - 'a';
            if (!node->children[idx])
                return false;
            node = node->children[idx];
        }
        return node->isEnd;
    }

    bool startsWith(const string &prefix) const
    {
        TrieNode *node = root;
        for (char c : prefix)
        {
            int idx = c - 'a';
            if (!node->children[idx])
                return false;
            node = node->children[idx];
        }
        return true;
    }

    void clear()
    {
        poolIndex = 0;
        root = newNode();
    }
};

Trie trie;
int main()
{
    trie.insert("apple");
    cout << trie.search("apple") << endl;   // true
    cout << trie.search("app") << endl;     // false
    cout << trie.startsWith("app") << endl; // true
    trie.insert("app");
    cout << trie.search("app") << endl; // true
}
