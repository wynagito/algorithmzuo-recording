// 划分为k个相等的子集
// 给定一个整数数组  nums 和一个正整数 k，
// 找出是否有可能把这个数组分成 k 个非空子集，其总和都相等。
// 测试链接 : https://leetcode.cn/problems/partition-to-k-equal-sum-subsets/

class Solution
{
public:
    bool canPartitionKSubsets(vector<int> &nums, int k)
    {
        int sum = 0;
        for (int num : nums)
        {
            sum += num;
        }
        if (sum % k != 0)
        {
            return false;
        }
        int n = nums.size();
        vector<int> dp(1 << n);
        return f(nums, sum / k, (1 << n) - 1, 0, k, dp);
    }
    bool f(vector<int> &nums, int limit, int status, int cur, int rest,
           vector<int> &dp)
    {
        if (rest == 0)
        {
            return status == 0;
        }
        if (dp[status] != 0)
        {
            return dp[status] == 1;
        }
        bool ans = false;
        for (int i = 0; i < nums.size(); i++)
        {
            // 考察每一根火柴，只能使用状态为1的火柴
            if ((status & (1 << i)) != 0 && cur + nums[i] <= limit)
            {
                if (cur + nums[i] == limit)
                {
                    ans = f(nums, limit, status ^ (1 << i), 0, rest - 1, dp);
                }
                else
                {
                    ans = f(nums, limit, status ^ (1 << i), cur + nums[i], rest,
                            dp);
                }
                if (ans)
                {
                    break;
                }
            }
        }
        dp[status] = ans ? 1 : -1;
        return ans;
    }
};