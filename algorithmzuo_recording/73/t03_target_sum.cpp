// 目标和
// 给你一个非负整数数组 nums 和一个整数 target 。
// 向数组中的每个整数前添加 '+' 或 '-' ，然后串联起所有整数
// 可以构造一个表达式
// 例如nums=[2, 1]，可以在2之前添加'+' ，在1之前添加'-'
// 然后串联起来得到表达式 "+2-1" 。
// 返回可以通过上述方法构造的，运算结果等于 target 的不同表达式的数目
// 测试链接 : https://leetcode.cn/problems/target-sum/

class Solution
{
public:
    // 普通尝试，暴力递归版
    int findTargetSumWays1(vector<int> &nums, int S)
    {
        return f1(nums, S, 0, 0);
    }

    // nums[0...i-1]范围上，已经形成的累加和是sum
    // nums[i...]范围上，每个数字可以标记+或者-
    // 最终形成累加和为target的不同表达式数目
    int f1(vector<int> &nums, int target, int i, int sum)
    {
        if (i == nums.size())
        {
            return sum == target ? 1 : 0;
        }
        return f1(nums, target, i + 1, sum + nums[i]) + f1(nums, target, i + 1, sum - nums[i]);
    }

    // 普通尝试，记忆化搜索版
    int findTargetSumWays2(vector<int> &nums, int S)
    {
        // i, sum -> value（返回值 ）
        unordered_map<int, unordered_map<int, int>> dp;
        return f2(nums, S, 0, 0, dp);
    }

    // 因为累加和可以为负数
    // 所以缓存动态规划表用哈希表
    int f2(vector<int> &nums, int target, int i, int j, unordered_map<int, unordered_map<int, int>> &dp)
    {
        if (i == nums.size())
        {
            return j == target ? 1 : 0;
        }
        if (dp.count(i) && dp[i].count(j))
        {
            return dp[i][j];
        }
        int ans = f2(nums, target, i + 1, j + nums[i], dp) + f2(nums, target, i + 1, j - nums[i], dp);
        dp[i] = {{j, ans}};
        return ans;
    }

    // 普通尝试
    // 严格位置依赖的动态规划
    // 平移技巧
    int findTargetSumWays3(vector<int> &nums, int target)
    {
        int s = 0;
        for (int num : nums)
        {
            s += num;
        }
        if (target < -s || target > s)
        {
            return 0;
        }
        int n = nums.size();
        // -s ~ +s -> 2 * s + 1
        int m = 2 * s + 1;
        // 原本的dp[i][j]含义:
        // nums[0...i-1]范围上，已经形成的累加和是sum
        // nums[i...]范围上，每个数字可以标记+或者-
        // 最终形成累加和为target的不同表达式数目
        // 因为sum可能为负数，为了下标不出现负数，
        // "原本的dp[i][j]"由dp表中的dp[i][j + s]来表示
        // 也就是平移操作！
        // 一切"原本的dp[i][j]"一律平移到dp表中的dp[i][j + s]
        vector<vector<int>> dp(n + 1, vector<int>(m, 0));
        // 原本的dp[n][target] = 1，平移！
        dp[n][target + s] = 1;
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = -s; j <= s; j++)
            {
                if (j + nums[i] + s < m)
                {
                    // 原本是 : dp[i][j] = dp[i + 1][j + nums[i]]
                    // 平移！
                    dp[i][j + s] = dp[i + 1][j + nums[i] + s];
                }
                if (j - nums[i] + s >= 0)
                {
                    // 原本是 : dp[i][j] += dp[i + 1][j - nums[i]]
                    // 平移！
                    dp[i][j + s] += dp[i + 1][j - nums[i] + s];
                }
            }
        }
        // 原本应该返回dp[0][0]
        // 平移！
        // 返回dp[0][0 + s]
        return dp[0][s];
    }

    // 新思路，转化为01背包问题
    // 思考1:
    // 虽然题目说nums是非负数组，但即使nums中有负数比如[3,-4,2]
    // 因为能在每个数前面用+或者-号
    // 所以[3,-4,2]其实和[3,4,2]会达成一样的结果
    // 所以即使nums中有负数，也可以把负数直接变成正数，也不会影响结果
    // 思考2:
    // 如果nums都是非负数，并且所有数的累加和是sum
    // 那么如果target>sum，很明显没有任何方法可以达到target，可以直接返回0
    // 思考3:
    // nums内部的数组，不管怎么+和-，最终的结果都一定不会改变奇偶性
    // 所以，如果所有数的累加和是sum，并且与target的奇偶性不一样
    // 那么没有任何方法可以达到target，可以直接返回0
    // 思考4(最重要):
    // 比如说给定一个数组, nums = [1, 2, 3, 4, 5] 并且 target = 3
    // 其中一个方案是 : +1 -2 +3 -4 +5 = 3
    // 该方案中取了正的集合为A = {1，3，5}
    // 该方案中取了负的集合为B = {2，4}
    // 所以任何一种方案，都一定有 sum(A) - sum(B) = target
    // 现在我们来处理一下这个等式，把左右两边都加上sum(A) + sum(B)，那么就会变成如下：
    // sum(A) - sum(B) + sum(A) + sum(B) = target + sum(A) + sum(B)
    // 2 * sum(A) = target + 数组所有数的累加和
    // sum(A) = (target + 数组所有数的累加和) / 2
    // 也就是说，任何一个集合，只要累加和是(target + 数组所有数的累加和) / 2
    // 那么就一定对应一种target的方式
    // 比如非负数组nums，target = 1, nums所有数累加和是11
    // 求有多少方法组成1，其实就是求，有多少种子集累加和达到6的方法，(1+11)/2=6
    // 因为，子集累加和6 - 另一半的子集累加和5 = 1（target)
    // 所以有多少个累加和为6的不同集合，就代表有多少个target==1的表达式数量
    // 至此已经转化为01背包问题了
    int findTargetSumWays(vector<int> &nums, int S)
    {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (abs(S) > sum || (S + sum) % 2 == 1)
        {
            return 0; // 此时没有方案
        }
        // 求非负数组nums有多少个子序列累加和是t
        // 01背包问题(子集累加和严格是t) + 空间压缩
        // dp[i][j] = dp[i-1][j] + dp[i-1][j-nums[i]]
        int bagSize = (S + sum) / 2;
        vector<int> dp(bagSize + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < nums.size(); i++)
        {
            for (int j = bagSize; j >= nums[i]; j--)
            {
                dp[j] += dp[j - nums[i]];
            }
        }
        return dp[bagSize];
    }
};