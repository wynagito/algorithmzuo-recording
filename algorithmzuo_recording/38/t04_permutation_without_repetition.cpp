// 有重复项数组的去重全排列
// 测试链接 : https://leetcode.cn/problems/permutations-ii/

#include <vector>
#include <unordered_set>

using namespace std;

class Solution
{
public:
    vector<vector<int>> permuteUnique(vector<int> &nums)
    {
        vector<vector<int>> ans;
        f(nums, 0, ans);
        return ans;
    }

    void f(vector<int> &nums, int i, vector<vector<int>> &ans)
    {
        if (i == nums.size())
        {
            ans.push_back(nums);
        }
        else
        {
            unordered_set<int> s;
            for (int j = i; j < nums.size(); j++)
            {
                // nums[j]没有来到过i位置，才会去尝试
                if (s.count(nums[j]))
                    continue;
                s.insert(nums[j]);
                swap(nums[i], nums[j]);
                f(nums, i + 1, ans);
                swap(nums[i], nums[j]); // 重要，确保下次迭代可以恢复原数组
            }
        }
    }
};