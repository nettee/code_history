#include <iostream>
#include <cassert>

int max(int x, int y)
{
    return (x > y) ? x : y;
}

int max(int x, int y, int z)
{
    if (x > y) {
        if (x > z) {
            return x;
        } else {
            return z;
        }
    } else {
        if (y > z) {
            return y;
        } else {
            return z;
        }
    }
}

template <typename T>
struct BinTreeNode {
    T val;
    BinTreeNode *left;
    BinTreeNode *right;
    BinTreeNode(T x) {
        val = x;
        left = NULL;
        right = NULL;
    }
};

template <typename T>
class BinTree {
public:
    BinTree();
    BinTree(BinTree<T>& tree);
    ~BinTree();

    bool empty();
    void clear() {
        clear_(root);
    }

    int height();
    int max_path_length();

    void input(T *v, int len) {
        assert(len > 0);
        root = input_subtree(1, v, len);
    }
    void output() { 
        output_(root); 
        std::cout << std::endl;
    }

    void preorder_traversal() {
        std::cout << " pre: ";
        preorder_(root);
        std::cout << std::endl;
    }
    void inorder_traversal() {
        std::cout << "  in: ";
        inorder_(root);
        std::cout << std::endl;
    }
    void postorder_traversal() {
        std::cout << "post: ";
        postorder_(root);
        std::cout << std::endl;
    }

private:
    BinTreeNode<T> *root;

    void clear_(BinTreeNode<T> *subtree);
    int height_(BinTreeNode<T> *subtree);
    int max_path_length_(BinTreeNode<T> *subtree);

    BinTreeNode<T> *input_subtree(int, T *, int);
    void output_(BinTreeNode<T> *tree);

    void preorder_(BinTreeNode<T> *subtree);
    void inorder_(BinTreeNode<T> *subtree);
    void postorder_(BinTreeNode<T> *subtree);
};

template <typename T>
BinTree<T>::BinTree()
{
    root = NULL;
}

template <typename T>
BinTree<T>::~BinTree()
{
    clear();
}

template <typename T>
void BinTree<T>::clear_(BinTreeNode<T> *tree)
{
    if (tree == NULL) {
        return;
    }
    clear_(tree->left);
    clear_(tree->right);
    delete tree;
}

template <typename T>
int BinTree<T>::height()
{
    return height_(root);
}

template <typename T>
int BinTree<T>::height_(BinTreeNode<T> *tree)
{
    if (tree == NULL) {
        return 0;
    } else {
        return 1 + max(height_(tree->left), height_(tree->right));
    }
}

template <typename T>
int BinTree<T>::max_path_length()
{
    return max_path_length_(root);
}

template <typename T>
int BinTree<T>::max_path_length_(BinTreeNode<T> *tree)
{
    if (tree == NULL) {
        return 0;
    } 
    int left_height = tree->left ? height_(tree->left) : 0;
    int right_height = tree->right ? height_(tree->right) : 0;
    if (tree->left == NULL && tree->right == NULL) {
        return 0;
    } else if (tree->left == NULL && tree->right != NULL) {
        return max(right_height, max_path_length_(tree->right));
    } else if (tree->left != NULL && tree->right == NULL) {
        return max(left_height, max_path_length_(tree->left));
    } else {
        return max(left_height + right_height, 
                max_path_length_(tree->left),
                max_path_length_(tree->right));
    }
}

template <typename T>
BinTreeNode<T> *BinTree<T>::input_subtree(int num, T *v, int len)
{
    if (num > len) {
        return NULL;
    }
    T val = v[num - 1];
    if (val == '*') {
        return NULL;
    }
    BinTreeNode<T> *np = new BinTreeNode<T>(val);
    np->left = input_subtree(num * 2, v, len);
    np->right = input_subtree(num * 2 + 1, v, len);
    return np;
}

template <typename T>
void BinTree<T>::output_(BinTreeNode<T> *t)
{
    if (t == NULL) {
        return;
    }
    if (t->left == NULL && t->right == NULL) {
        std::cout << t->val;
    } else {
        std::cout << "(";
        std::cout << t->val;
        if (t->left) {
            std::cout << " ";
            output_(t->left);
        }
        if (t->right) {
            std::cout << " ";
            output_(t->right);
        }
        std::cout << ")";
    }
}
    
template <typename T>
void BinTree<T>::preorder_(BinTreeNode<T> *tree)
{
    if (tree == NULL) {
        return;
    }
    std::cout << tree->val << " ";
    preorder_(tree->left);
    preorder_(tree->right);
}

template <typename T>
void BinTree<T>::inorder_(BinTreeNode<T> *tree)
{
    if (tree == NULL) {
        return;
    }
    inorder_(tree->left);
    std::cout << tree->val << " ";
    inorder_(tree->right);
}

template <typename T>
void BinTree<T>::postorder_(BinTreeNode<T> *tree)
{
    if (tree == NULL) {
        return;
    }
    postorder_(tree->left);
    postorder_(tree->right);
    std::cout << tree->val << " ";
}
