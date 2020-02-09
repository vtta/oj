//
// Created by vtta 🍉 on 2020/2/8.
//
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
    int n, m;
    struct Node {
        int lo, hi, val, lazy;
        void calc(int v) {
            lazy = v;
            val = lazy * (hi - lo);
        }
    };
    std::vector<Node> nodes;

    void init(int i, int l, int r) {
        nodes[i].lo = l;
        nodes[i].hi = r;
        if (r - l <= 1) {
            return;
        }
        int m = (l + r) / 2;
        init(i * 2, l, m);
        init(i * 2 + 1, m, r);
    }
    void update(int i, int l, int r, int v) {
        Node &x = nodes[i];
        if (r <= x.lo || l >= x.hi) {
            return;
        }
        if (l <= x.lo && x.hi <= r) {
            x.calc(v);
            return;
        }
        prop(i);
        update(i * 2, l, r, v);
        update(i * 2 + 1, l, r, v);
        calc(i);
    }
    int query(int i, int l, int r) {
        Node &x = nodes[i];
        if (r <= x.lo || l >= x.hi) {
            return 0;
        }
        if (l <= x.lo && x.hi <= r) {
            return x.val;
        }
        prop(i);
        int ll = query(i * 2, l, r);
        int rr = query(i * 2 + 1, l, r);
        calc(i);
        return ll + rr;
    }
    void prop(int i) {
        Node &x = nodes[i];
        if (x.lazy != 0) {
            nodes[i * 2].calc(x.lazy);
            nodes[i * 2 + 1].calc(x.lazy);
            x.lazy = 0;
        }
    }
    void calc(int i) { nodes[i].val = nodes[i * 2].val + nodes[i * 2 + 1].val; }

public:
    SegmentTree(int n) : n(n), m(4 * n + 1), nodes(m) { init(1, 0, n); }

    void update(int l, int r, int v) { update(1, l, r, v); }
    int query(int l, int r) { return query(1, l, r); }
};

struct Solution {
    int n;
    SegmentTree tree;

    Solution(int n) : n(n), tree(n) { tree.update(0, n, 1); }

    void solve() {
        int q;
        cin >> q;
        for (int i = 0, x, y, z; i < q; ++i) {
            cin >> x >> y >> z;
            tree.update(x - 1, y, z);
        }
        cout << "The total value of the hook is " << tree.query(0, n) << "."
             << endl;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.precision(20);
    int T;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        int n;
        cin >> n;
        cout << "Case " << i + 1 << ": ";
        Solution(n).solve();
    }
    return 0;
}