#include <cmath>
#include <functional>
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;
typedef long long i64;
struct Solution {
    int n, m;
    vector<int> a;
    vector<bool> ok;

    Solution(int n, int m) : n(n), m(m), a(n), ok(n, false) {
        for (auto &i : a) {
            cin >> i;
        }
        for (int i = 0; i < m; i += 1) {
            int t;
            cin >> t;
            ok[t] = true;
        }
    }

    void solve() {
        for (int i = n; i > 0; --i) {
            for (int j = 1; j < i; ++j) {
                if (a[j - 1] > a[j]) {
                    if (ok[j]) {
                        swap(a[j - 1], a[j]);
                    }
                }
            }
        }
        bool sorted = true;
        for (int i = 1; i < n; ++i) {
            if (a[i - 1] > a[i]) {
                sorted = false;
                break;
            }
        }
        cout << (sorted ? "YES" : "NO") << endl;
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