// 子数组最大累加和
// 给你一个整数数组 nums
// 返回非空子数组的最大累加和
// 测试链接 : https://leetcode.cn/problems/maximum-subarray/

class Solution
{
public:
    // 动态规划
    int maxSubArray1(vector<int> &nums)
    {
        int n = nums.size();
        // dp[i] : 子数组必须以i位置的数做结尾，往左能延伸出来的最大累加和
        vector<int> dp(n);
        dp[0] = nums[0];
        int ans = nums[0];
        for (int i = 1; i < n; i++)
        {
            dp[i] = max(nums[i], dp[i - 1] + nums[i]);
            ans = max(ans, dp[i]);
        }
        return ans;
    }

    // 空间压缩
    int maxSubArray2(vector<int> &nums)
    {
        int n = nums.size();
        int ans = nums[0];
        for (int i = 1, pre = nums[0]; i < n; i++)
        {
            pre = max(nums[i], pre + nums[i]);
            ans = max(ans, pre);
        }
        return ans;
    }

    // 如下代码为附加问题的实现
    // 子数组中找到拥有最大累加和的子数组
    // 并返回如下三个信息:
    // 1) 最大累加和子数组的开头left
    // 2) 最大累加和子数组的结尾right
    // 3) 最大累加和子数组的累加和sum
    // 如果不止一个子数组拥有最大累加和，那么找到哪一个都可以
    int left, right, sum;

    // 找到拥有最大累加和的子数组
    // 更新好全局变量left、right、sum
    // 上游调用函数可以直接使用这三个变量
    // 相当于返回了三个值
    void extra(vector<int> nums)
    {
        sum = INT_MIN;
        for (int l = 0, r = 0, pre = INT_MIN; r < nums.size(); r++)
        {
            if (pre >= 0)
            {
                // 吸收前面的累加和有利可图
                // 那就不换开头
                pre += nums[r];
            }
            else
            {
                // 吸收前面的累加和已经无利可图
                // 那就换开头
                pre = nums[r];
                l = r;
            }
            if (pre > sum)
            {
                sum = pre;
                left = l;
                right = r;
            }
        }
    }
};