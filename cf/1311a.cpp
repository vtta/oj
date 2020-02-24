#include <functional>
#include <iostream>
using namespace std;
typedef long long i64;
struct Solution {
    int n, a, b;

    Solution(int n = 0) : n(n) { cin >> a >> b; }

    void solve() {
        auto delta = b - a;
        if (delta == 0) {
            cout << 0 << endl;
        } else if (delta > 0) {
            if (delta % 2) {
                cout << 1 << endl;
            } else {
                cout << 2 << endl;
            }
        } else {
            if (delta % 2) {
                cout << 2 << endl;
            } else {
                cout << 1 << endl;
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.precision(20);

    int T;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        Solution().solve();
    }

    return 0;
}
