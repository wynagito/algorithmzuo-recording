// 接雨水
// 给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水
// 测试链接 : https://leetcode.cn/problems/trapping-rain-water/

class Solution
{
public:
    int trap1(vector<int> &nums)
    {
        int n = nums.size();
        int lmax[n];
        int rmax[n];
        lmax[0] = nums[0];
        // 0~i范围上的最大值，记录在lmax[i]
        for (int i = 1; i < n; i++)
        {
            lmax[i] = max(lmax[i - 1], nums[i]);
        }
        rmax[n - 1] = nums[n - 1];
        // i~n-1范围上的最大值，记录在rmax[i]
        for (int i = n - 2; i >= 0; i--)
        {
            rmax[i] = max(rmax[i + 1], nums[i]);
        }
        int ans = 0;
        //   x              x
        //   0 1 2 3...n-2 n-1
        for (int i = 1; i < n - 1; i++)
        {
            ans += max(0, min(lmax[i - 1], rmax[i + 1]) - nums[i]);
        }
        return ans;
    }

    // 双指针的解法（最优解）
    // 时间复杂度O(n)，额外空间复杂度O(1)
    // 提交时改名为trap
    int trap2(vector<int> &nums)
    {
        int l = 1, r = nums.size() - 2, lmax = nums[0], rmax = nums[nums.size() - 1];
        int ans = 0;
        while (l <= r)
        {
            if (lmax <= rmax)
            {
                ans += max(0, lmax - nums[l]);
                lmax = max(lmax, nums[l++]);
            }
            else
            {
                ans += max(0, rmax - nums[r]);
                rmax = max(rmax, nums[r--]);
            }
        }
        return ans;
    }
};