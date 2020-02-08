//
// Created by vtta 🍉 on 2020/2/8.
//
#include <iostream>
#include <vector>
using namespace std;

struct Solution {
    int n;
    vector<int> tree;

    Solution(int n) : n(n), tree(2 * n, 0) {
        for (int i = 0; i < n; ++i) {
            cin >> tree[i + n];
        }
        build();
    }

    void solve() {
        string cmd;
        int i, j;
        while (true) {
            cin >> cmd;
            if (cmd[0] == 'E') {
                break;
            }
            cin >> i >> j;
            switch (cmd[0]) {
                case 'A':
                    update(i - 1, +j);
                    break;
                case 'S':
                    update(i - 1, -j);
                    break;
                case 'Q':
                    cout << query(i - 1, j) << endl;
                    break;
            }
        }
    }

    void build() {
        for (int i = n - 1; i > 0; --i) {
            tree[i] = tree[2 * i] + tree[2 * i + 1];
        }
    }
    void update(int pos, int delta) {
        for (tree[pos += n] += delta; pos > 1; pos /= 2) {
            tree[pos / 2] = tree[pos] + tree[pos ^ 1];
        }
    }
    int query(int l, int r) {
        int res = 0;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1) {
                res += tree[l++];
            }
            if (r & 1) {
                res += tree[--r];
            }
        }
        return res;
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
        cout << "Case " << i + 1 << ":" << endl;
        Solution(n).solve();
    }
    return 0;
}