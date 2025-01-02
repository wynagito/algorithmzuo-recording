// 乘积最大子数组
// 给你一个整数数组 nums
// 请你找出数组中乘积最大的非空连续子数组
// 并返回该子数组所对应的乘积
// 测试链接 : https://leetcode.cn/problems/maximum-product-subarray/

class Solution
{
public:
    // 用int类型的变量会让中间结果溢出
    // 所以改成用long类型的变量
    // 思路是不变的
    int maxProduct(vector<int> &nums)
    {
        long ans = nums[0], premin = nums[0], premax = nums[0], curmin, curmax;
        for (int i = 1; i < nums.size(); i++)
        {
            curmin = min((long)nums[i], min(premin * nums[i], premax * nums[i]));
            curmax = max((long)nums[i], max(premin * nums[i], premax * nums[i]));
            premin = curmin;
            premax = curmax;
            ans = max(ans, premax);
        }
        return (int)ans;
    }
};