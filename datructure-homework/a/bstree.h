#ifndef __BinSearchTree_H__
#define __BinSearchTree_H__

#include <iostream>
#include <cassert>

template <typename E>
struct BinNode {
    E val;
    BinNode *left;
    BinNode *right;
    BinNode(E x) {
        val = x;
        left = NULL;
        right = NULL;
    }
};

template <typename E>
class BinSearchTree {
public:
    BinSearchTree() {
        root = NULL;
    }

    ~BinSearchTree() {
        clear(root);
    }

    void clear() {
        clear(root);
        root = NULL;
    }

    bool empty() {
        return root == NULL;
    }

    void insert(E x) {
        insert(x, root);
    }

    void fromArray(E *arr, int len) {
        clear();
        for (int i = 0; i < len; i++) {
            insert(arr[i]);
        }
    }

    void toArray(E *dest, int len) {
        int n = 0;
        toArray(root, dest, n, len);
    }

private:
    BinNode<E> *root;

    void clear(BinNode<E> *t) {
        if (t == NULL) {
            return;
        }
        clear(t->left);
        clear(t->right);
        delete t;
    }

    void insert(E x, BinNode<E> *&t) {
        if (t == NULL) {
            t = new BinNode<E>(x);
            return;
        }
        if (x < t->val) {
            insert(x, t->left);
        } else if (x > t->val) {
            insert(x, t->right);
        } else {  // duplicate
            ;  // do nothing
        }
    }

    void toArray(BinNode<E> *t, E *dest, int &n, int maxlen) {
        if (t == NULL) {
            return;
        }
        assert(n < maxlen);
        toArray(t->left, dest, n, maxlen);
        dest[n] = t->val;
        n++;
        toArray(t->right, dest, n, maxlen);
    }
};

#endif
