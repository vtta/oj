//
// Created by vtta 🍉 on 2020/2/11.
//
#include <cassert>
#include <vector>
using namespace std;
namespace BS {

using u64 = size_t;

u64 lower_bound(vector<int> &nums, int target) {
    auto ok = [&](u64 m) { return nums[m] < target; };
    u64 l = 0, r = nums.size();
    while (l < r) {
        u64 m = l + (r - l) / 2;
        if (ok(m)) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    return l;
}

u64 upper_bound(vector<int> &nums, int target) {
    auto ok = [&](u64 m) { return nums[m] > target; };
    u64 l = 0, r = nums.size();
    while (l < r) {
        u64 m = l + (r - l) / 2;
        if (!ok(m)) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    return l;
}

};  // namespace BS

int main() {
    {
        vector<int> vec{1, 1, 1, 1, 3, 3, 3};
        assert(BS::lower_bound(vec, 3) == 4);
        assert(BS::upper_bound(vec, 3) == 7);
        assert(BS::lower_bound(vec, 2) == 4);
        assert(BS::upper_bound(vec, 2) == 4);
        assert(BS::lower_bound(vec, 4) == 7);
        assert(BS::upper_bound(vec, 4) == 7);
    }
    {
        vector<int> vec{0, 1, 2, 3, 4, 5, 6, 7};
        for (auto i = 0UL; i < vec.size(); ++i) {
            assert(BS::lower_bound(vec, vec[i]) == i);
            assert(BS::upper_bound(vec, vec[i]) == i + 1);
        }
    }
    {
        vector<int> vec{0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7};
        for (auto i = 0UL; i < vec.size(); ++i) {
            assert(BS::lower_bound(vec, vec[i]) == i - i % 2);
            assert(BS::upper_bound(vec, vec[i]) == i + 2 - i % 2);
        }
    }
    return 0;
}