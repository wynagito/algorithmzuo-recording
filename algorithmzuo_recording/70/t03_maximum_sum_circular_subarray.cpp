// 环形数组的子数组最大累加和
// 给定一个数组nums，长度为n
// nums是一个环形数组，下标0和下标n-1是连在一起的
// 返回环形数组中，子数组最大累加和
// 测试链接 : https://leetcode.cn/problems/maximum-sum-circular-subarray/

class Solution
{
public:
    int maxSubarraySumCircular(vector<int> &nums)
    {
        int n = nums.size(), all = nums[0], maxsum = nums[0], minsum = nums[0];
        for (int i = 1, maxpre = nums[0], minpre = nums[0]; i < n; i++)
        {
            all += nums[i];
            maxpre = max(nums[i], nums[i] + maxpre);
            maxsum = max(maxsum, maxpre);
            minpre = min(nums[i], nums[i] + minpre);
            minsum = min(minsum, minpre);
        }
        // 1) maxsum
        // 2) all - minsum
        return all == minsum ? maxsum : max(maxsum, all - minsum);
    }
};