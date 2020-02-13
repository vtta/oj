//
// Created by vtta 🍉 on 2020/2/12.
//
#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
struct Solution {
    i64 n, m, g, b;

    Solution(int n) : n(n), m((n + 1) / 2) { cin >> g >> b; }

    void solve() {
        i64 cycle = (m + g - 1) / g;
        i64 res = (cycle - 1) * b + m;
        cout << max(res, n) << '\n';
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
        Solution(n).solve();
    }

    return 0;
}