// 给你一个整数数组 nums ，其中可能包含重复元素，请你返回该数组所有可能的组合
// 答案 不能 包含重复的组合。返回的答案中，组合可以按 任意顺序 排列
// 注意其实要求返回的不是子集，因为子集一定是不包含相同元素的，要返回的其实是不重复的组合
// 比如输入：nums = [1,2,2]
// 输出：[[],[1],[1,2],[1,2,2],[2],[2,2]]
// 测试链接 : https://leetcode.cn/problems/subsets-ii/

#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    vector<vector<int>> subsetsWithDup(vector<int> &nums)
    {
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());
        vector<int> path(nums.size());
        f(nums, 0, path, 0, ans);
        return ans;
    }

    // i: 当前处理的位置
    // path: 当前组合
    // size: 当前组合的长度
    // ans: 结果集
    void f(vector<int> &nums, int i, vector<int> &path, int size, vector<vector<int>> &ans)
    {
        if (i == nums.size())
        {
            vector<int> cur(path.begin(), path.begin() + size);
            ans.push_back(cur);
        }
        else
        {
            // 下一组的第一个数的位置
            int j = i + 1;
            while (j < nums.size() && nums[i] == nums[j])
            {
                j++;
            }
            // 当前数x，要0个
            f(nums, j, path, size, ans);
            // 当前数x，要1个、要2个、要3个...都尝试
            for (; i < j; i++)
            {
                path[size++] = nums[i];
                f(nums, j, path, size, ans);
            }
        }
    }
};
