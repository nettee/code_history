#include <iostream>
#include <cassert>

template <typename T>
struct ThreadTreeNode {
    T val;
    ThreadTreeNode *left, *right;
    unsigned char ltag, rtag;
    ThreadTreeNode(T x) {
        val = x;
        left = NULL;
        right = NULL;
        ltag = 0;
        rtag = 0;
    }
};

template <typename T>
class ThreadTree {
public:
    ThreadTree() { root = NULL; }
    ~ThreadTree() { return; }

    void in_thread();
    void inorder();
    ThreadTreeNode<T> *first(ThreadTreeNode<T> *);
    ThreadTreeNode<T> *last(ThreadTreeNode<T> *);
    ThreadTreeNode<T> *next(ThreadTreeNode<T> *);
    ThreadTreeNode<T> *prior(ThreadTreeNode<T> *);

    void input(T *v, int len) {
        assert(len > 0);
        root = input_subtree(1, v, len);
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
    ThreadTreeNode<T> *root;

    void clear_(ThreadTreeNode<T> *subtree);

    void in_thread_(ThreadTreeNode<T> *current, ThreadTreeNode<T> *&pre);

    ThreadTreeNode<T> *input_subtree(int, T *, int);

    void preorder_(ThreadTreeNode<T> *subtree);
    void inorder_(ThreadTreeNode<T> *subtree);
    void postorder_(ThreadTreeNode<T> *subtree);
};

template <typename T>
void ThreadTree<T>::in_thread()
{
    ThreadTreeNode<T> *pre = NULL;
    if (root != NULL) {
        in_thread_(root, pre);
        pre->right = NULL;
        pre->rtag = 1;
    }
}

template <typename T>
void ThreadTree<T>::in_thread_(ThreadTreeNode<T> *current, ThreadTreeNode<T> *&pre)
{
    if (current == NULL) {
        return;
    }
    in_thread_(current->left, pre);
    if (current->left == NULL) {
        current->left = pre;
        current->ltag = 1;
    }
    if (pre != NULL && pre->right == NULL) {
        pre->right = current;
        pre->rtag = 1;
    }
    pre = current;
    in_thread_(current->right, pre);
}

template <typename T>
ThreadTreeNode<T> *ThreadTree<T>::first(ThreadTreeNode<T> *q)
{
    while (q->ltag == 0) {
        q = q->left;
    }
    return q;
}

template <typename T>
ThreadTreeNode<T> *ThreadTree<T>::last(ThreadTreeNode<T> *q)
{
    while (q->rtag == 0) {
        q = q->right;
    }
    return q;
}

template <typename T>
ThreadTreeNode<T> *ThreadTree<T>::next(ThreadTreeNode<T> *q)
{
    if (q->rtag == 0) {
        return first(q->right);
    } else {
        return q->right;
    }
}

template <typename T>
ThreadTreeNode<T> *ThreadTree<T>::prior(ThreadTreeNode<T> *q)
{
    if (q->ltag == 0) {
        return last(q->left);
    } else {
        return q->left;
    }
}

template <typename T>
void ThreadTree<T>::inorder()
{
    std::cout << "///// ";
    ThreadTreeNode<T> *q;
    for (q = first(root); q != NULL; q = next(q)) {
        std::cout << q->val << " ";
    }
    std::cout << std::endl;
}

template <typename T>
ThreadTreeNode<T> *ThreadTree<T>::input_subtree(int num, T *v, int len)
{
    if (num > len) {
        return NULL;
    }
    T val = v[num - 1];
    if (val == '*') {
        return NULL;
    }
    ThreadTreeNode<T> *np = new ThreadTreeNode<T>(val);
    np->left = input_subtree(num * 2, v, len);
    np->right = input_subtree(num * 2 + 1, v, len);
    return np;
}
    
template <typename T>
void ThreadTree<T>::preorder_(ThreadTreeNode<T> *tree)
{
    if (tree == NULL) {
        return;
    }
    std::cout << tree->val << " ";
    preorder_(tree->left);
    preorder_(tree->right);
}

template <typename T>
void ThreadTree<T>::inorder_(ThreadTreeNode<T> *tree)
{
    if (tree == NULL) {
        return;
    }
    inorder_(tree->left);
    std::cout << tree->val << " ";
    inorder_(tree->right);
}

template <typename T>
void ThreadTree<T>::postorder_(ThreadTreeNode<T> *tree)
{
    if (tree == NULL) {
        return;
    }
    postorder_(tree->left);
    postorder_(tree->right);
    std::cout << tree->val << " ";
}
