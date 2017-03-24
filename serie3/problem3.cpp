// UNCOMMENT THE NEXT LINE TO ENABLE THE TESTS AND BEFORE SUBMITTING
// #include "tests.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>

template <typename ElementType>
class MyVector {
private:
    size_t elem_size;
    size_t elem_capacity;
    ElementType* elem;

    // helper function
    void swap (MyVector& v) {
        std::swap(elem_size, v.elem_size);
        std::swap(elem_capacity, v.elem_capacity);
        std::swap(elem, v.elem);
    }

public:
    // constructor
    MyVector(): elem_size(0), elem_capacity(0), elem(nullptr) {};
    MyVector(size_t s): elem_size(0), elem_capacity(s), elem(new ElementType[s]) {};

    // desctructor
    ~MyVector() {
        delete[] elem;
    }

    // copy constructor
    MyVector (const MyVector &v) : elem_size(v.elem_size), elem_capacity(v.elem_capacity), elem(new ElementType[v.elem_capacity]) {
        std::copy(v.elem, v.elem + v.elem_size, elem);
    }

    // assignment operator
    MyVector& operator= (const MyVector& v) {
        MyVector cpy(v);
        swap(cpy);
        return *this;
    }

    size_t size() const {
        return elem_size;
    }

    size_t capacity() const {
        return elem_capacity;
    }

    bool empty() const {
        return elem_size == 0;
    }

    void push_back(ElementType el) {
        // double elem_capacity if array is full
        if (elem_size == elem_capacity) {

            elem_capacity = (elem_capacity > size_t(0)) ? elem_capacity * 2 : size_t(1);
            ElementType* temp = new ElementType[elem_capacity];
            std::copy(elem, elem + elem_size, temp);
            std::swap(elem, temp);
        }

        elem[elem_size++] = el;
    }

    ElementType& back() const {
        return elem[elem_size - 1];
    }

    void pop_back() {
        if (--elem_size < elem_capacity / 2) {
            elem_capacity /= 2;
            ElementType* temp = new ElementType[elem_capacity];
            std::copy(elem, elem + elem_size, temp);
            std::swap(elem, temp);
        }
    }

    void clear() {
        elem_size = size_t(0);
        elem_capacity = size_t(0);
        ElementType* temp = new ElementType[elem_capacity];
        std::swap(elem, temp);
    }

    // for const objects
    ElementType operator[] (size_t pos) const {
        return elem[pos];
    }

    // for non-const objects
    ElementType& operator[] (size_t pos) {
        return elem[pos];
    }

    ElementType* begin() const {
        return elem;
    }

    ElementType* end() const {
        return elem + elem_size;
    }

    void print_all() const {
        for (auto it = this->begin(); it != this->begin() + elem_capacity; ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }

    void print() const {
        for (auto it = this->begin(); it != this->end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
};

template <typename Container>
void insertionSort (Container& c, int skip_param = 1) {
    for (int i = 0; i <= c.size() - 1; i += skip_param) {
        for (int j = i-1; j >= 0 && c[j] > c[j + skip_param]; j -= skip_param)
            std::swap(c[j], c[j + skip_param]);
    }
}

template <typename Container>
void shellSort (Container& c) {
    int skip_param = c.size();
    while (skip_param / 2 > 0) {
        skip_param /= 2;
        insertionSort(c, skip_param);
    }
}


int main() {

    std::string filename = "test.txt";
    std::ifstream in(filename.c_str());


    MyVector<int> myvec;

    // read in vector until 0 appears (exclusive)
    int e;
    in >> e;

    while(e != 0) {
        myvec.push_back(e);
        in >> e;
    }

    myvec.print();
    myvec.print_all();

    // sort vector
    shellSort(myvec);

    // output vector
    for(auto x:myvec) {
        std::cout << x << " ";
    }

    return 0;
}
