// https://vjudge.net/problem/POJ-2485
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

const int INF = numeric_limits<int>::max();

struct Solution {
    int n;
    vector<vector<int> > g;
    vector<int> mst, key, parent;

    Solution(int n) : n(n), g(n), mst(n, 0), key(n, INF), parent(n, -1) {
        for (int i = 0; i < n; ++i) {
            g[i].resize(n);
            for (int j = 0; j < n; ++j) {
                cin >> g[i][j];
            }
        }
    }
    void solve() {
        prim();

        int longest = -INF;
        for (int i = 1; i < n; ++i) {
            longest = max(longest, g[parent[i]][i]);
        }
        cout << longest << endl;
    }
    int prim() {
        // vertex 0 will be the root
        key[0] = 0;
        // n - 1 vertices left to expand to
        for (int i = 1; i < n; ++i) {
            int u = min_key_idx();
            mst[u] = 1;
            for (int v = 0; v < n; ++v) {
                if (mst[v] == 0 && g[u][v] != 0 && g[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = g[u][v];
                }
            }
        }
        return 0;
    }
    int min_key_idx() {
        int min = INF, idx;
        for (int i = 0; i < n; ++i) {
            if (mst[i] == 0 && key[i] < min) {
                min = key[i];
                idx = i;
            }
        }
        return idx;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        int n;
        cin >> n;
        Solution(n).solve();
    }
}
