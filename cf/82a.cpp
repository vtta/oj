//
// Created by vtta 🍉 on 2020/2/12.
//
#include <bits/stdc++.h>
using namespace std;
typedef long long i64;

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    [](char ch) { return ch != '0'; }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(
        std::find_if(s.rbegin(), s.rend(), [](char ch) { return ch != '0'; })
            .base(),
        s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

struct Solution {
    string str;
    int n;
    vector<int> dp;

    Solution() {
        cin >> str;
        trim(str);
    }

    void solve() {
        bool flag = false;
        auto res = 0UL;
        for (auto i = 0UL; i < str.length(); ++i) {
            if (flag && str[i] == '0') {
                res += 1;
            }
            flag |= str[i] == '1';
        }
        cout << res << '\n';
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