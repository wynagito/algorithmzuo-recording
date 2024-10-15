// 使数组和能被P整除
// 给你一个正整数数组 nums，请你移除 最短 子数组（可以为 空）
// 使得剩余元素的 和 能被 p 整除。 不允许 将整个数组都移除。
// 请你返回你需要移除的最短子数组的长度，如果无法满足题目要求，返回 -1 。
// 子数组 定义为原数组中连续的一组元素。
// 测试链接 : https://leetcode.cn/problems/make-sum-divisible-by-p/

class Solution
{
public:
    int minSubarray(vector<int> &nums, int p)
    {
        // key : 前缀和%p的余数
        // value : 最晚出现的位置
        unordered_map<int, int> hh;
        hh[0] = -1;
        // 整体余数
        int m = 0;
        for (int a : nums)
        {
            m = (m + a) % p;
        }
        if (!m)
            return 0;
        int ans = INT_MAX;
        for (int i = 0, s = 0; i < nums.size(); ++i)
        {
            // 0...i这部分的余数
            s = (s + nums[i]) % p;
            int f = (s + p - m) % p;
            if (hh.find(f) != hh.end())
            {
                ans = min(ans, i - hh[f]);
            }
            hh[s] = i;
        }
        return ans == nums.size() ? -1 : ans;
    }
};
