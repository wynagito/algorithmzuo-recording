// 滑动窗口：维持左、右边界都不回退的一段范围，来求解很多子数组（串）的相关问题
// 滑动窗口的关键：找到 范围 和 答案指标 之间的 单调性关系（类似贪心）
// 滑动过程：滑动窗口可以用 简单变量 或者 结构 来 维护信息
// 求解大流程：求子数组在 每个位置 开头 或 结尾 情况下的答案（开头还是结尾在于个人习惯）

// 累加和大于等于target的最短子数组长度
// 给定一个含有 n 个正整数的数组和一个正整数 target
// 找到累加和 >= target 的长度最小的子数组并返回其长度
// 如果不存在符合条件的子数组返回0
// 测试链接 : https://leetcode.cn/problems/minimum-size-subarray-sum/

class Solution
{
public:
    int minSubArrayLen(int target, vector<int> &nums)
    {
        int s = 0;
        int j = 0;
        int res = 0x3f3f3f;
        for (int i = 0; i < nums.size(); ++i)
        {
            s += nums[i];
            while (s >= target)
            {
                // sum : nums[j....i]
                // 如果j位置的数从窗口出去，还能继续达标，那就出去
                res = min(res, i - j + 1);
                s -= nums[j++];
            }
        }
        return res == 0x3f3f3f ? 0 : res;
    }
};