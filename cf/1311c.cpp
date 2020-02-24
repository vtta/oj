#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;
typedef long long i64;
struct Solution {
    int n, m;
    vector<int> p, t, x;
    string s;

    Solution(int n, int m) : n(n), m(m), p(m), t(26), x(n) {
        cin >> s;
        for (int i = 0; i < m; ++i) {
            cin >> p[i];
        }
        // 2 8 3 2 9
        // 0 1
        // 0 1 2 3 4 5 6 7
        // 0 1 2
        // 0 1
        // 0 1 2 3 4 5 6 7 8 9
        // 2 2 3 8 9
        // 0 -> 5 sz - ub
        // 1 -> 5 sz - ub
        // 2 -> 3 sz - ub
        // 3 -> 2
        // ...
        // 7 -> 2
        // 8 -> 1
        // 9 -> 0
    }

    void solve() {
        sort(begin(p), end(p));
        for (int i = 0; i < n; ++i) {
            x[i] = distance(upper_bound(begin(p), end(p), i), end(p)) + 1;
        }
        for (int i = 0; i < n; ++i) {
            t[s[i] - 'a'] += x[i];
        }
        for (auto const &i : t) {
            cout << i << " ";
        }
        cout << endl;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.precision(20);

    int T;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        int n, m;
        cin >> n >> m;
        Solution(n, m).solve();
    }

    return 0;
}