#include <cmath>
#include <functional>
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;
typedef long long i64;
struct Solution {
    int n, m;
    vector<int> a, p;
    unordered_set<int> s;

    Solution(int n, int m) : n(n), m(m), a(n), p(m) {
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        for (int i = 0; i < m; ++i) {
            cin >> p[i];
            s.insert(p[i]);
        }
    }

    void solve() {
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (a[i] > a[j]) {
                    swap(a[i], a[j]);
                    if (s.find(i + 1) == s.end()) {
                        cout << "NO" << endl;
                        return;
                        ;
                    }
                }
            }
        }
        cout << "YES" << endl;
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