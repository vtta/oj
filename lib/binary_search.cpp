//
// Created by vtta 🍉 on 2020/2/11.
//
#include <cassert>
#include <vector>
using namespace std;
namespace BS {

using u64 = size_t;

u64 lower_bound(vector<int> &nums, int target) {
    u64 n = nums.size(), p = n - 1;
    for (u64 w = n / 2; w > 0; w /= 2) {
        while (p >= w && nums[p - w] >= target) {
            p -= w;
        }
    }
    return p;
}

u64 upper_bound(vector<int> &nums, int target) {
    u64 n = nums.size(), p = 0;
    for (u64 w = n / 2; w > 0; w /= 2) {
        while (p + w < n && nums[p + w] <= target) {
            p += w;
        }
    }
    return p + 1;
}

};  // namespace BS

int main() {
    {
        vector<int> vec{1, 1, 1, 1, 2, 2, 2};
        assert(BS::lower_bound(vec, 2) == 4);
        assert(BS::upper_bound(vec, 2) == 7);
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