//
// Created by vtta 🍉 on 2020/2/7.
//
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
int min(int x, int y) { return x < y ? x : y; }
class SegmentTree {
    int n, m, inv;
    // int (*func)(int, int);
    std::vector<int> lo, hi, val, lazy;

    void update(int i, int l, int r, int v) {
        if (r <= lo[i] || l >= hi[i]) {
            return;
        }
        if (l <= lo[i] && hi[i] <= r) {
            lazy[i] += v;
        }
        prop(i);
        update(i * 2, l, r, v);
        update(i * 2 + 1, l, r, v);
        calc(i);
    }
    void init(int i, int l, int r) {
        lo[i] = l;
        hi[i] = r;
        if (r - l == 1) {
            return;
        }
        int m = (l + r) / 2;
        init(i * 2, l, m);
        init(i * 2, m, r);
    }
    int query(int i, int l, int r) {
        if (r <= lo[i] || l >= hi[i]) {
            return inv;
        }
        if (l <= lo[i] && hi[i] <= r) {
            return val[i] + lazy[i];
        }
        prop(i);
        int ll = query(i * 2, l, r);
        int rr = query(i * 2 + 1, l, r);
        calc(i);
        return std::min(ll, rr);
    }
    void prop(int i) {
        lazy[i * 2] += lazy[i];
        lazy[i * 2 + 1] += lazy[i];
        lazy[i] = 0;
    }
    void calc(int i) { val[i] = std::min(val[i * 2], val[i * 2 + 1]); }

public:
    SegmentTree(int n)
        : n(n), m(4 * n + 1), inv(0x7fffffff), lo(m), hi(m), val(m), lazy(m) {
        init(1, 0, n);
    }

    void update(int l, int r, int v) { update(1, l, r, v); }
    int query(int l, int r) { return query(1, l, r); }
};
