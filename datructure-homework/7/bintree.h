#include "lstack.h"
#include <iostream>
#include <cassert>

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
    int nodes();

    void input(T *v, int len) {
        assert(len > 0);
        root = input_subtree(1, v, len);
    }
    void output() { 
        output_(root); 
        std::cout << std::endl;
    }

    void preorder_traversal() {
        preorder_(root);
        std::cout << std::endl;
    }
    void inorder_traversal() {
        inorder_(root);
        std::cout << std::endl;
    }
    void postorder_traversal() {
        postorder_(root);
        std::cout << std::endl;
    }
    void print_path() {
        assert(root != NULL);
        lstack<T> s;
        print_path(root, s);
    }

private:
    BinTreeNode<T> *root;

    void clear_(BinTreeNode<T> *subtree);

    BinTreeNode<T> *input_subtree(int, T *, int);
    void output_(BinTreeNode<T> *tree);

    void preorder_(BinTreeNode<T> *subtree);
    void inorder_(BinTreeNode<T> *subtree);
    void postorder_(BinTreeNode<T> *subtree);
    void print_path(BinTreeNode<T> *subtree, lstack<T> &s);
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

template <typename T>
void BinTree<T>::print_path(BinTreeNode<T> *tree, lstack<T> &s)
{
    assert(tree != NULL);
    s.push(tree->val);
    if (tree->left == NULL && tree->right == NULL) {
        std::cout << "Path of leaf " << tree->val << ": ";
        s.output();
    } else {
        if (tree->left)
            print_path(tree->left, s);
        if (tree->right)
            print_path(tree->right, s);
    }
    s.pop();
}

