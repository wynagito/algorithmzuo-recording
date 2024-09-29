// 插入、删除和获取随机元素O(1)时间且允许有重复数字的结构
// 测试链接 : https://leetcode.cn/problems/insert-delete-getrandom-o1-duplicates-allowed/

#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class RandomizedCollection {
public:
    unordered_map<int, unordered_set<int>> idx; // 元素的值 : 在nums中下标的集合
    vector<int> nums;

    /** Initialize your data structure here. */
    RandomizedCollection() {
        idx.clear();
        nums.clear();
    }
    
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        nums.push_back(val);
        idx[val].insert(nums.size() - 1);
        return idx[val].size() == 1;
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        if (idx.find(val) == idx.end()) {
            return false;
        }
        int i = *(idx[val].begin());
        nums[i] = nums.back();
        idx[val].erase(i);
        idx[nums[i]].erase(nums.size() - 1);
        if (i < nums.size() - 1) {
            idx[nums[i]].insert(i);
        }
        if (idx[val].size() == 0) {
            idx.erase(val);
        }
        nums.pop_back();
        return true;
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
        return nums[rand() % nums.size()];
    }
};
