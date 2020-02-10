//
// Created by vtta 🍉 on 2020/2/9.
//
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

typedef long long i64;

struct Solution1 {
    int n, h, q;
    vector<i64> tree, lazy, len;

    Solution1(int n) : n(n), h(log2(n) + 1), tree(2 * n), lazy(n), len(2 * n) {
        cin >> q;
        for (int i = 0; i < n; ++i) {
            cin >> tree[i + n];
            len[i + n] = 1;
        }
        init();
    }

    void init() {
        for (int i = n - 1; i > 0; --i) {
            tree[i] = tree[i * 2] + tree[i * 2 + 1];
            len[i] = len[i * 2] + len[i * 2 + 1];
        }
    }
    void apply(int p, i64 x) {
        tree[p] += len[p] * x;
        if (p < n) {
            lazy[p] += x;
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
            tree[p] = tree[p * 2] + tree[p * 2 + 1] + lazy[p] * len[p];
        }
    }
    void update(int l, int r, i64 x) {
        l += n;
        r += n;
        int l0 = l, r0 = r;
        for (; l < r; l /= 2, r /= 2) {
            if (l & 1) {
                apply(l++, x);
            }
            if (r & 1) {
                apply(--r, x);
            }
        }
        swim(l0);
        swim(r0 - 1);
    }
    i64 query(int l, int r) {
        l += n;
        r += n;
        sink(l);
        sink(r - 1);
        i64 res = 0;
        for (; l < r; l /= 2, r /= 2) {
            if (l & 1) {
                res += tree[l++];
            }
            if (r & 1) {
                res += tree[--r];
            }
        }
        return res;
    }

    void solve() {
        for (int i = 0, a, b, c; i < q; ++i) {
            char cmd;
            cin >> cmd;
            if (cmd == 'Q') {
                cin >> a >> b;
                cout << query(a - 1, b) << endl;
            } else {
                cin >> a >> b >> c;
                update(a - 1, b, c);
            }
        }
    }
};

struct Solution {
    int n, q;
    struct node {
        int low, high;
        i64 val, lazy;
    };
    vector<node> tree;

    Solution(int n) : n(n), tree(4 * n) {
        cin >> q;
        init(0, n);
    }
    void init(int l, int r, int i = 1) {
        node &x = tree[i];
        x.low = l;
        x.high = r;
        if (r - l == 1) {
            cin >> tree[i].val;
            return;
        }
        int m = (l + r) / 2;
        init(l, m, i * 2);
        init(m, r, i * 2 + 1);
        update(i);
    }
    void prop(int i) {
        node &x = tree[i];
        if (x.lazy) {
            node &l = tree[i * 2], &r = tree[i * 2 + 1];
            l.lazy += x.lazy;
            r.lazy += x.lazy;
            l.val += x.lazy * (l.high - l.low);
            r.val += x.lazy * (r.high - r.low);
            x.lazy = 0;
        }
    }
    void update(int i) {
        node &x = tree[i], &l = tree[i * 2], &r = tree[i * 2 + 1];
        x.val = l.val + r.val + x.lazy * (x.high - x.low);
    }
    i64 query(int l, int r, int i = 1) {
        node &x = tree[i];
        if (x.high <= l || r <= x.low) {
            return 0;
        }
        if (l <= x.low && x.high <= r) {
            return x.val;
        }
        prop(i);
        i64 ll = query(l, r, i * 2);
        i64 rr = query(l, r, i * 2 + 1);
        update(i);
        return ll + rr;
    }
    void modify(int l, int r, i64 v, int i = 1) {
        node &x = tree[i];
        if (x.high <= l || r <= x.low) {
            return;
        }
        if (l <= x.low && x.high <= r) {
            x.lazy += v;
            x.val += v * (x.high - x.low);
            return;
        }
        prop(i);
        modify(l, r, v, i * 2);
        modify(l, r, v, i * 2 + 1);
        update(i);
    }

    void solve() {
        for (int i = 0, a, b, c; i < q; ++i) {
            char cmd;
            cin >> cmd;
            if (cmd == 'Q') {
                cin >> a >> b;
                cout << query(a - 1, b) << endl;
            } else {
                cin >> a >> b >> c;
                modify(a - 1, b, c);
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
        Solution1(n).solve();
    }

    return 0;
}