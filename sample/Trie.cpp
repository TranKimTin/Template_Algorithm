#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int ALPHABET_SIZE = 26;

struct TrieNode
{
    TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;

    void init()
    {
        for (int i = 0; i < ALPHABET_SIZE; ++i)
            children[i] = nullptr;
        isEndOfWord = false;
    }
};
class Trie
{
    // Memory pool
    vector<TrieNode> pool;
    int poolIndex = 0;

    TrieNode *newNode()
    {
        if (poolIndex >= pool.size())
        {
            cerr << "Pool exhausted!" << endl;
            exit(1);
        }
        pool[poolIndex].init();
        return &pool[poolIndex++];
    }

    TrieNode *root;

public:
    Trie(int maxNodes = 100000)
    {
        pool.resize(maxNodes); // cấp trước bộ nhớ cho tất cả nodes
        poolIndex = 0;
        root = newNode(); // node gốc
    }

    void insert(const string &key)
    {
        TrieNode *node = root;
        for (char c : key)
        {
            int index = c - 'a';
            if (!node->children[index])
                node->children[index] = newNode();
            node = node->children[index];
        }
        node->isEndOfWord = true;
    }

    bool search(const string &key)
    {
        TrieNode *node = root;
        for (char c : key)
        {
            int index = c - 'a';
            if (!node->children[index])
                return false;
            node = node->children[index];
        }
        return node->isEndOfWord;
    }
};

int main()
{
    Trie trie;

    trie.insert("hello");
    trie.insert("world");

    cout << trie.search("hello") << "\n"; // 1
    cout << trie.search("world") << "\n"; // 1
    cout << trie.search("hell") << "\n";  // 0
}
