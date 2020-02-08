//
// Created by vtta 🍉 on 2020/2/8.
//
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Solution {
    int n, m;
    vector<int> w, f;

    Solution(int n) : n(n), m(n * 2 + 1), w(m), f(m * m) {
        for (int i = 0; i < n; ++i) {
            cin >> w[i];
            w[i + n] = w[i];
        }
        w[m - 1] = w[0];
    }

    void solve() {
        int res = 0;
        for (int i = 0; i < n; ++i) {
            res = max(res, dp(i, i + n));
        }
        cout << res << endl;
    }

    int dp(int i, int j) {
        int &res = f[i * m + j];
        if (res != 0) {
            return res;
        }
        for (int k = i + 1; k < j; ++k) {
            res = max(res, dp(i, k) + dp(k, j) + w[i] * w[k] * w[j]);
        }
        return res;
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