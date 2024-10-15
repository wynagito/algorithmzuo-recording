// 返回无序数组中累加和为给定值的子数组个数
// 测试链接 : https://leetcode.cn/problems/subarray-sum-equals-k/

class Solution
{
public:
    int subarraySum(vector<int> &nums, int k)
    {
        unordered_map<int, int> mp;
        // 0这个前缀和，在没有任何数字的时候，已经有1次了
        mp[0] = 1; // 方案数
        long long sum = 0;
        int res = 0;
        for (auto t : nums)
        {
            sum += t;
            if (mp[sum - k])
                res += mp[sum - k];
            mp[sum]++;
        }
        return res;
    }
};