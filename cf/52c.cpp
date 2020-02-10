//
// Created by vtta 🍉 on 2020/2/10.
//
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
typedef long long i64;
struct Solution {
    int n, h, m;
    vector<i64> tree, lazy;

    Solution(int n) : n(n), h(log2(n) + 1), tree(n * 2), lazy(n * 2) {
        for (int i = 0; i < n; ++i) {
            cin >> tree[i + n];
        }
        init();
        cin >> m;
    }

    void init() {
        for (int i = n - 1; i > 0; --i) {
            tree[i] = min(tree[i * 2], tree[i * 2 + 1]);
        }
    }
    void apply(int p, i64 v) {
        tree[p] += v;
        if (p < n) {
            lazy[p] += v;
        }
    }
    void sink(int p) {
        int w = pow(2, h);
        while ((w /= 2) > 1) {
            int i = p / w;
            i64 &x = lazy[i];
            if (x != 0) {
                apply(i * 2, x);
                apply(i * 2 + 1, x);
                x = 0;
            }
        }
    }
    void swim(int p) {
        while ((p /= 2) > 0) {
            tree[p] = min(tree[p * 2], tree[p * 2 + 1]) + lazy[p];
        }
    }
    i64 query(int l, int r) {
        l += n;
        r += n;
        sink(l);
        sink(r - 1);
        i64 res = 0x7fffffffffffffff;
        for (; l < r; l /= 2, r /= 2) {
            if (l & 1) {
                res = min(res, tree[l++]);
            }
            if (r & 1) {
                res = min(tree[--r], res);
            }
        }
        return res;
    }

    void modify(int l, int r, i64 v) {
        l += n;
        r += n;
        for (int i = l, j = r; i < j; i /= 2, j /= 2) {
            if (i & 1) {
                apply(i++, v);
            }
            if (j & 1) {
                apply(--j, v);
            }
        }
        swim(l);
        swim(r - 1);
    }

    void solve() {
        for (int i = 0, l, r, v; i < m; ++i) {
            cin >> l >> r;
            if (cin.peek() == ' ') {
                cin >> v;
                if (l <= r) {
                    modify(l, r + 1, v);
                } else {
                    modify(l, n, v);
                    modify(0, r + 1, v);
                }
            } else {
                if (l <= r) {
                    cout << query(l, r + 1) << endl;
                } else {
                    cout << min(query(l, n), query(0, r + 1)) << endl;
                }
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.precision(20);

    int n;
    while (cin >> n) {
        Solution(n).solve();
    }

    return 0;
}