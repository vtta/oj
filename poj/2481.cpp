// https://vjudge.net/problem/POJ-2481
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Node {
    Node(int s, int e, int i) : s(s), e(e), i(i) {}
    int s, e, i;
    bool operator<(Node const &other) const {
        return e > other.e || (e == other.e && s < other.s);
    }
    bool operator==(Node const &other) const {
        return e == other.e && s == other.s;
    }
    bool operator!=(Node const &other) const { return !(*this == other); }
};

struct Solution {
    int n, maxidx;
    vector<Node> cow;
    vector<int> tree;
    vector<int> res;

    int lowbit(int x) { return x & -x; }
    void update(int idx, int delta) {
        while (idx <= maxidx) {
            tree[idx] += delta;
            idx += lowbit(idx);
        }
    }
    int sum(int idx) {
        int sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= lowbit(idx);
        }
        return sum;
    }

    Solution(int n) : n(n), maxidx(0), cow(), tree(), res() {
        for (int s, e, i = 0; i < n; ++i) {
            cin >> s >> e;
            s += 1;
            e += 1;
            cow.push_back(Node(s, e, i));
            maxidx = max(maxidx, s);
        }
        tree.resize(maxidx + 1);
        res.resize(n);
    }
    void solve() {
        sort(cow.begin(), cow.end());
        Node *prev = &cow.back();
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            Node *cur = &cow[i];
            if (*prev == *cur) {
                cnt += 1;
            } else {
                cnt = 0;
            }
            res[cur->i] = sum(cur->s) - cnt;
            update(cur->s, +1);
            prev = cur;
        }
        for (int i = 0; i < n; ++i) {
            cout << res[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    while (true) {
        int n;
        cin >> n;
        if (n == 0) {
            break;
        } else {
            Solution(n).solve();
        }
    }
    return 0;
}
