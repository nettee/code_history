#ifndef __DISJOINT_SET_H__
#define __DISJOINT_SET_H__

#include <iostream>
#include <cassert>

class DisjointSet {
public:
    DisjointSet(int size) {
        num_set = size;
        sets = new int[num_set];
        for (int i = 0; i < num_set; i++) {
            sets[i] = -1;
        }
    }

    ~DisjointSet() {
        delete[] sets;
    }

    void setUnion(int root1, int root2) {
        assert(root1 != root2);
        sets[root2] = root1;
    }

    int find(int x) {
        if (sets[x] == -1) {   // root
            return x;
        } else {
            return find(sets[x]);
        }
    }

    void print_disjoint_set();

    void output();

private:
    int *sets;
    int num_set;
};

void DisjointSet::print_disjoint_set()
{
    int *roots = new int[num_set];
    int num_disj_set = 0;
    for (int i = 0; i < num_set; i++) {
        if (sets[i] == -1) {
            roots[num_disj_set++] = i;
        }
    }
    for (int i = 0; i < num_disj_set; i++) {
        int root = roots[i];
        std::cout << ((i == 0) ? "{" : ", ");
        int nr_element = 0;
        for (int j = 0; j < num_set; j++) {
            if (find(j) == root) {
                std::cout << ((nr_element++ == 0) ? "{" : ", ");
                std::cout << j;
            }
        }
        std::cout << "}";
    }
    std::cout << "}" << std::endl;
}

void DisjointSet::output()
{
    for (int i = 0; i < num_set; i++) {
        std::cout << ((i == 0) ? "{" : ", ");
        std::cout << sets[i];
    }
    std::cout << "}" << std::endl;
}

#endif
