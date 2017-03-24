// UNCOMMENT THE NEXT LINE TO ENABLE THE TESTS AND BEFORE SUBMITTING
//#include "tests.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>


template <typename T>
struct node {
    T value;
    int levels;
    std::vector<node*> next;

    // constructor
    node (T v, int l) : value(v), levels(l) {
        for (int i = 0; i < levels; ++i) {
            next.push_back(nullptr);
        }
    }
};


template<typename T>
class SkipList {
private:
    int max_level;
    node<T>* head_node;
    node<T>* tail_node;

    int random_level() {
        return rand() % max_level + 1;
    }

    int node_level(const std::vector<node<T>*>& v) {
        int current_level = 1;

        for (size_t i = 0; i < v.size(); ++i) {
            if (v[i] != nullptr) {
                ++current_level;
            } else {
                break;
            }
        }

        return current_level;
    }


public:

    // constructor
    SkipList() : max_level(16) {
        head_node = new node<T>(0, max_level);
        tail_node = new node<T>(0, max_level);

        // assign all head pointers to tail
        for (size_t i = 0; i < head_node->next.size(); ++i) {
            head_node->next[i] = tail_node;
        }
    };

    // destructor
    ~SkipList() {
        delete head_node;
        delete tail_node;
    };

    void print() const {
        node<T>* temp = head_node->next[0];

        while (temp->next[0] != nullptr) {
            std::cout << temp->next[0]->value << " ";
            temp = temp->next[0];
        }
        std::cout << std::endl;
    };

    node<T>* find( const T& searchValue ) const {
        node<T>* temp = head_node;

        for (int i = max_level; i-- > 0;) {
            while (temp->next[i] != nullptr && temp->next[i]->value < searchValue) {
                temp = temp->next[i];
            }
        }

        temp = temp->next[0];

        if (temp != nullptr && temp->value == searchValue) {
            return temp;
        } else {
            return nullptr;
        }
    }

    void insert( const T& newValue ) {
        node<T>* temp = nullptr;
        std::vector<node<T>*> update(head_node->next);
        temp = head_node;

        for (int i = head_node->levels; i-- > 0;) {
            while (temp->next[i] != nullptr && temp->next[i]->value < newValue) {
                temp = temp->next[i];
            }
            update[i] = temp;
        }

        temp = temp->next[0];
        int new_level = random_level();
        int update_level = node_level(update);

        if (update_level < new_level) {
            for (int i = update_level + 1; i < new_level; ++i) {
                update[i] = head_node;
            }
        }

        temp = new node<T>(newValue, new_level);

        for (int i = 0; i < new_level; ++i) {
            temp->next[i] = update[i]->next[i];
            update[i]->next[i] = temp;
        }
    };

    void erase( const T& eraseValue ) {
        while(find(eraseValue)) {
            std::vector<node<T>*> update(head_node->next);
            node<T>* temp = head_node;

            for (int i = head_node->levels; i-- > 0;) {
                while (temp->next[i] != nullptr && temp->next[i]->value < eraseValue) {
                    temp = temp->next[i];
                }
                update[i] = temp;
            }

            temp = temp->next[0];

            if (temp->value == eraseValue) {
                for (size_t i = 0; i < update.size(); ++i) {
                    if (update[i]->next[i] != temp) {
                        break;
                    }
                    update[i]->next[i] = temp->next[i];
                }
                delete temp;
            }
        }
    }
};



int main() {

    // Initialize an empty SkipList object
    SkipList<int> s;

    // insert elements
    int input;
    std::cin >> input;
    while (input!=0) {
        s.insert(input);
        std::cin >> input;
    }

    // erase elements
    int erase;
    std::cin >> erase;
    while (erase!=0) {
        s.erase (erase);
        std::cin >> erase;
    }

    s.print();

    return 0;
}
