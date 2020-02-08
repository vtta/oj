//
// Created by vtta 🍉 on 2020/2/8.
//
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Solution {
    int n, m;
    vector<int> tree;

    Solution(int n) : n(n), tree(2 * n) {
        cin >> m;
        for (int i = 0; i < n; ++i) {
            cin >> tree[i + n];
        }
        build();
    }

    void solve() {
        for (int i = 0, a, b; i < m; ++i) {
            char c;
            cin >> c >> a >> b;
            if (c == 'Q') {
                cout << query(a - 1, b) << endl;
            } else {
                update(a - 1, b);
            }
        }
    }

    void build() {
        for (int i = n - 1; i > 0; --i) {
            tree[i] = max(tree[i * 2], tree[i * 2 + 1]);
        }
    }

    void update(int p, int v) {
        for (tree[p += n] = v; p > 1; p /= 2) {
            tree[p / 2] = max(tree[p], tree[p ^ 1]);
        }
    }

    int query(int l, int r) {
        int res = 0;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1) {
                res = max(tree[l++], res);
            }
            if (r & 1) {
                res = max(res, tree[--r]);
            }
        }
        return res;
    }
};

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.precision(20);
    int n;
    while (cin >> n) {
        Solution(n).solve();
    }
    return 0;
}