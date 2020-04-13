#include <iostream>
#include <string>
#include <vector>
using namespace std;
using u64 = uint64_t;
int main(int argc, char *argv[]) {
    string str;
    cin >> str;
    auto n = str.length();
    vector<u64> x(26);
    vector<vector<u64>> xy(26, x);
    u64 ans = 0;
    for (auto const &i : str) {
        auto ch = i - 'a';
        for (auto j = 0; j < 26; j += 1) {
            xy[ch][j] += x[j];
            ans = max(ans, xy[ch][j]);
        }
        x[ch] += 1;
        ans = max(ans, x[ch]);
    }
    cout << ans << endl;
    return 0;
}
