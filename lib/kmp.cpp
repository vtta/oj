#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>
using namespace std;
int kmp(string const &s, string const &p) {
    auto ns = s.size(), np = p.size();
    if (np == 0) {
        return 0;
    }
    if (ns < np || ns == 0) {
        return -1;
    }

    vector<size_t> next(np);
    auto cur = 1ul, prev = 0ul;
    while (cur < np) {
        if (p[cur] == p[prev]) {
            // sotre the prefix length which is index + 1
            next[cur] = prev + 1;
            // move on to next char
            ++cur, ++prev;
        } else if (prev > 0) {
            // still possible to find the prefix of the prefix
            prev = next[prev - 1];
        } else {
            next[cur] = 0;
            ++cur;
        }
    }

    auto i = 0ul, j = 0ul;
    while (i < ns && j < np) {
        if (s[i] == p[j]) {
            ++i, ++j;
        } else if (j > 0) {
            j = next[j - 1];
        } else {
            ++i;
        }
    }

    return i - j > ns - np ? -1 : i - j;
}

int main() {
    string s, p;
    cin >> s >> p;
    cout << kmp(s, p) << endl;
    return 0;
}