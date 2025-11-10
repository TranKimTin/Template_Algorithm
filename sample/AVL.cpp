#include <iostream>
#include <algorithm>

#define INF 999999999
#define MAX_NODE 1000005

using namespace std;

struct AVLNode
{
    int value;
    int height;
    int count; // số lượng node có cùng value
    int size;  // tổng số lượng node trong cây con, tính cả count
    int min;
    int max;
    long long sum;
    AVLNode *left;
    AVLNode *right;

    void init(int val)
    {
        value = min = max = sum = val;
        height = count = size = 1;
        left = right = NULL;
    }
};
AVLNode AVLPool[MAX_NODE];
int AVLSizePool;

class AVLTree
{
private:
    AVLNode *root;

    int height(AVLNode *node)
    {
        return node ? node->height : 0;
    }

    int size(AVLNode *node)
    {
        return node ? node->size : 0;
    }

    long long sum(AVLNode *node)
    {
        return node ? node->sum : 0;
    }

    int getMin(AVLNode *node)
    {
        return node ? node->min : INF;
    }

    int getMax(AVLNode *node)
    {
        return node ? node->max : -INF;
    }

    void update(AVLNode *node)
    {
        if (!node)
            return;
        node->height = 1 + max(height(node->left), height(node->right));
        node->size = size(node->left) + size(node->right) + node->count;
        node->sum = sum(node->left) + sum(node->right) + 1LL * node->value * node->count;
        node->min = min(getMin(node->left), node->value);
        node->max = max(getMax(node->right), node->value);
    }

    AVLNode *rotateLeft(AVLNode *y)
    {
        AVLNode *x = y->right;
        AVLNode *T = x->left;
        x->left = y;
        y->right = T;
        update(y);
        update(x);
        return x;
    }

    AVLNode *rotateRight(AVLNode *x)
    {
        AVLNode *y = x->left;
        AVLNode *T = y->right;
        y->right = x;
        x->left = T;
        update(x);
        update(y);
        return y;
    }

    int getBalance(AVLNode *node)
    {
        return node ? height(node->left) - height(node->right) : 0;
    }

    AVLNode *insert(AVLNode *node, int value)
    {
        if (!node)
        {
            // return new AVLNode(value);
            node = AVLPool + AVLSizePool++;
            node->init(value);
            return node;
        }

        if (value == node->value)
        {
            node->count++;
        }
        else if (value < node->value)
        {
            node->left = insert(node->left, value);
        }
        else
        {
            node->right = insert(node->right, value);
        }

        update(node);

        int balance = getBalance(node);

        if (balance > 1 && value < node->left->value)
        {
            return rotateRight(node);
        }

        if (balance < -1 && value > node->right->value)
        {
            return rotateLeft(node);
        }

        if (balance > 1 && value > node->left->value)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && value < node->right->value)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    AVLNode *findMin(AVLNode *node)
    {
        while (node->left)
            node = node->left;
        return node;
    }

    AVLNode *findMax(AVLNode *node)
    {
        while (node->right)
            node = node->right;
        return node;
    }

    AVLNode *erase(AVLNode *node, int value)
    {
        if (!node)
            return NULL;

        if (value == node->value)
        {
            if (node->count > 1)
            {
                node->count--;
            }
            else
            {
                if (!node->left || !node->right)
                {
                    AVLNode *temp = node->left ? node->left : node->right;
                    // delete node;
                    return temp;
                }
                else
                {
                    AVLNode *temp = findMin(node->right);
                    node->value = temp->value;
                    node->count = temp->count;
                    temp->count = 1;
                    node->right = erase(node->right, temp->value);
                }
            }
        }
        else if (value < node->value)
        {
            node->left = erase(node->left, value);
        }
        else
        {
            node->right = erase(node->right, value);
        }

        update(node);

        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0)
        {
            return rotateRight(node);
        }

        if (balance > 1 && getBalance(node->left) < 0)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && getBalance(node->right) <= 0)
        {
            return rotateLeft(node);
        }

        if (balance < -1 && getBalance(node->right) > 0)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void printInOrder(AVLNode *node)
    {
        if (!node)
            return;
        printInOrder(node->left);
        for (int i = 0; i < node->count; i++)
            cout << node->value << " ";
        printInOrder(node->right);
    }

    AVLNode *getByIndex(AVLNode *root, int k)
    {
        if (!root)
            return root;
        int sizeLeft = size(root->left);

        if (k <= sizeLeft)
        {
            return getByIndex(root->left, k);
        }
        else if (k <= sizeLeft + root->count)
        {
            return root;
        }
        else
        {
            return getByIndex(root->right, k - sizeLeft - root->count);
        }
    }

    AVLNode *lowerBound(AVLNode *root, int value)
    {
        if (!root)
            return root;
        if (value == root->value)
            return root;
        if (value < root->value)
        {
            AVLNode *leftLB = lowerBound(root->left, value);
            return leftLB ? leftLB : root;
        }
        else
        {
            return lowerBound(root->right, value);
        }
    }

    int indexOf(AVLNode *root, int value)
    {
        if (!root)
            return 0;
        if (value == root->value)
        {
            return size(root->left) + 1;
        }
        else if (value < root->value)
        {
            return indexOf(root->left, value);
        }
        else
        {
            return size(root->left) + root->count + indexOf(root->right, value);
        }
    }

public:
    AVLTree() : root(NULL) {}

    void insert(int value)
    {
        root = insert(root, value);
    }

    void erase(int value)
    {
        root = erase(root, value);
    }

    int getByIndex(int k)
    {
        return getByIndex(root, k)->value;
    }

    int indexOf(int value) // đếm từ 1
    {
        return indexOf(root, value);
    }

    int getMin()
    {
        return findMin(root)->value;
    }

    int getMax()
    {
        return findMax(root)->value;
    }

    AVLNode *lowerBound(int value)
    {
        return lowerBound(root, value);
    }

    void print()
    {
        printInOrder(root);
        cout << endl;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);
    AVLTree tree;

    int n = 10;
    int a[10] = {6, 1, 1, 7, 2, 3, 5, 3, 9, 10};

    for (int i = 0; i < n; i++)
    {
        tree.insert(a[i]);
    }
    tree.print();

    for (int i = 1; i <= n; i++)
    {
        cout << tree.getByIndex(i) << " ";
    }

    cout << endl;
    for (int i = 1; i <= 10; i++)
    {
        cout << "Lower bound of " << i << " is " << tree.lowerBound(i)->value << "\n";
    }

    for (int i = 1; i <= 10; i++)
    {
        cout << "Index of " << i << " is " << tree.indexOf(i) << "\n";
    }
    return 0;
}
