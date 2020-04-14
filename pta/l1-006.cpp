#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
using i64 = int64_t;
using u64 = uint64_t;
int main(int argc, char *argv[]) {
    int x;
    cin >> x;
    int n = 13, len = 1, b = x;
    vector<int> fact(n);
    fact[0] = 1;
    for (int i = 1; i < n; i += 1) {
        fact[i] = i * fact[i - 1];
    }
    // len == 1
    for (int i = 2; i <= sqrt(x); i += 1) {
        if (x % i == 0) {
            b = i;
            break;
        }
    }
    // len >= 2
    for (int i = n; i >= 1; i -= 1) {
        for (int j = i + 2; j < n; j += 1) {
            // (i + 1) * (i + 2) * ... * j
            int t = fact[j] / fact[i];
            if (x % t != 0) {
                break;
            }
            if (j - i >= len) {
                len = j - i;
                b = i + 1;
            }
        }
    }
    cout << len << endl << b;
    for (int i = b + 1; i < b + len; i += 1) {
        cout << "*" << i;
    }
    return 0;
}
