#ifndef __HASH_MAP_H__
#define __HASH_MAP_H__

#include <iostream>
#include <cassert>

const int table_size = 20;

typedef int K;

enum entry_state { active, empty, deleted };

int hash(K key)
{
    return key % 19;
}

template <typename V>
struct Entry {
    entry_state state;
    K key;
    V value;
};

template <typename V>
class HashMap {
public:
    HashMap() {
        table = new Entry<V>[table_size];
        siz = 0;
        for (int i = 0; i < table_size; i++) {
            table[i].state = empty;
        }
    }

    ~HashMap() {
        delete[] table;
    }

    void clear() {
        siz = 0;
        for (int i = 0; i < table_size; i++) {
            table[i].state = empty;
        }
    }

    bool isEmpty() {
        return siz == 0;
    }

    int size() {
        return siz;
    }

    void put(K key, V value) {
        int h = hash(key);
        int i = h;
        do {
            Entry<V> *en = &table[i];
            if (en->state != active) {
                en->key = key;
                en->value = value;
                en->state = active;
                return;
            } else if (en->key == key) {
                en->value = value;
                return;
            }
            i = (i + 1) % table_size;
        } while (i != h);
        std::cerr << "table full!" << std::endl;
        assert(0);
        ++siz;
    }

    V get(K key) {
        int h = hash(key);
        Entry<V> *en = &table[h];
        if (en->state == empty) {
        }
        int i = h;
        do {
            Entry<V> *en = &table[i];
            if (en->state == empty) {
                return '*';
            } else if (en->key == key) {
                if (en->state == active) {
                    return en->value;
                } else {  // deleted
                    return '*';
                }
            }
            i = (i + 1) % table_size;
        } while (i != h);
        return '*';
    }

    void remove(K key) {
        int h = hash(key);
        int i = h;
        do {
            Entry<V> *en = &table[i];
            if (en->state == empty) {
                return;
            } else if (en->key == key) {
                en->state = deleted;
                return;
            }
            i = (i + 1) % table_size;
        } while (i != h);
    }
        
    void print_table();

private:
    Entry<V> *table;
    int siz;
};

template <typename V>
void HashMap<V>::print_table()
{
    for (int i = 0; i < table_size; i++) {
        std::cout << i << ": ";
        Entry<V> en = table[i];
        if (en.state == empty) {
            std::cout << "(     )";
        } else if (en.state == active) {
            std::cout << "(" << en.key << ", " << en.value << ")";
        } else {
            std::cout << en.key << "(d)";
        }
        if ((i + 1) % 4 == 0) {
            std::cout << std::endl;
        } else {
            std::cout << "\t";
        }
    }
}

#endif
