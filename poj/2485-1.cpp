// https://vjudge.net/problem/POJ-2485
#include <iostream>
#include <limits>
#include <vector>

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
    const_reference peek() { return data[inverse[0]]; }
    size_type peek_key() { return inverse[0]; }
    value_type pop() {
        value_type res(peek());
        remove(inverse[0]);
        return res;
    }
    size_type push(const_reference v) {
        size_type k = data.size();
        insert(k, v);
        return k;
    }
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

    bool less(size_type i, size_type j) {
        return cmp(data[inverse[i]], data[inverse[j]]);
    }
    void exch(size_type i, size_type j) {
        position[inverse[i]] = j;
        position[inverse[j]] = i;
        std::swap(inverse[i], inverse[j]);
    }
    void swim(size_type i) {
        size_type j;
        while (i > 0 && less(i, j = parent(i))) {
            exch(i, j);
            i = j;
        }
    }
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
    void heapify() {
        for (size_type i = size() / 2; i > 0; --i) {
            sink(i - 1);
        }
    }
};

using namespace std;

const int INF = numeric_limits<int>::max();

struct Solution {
    int n;
    vector<vector<int> > g;
    vector<int> mst, parent;
    IndexedHeap<int> heap;

    Solution(int n)
        : n(n), g(n), mst(n, 0), parent(n, -1), heap(vector<int>(n, INF)) {
        for (int i = 0; i < n; ++i) {
            g[i].resize(n);
            for (int j = 0; j < n; ++j) {
                cin >> g[i][j];
            }
        }
    }
    void solve() {
        prim();

        int longest = -INF;
        for (int i = 1; i < n; ++i) {
            longest = max(longest, g[parent[i]][i]);
        }
        cout << longest << endl;
    }
    void prim() {
        heap.update(0, 0);
        // n - 1 vertices left to expand to
        for (int i = 1; i < n; ++i) {
            int u = heap.peek_key();
            heap.pop();
            mst[u] = 1;
            for (int v = 0; v < n; ++v) {
                if (mst[v] == 0 && g[u][v] != 0 && g[u][v] < heap[v]) {
                    parent[v] = u;
                    heap.update(v, min(g[u][v], heap[v]));
                }
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        int n;
        cin >> n;
        Solution(n).solve();
    }
}
