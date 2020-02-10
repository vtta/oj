//
// Created by vtta 🍉 on 2020/2/5.
//
#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>

// key: from outside the heap, if users see the heap as a map
// index: the index in the logical heap, it's inside the implementation
// min heap in c++03 for poj
template <typename T, typename C = std::vector<T>, typename Cmp = std::less<T> >
class IndexedHeap {
public:
    typedef T value_type;
    typedef C container_type;
    typedef Cmp value_compare;
    typedef std::size_t size_type;
    typedef T &reference;
    typedef T const &const_reference;
    typedef T *pointer;
    typedef T const *const_pointer;

    IndexedHeap(container_type const &c = container_type())
        : inf(-1),
          sz(c.size()),
          cmp(),
          data(c),
          position(sz, inf),
          inverse(sz, inf) {
        for (size_type i = 0; i < size(); ++i) {
            position[i] = i;
            inverse[i] = i;
        }
        heapify();
    }
    const_reference at(size_type k) { return data.at(k); }
    const_reference operator[](size_type k) { return data[k]; }
    size_type size() const { return sz; }
    bool empty() const { size() == 0; }
    bool contains(size_type k) const {
        return k < size() && position[k] != inf;
    }
    const_reference top() const { return data[inverse[0]]; }
    size_type top_key() const { return inverse[0]; }
    // O(logn)
    void pop() { remove(top_key()); }
    // O(logn)
    size_type push(const_reference v) {
        size_type k = data.size();
        insert(k, v);
        return k;
    }
    // O(logn)
    void insert(size_type k, const_reference v) {
        if (k >= data.size()) {
            data.resize(k + 1);
        }
        size_type x;
        while (k >= (x = position.size())) {
            position.resize(2 * x + 1, inf);
        }
        while (sz >= (x = inverse.size())) {
            inverse.resize(2 * x + 1, inf);
        }
        data[k] = v;
        position[k] = sz;
        inverse[sz] = k;
        swim(sz);
        sz += 1;
    }
    // O(logn)
    void update(size_type k, const_reference v) {
        size_type i = position[k];
        bool increase = cmp(data[k], v);
        data[k] = v;
        if (increase) {
            sink(i);
        } else {
            swim(i);
        }
    }
    // O(logn)
    void remove(size_type k) {
        size_type i = position[k];
        sz -= 1;
        exch(i, sz);
        swim(i);
        sink(i);
        // data[k] is not actually deleted
        position[k] = inf;
        inverse[sz] = inf;
    }

private:
    const size_type inf;
    size_type sz;
    value_compare cmp;
    container_type data;
    // position map, key -> index
    // which maps a given key to the node position in the heap
    std::vector<size_type> position;
    // inverse map, index -> key
    // which maps the node position in the heap to the key
    std::vector<size_type> inverse;

    static size_type parent(size_type i) { return (i - 1) / 2; }
    static size_type left(size_type i) { return i * 2 + 1; }
    static size_type right(size_type i) { return i * 2 + 2; }

    // O(1)
    bool less(size_type i, size_type j) {
        return cmp(data[inverse[i]], data[inverse[j]]);
    }
    // O(1)
    void exch(size_type i, size_type j) {
        position[inverse[i]] = j;
        position[inverse[j]] = i;
        std::swap(inverse[i], inverse[j]);
    }
    // O(logn)
    void swim(size_type i) {
        size_type j;
        while (i > 0 && less(i, j = parent(i))) {
            exch(i, j);
            i = j;
        }
    }
    // O(logn)
    void sink(size_type i) {
        size_type j;
        while ((j = left(i)) < size()) {
            if (j + 1 < size() && less(j + 1, j)) {
                j += 1;
            }
            if (less(i, j)) {
                break;
            }
            exch(i, j);
            i = j;
        }
    }
    // O(n)
    void heapify() {
        for (size_type i = size() / 2; i > 0; --i) {
            sink(i - 1);
        }
    }
};

void case1() {
    int n = 10e5;
    std::vector<int> vec;
    for (int i = 0; i < n; ++i) {
        vec.push_back(i);
    }
    std::shuffle(vec.begin(), vec.end(), std::mt19937(std::random_device()()));
    IndexedHeap<int> heap(vec);
    for (int i = 0; i < n; ++i) {
        assert(heap[i] == vec[i]);
    }
    for (int i = 0; i < n; ++i) {
        assert(heap.top() == i);
        heap.pop();
    }
}

void case2() {
    std::vector<int> vec{9, 8, 7, 4, 1};
    auto n = vec.size();
    IndexedHeap<int> heap(vec);

    for (auto i = 0U; i < n; ++i) {
        // for (auto const &k : heap.inverse) {
        //     std::cout << heap[k] << " ";
        // }
        // std::cout << std::endl;
        assert(heap.top() == vec.back());
        assert(heap.top_key() == vec.size() - 1);
        heap.pop();
        vec.pop_back();
    }
}

// init
// indx: 0 1 2 3 4
// data: 9 8 7 4 1
// posi: 3 4 2 1 0
// inve: 4 3 2 0 1
// heap: 1 4 7 9 8
//
// pop -> 1
// indx: 0 1 2 3 4
// data: 9 8 7 4 -
// posi: 3 4 2 0 -
// inve: 3 4 2 0 -
// heap: 4 1 8 9

void case3() {
    int n = 10e5;
    std::vector<int> vec;
    for (int i = n; i > 0; --i) {
        vec.push_back(i);
    }
    IndexedHeap<int> heap(vec);
    for (auto i = 0; i < n; ++i) {
        // for (auto const &k : heap.inverse) {
        //     std::cout << heap[k] << " ";
        // }
        // std::cout << std::endl;
        assert(heap.top() == vec.back());
        assert(heap.top_key() == vec.size() - 1);
        heap.pop();
        vec.pop_back();
    }
}

int main() {
    case1();
    case2();
    case3();

    return 0;
}
