// 动态规划方法的复杂度大致可以理解为：O(状态数量 * 每个状态的枚举代价)
// 当每个状态的枚举代价为O(1)，那么写出记忆化搜索的版本，就是时间复杂度最好的实现了
// 但是当每个状态的枚举代价比较高的时候，记忆化搜索的版本可能不是最优解，可能存在进一步的优化
// 之所以从记忆化搜索改出了严格位置依赖的版本，是为了建立空间感，让观察并优化枚举的分析变容易

// 通过观察优化枚举的技巧包括：
// 观察并优化转移方程、观察并设计高效的查询结构

// 买卖股票的最佳时机
// 给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格
// 你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票
// 设计一个算法来计算你所能获取的最大利润
// 返回你可以从这笔交易中获取的最大利润
// 如果你不能获取任何利润，返回 0
// 测试链接 : https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int ans = 0;
        for (int i = 1, minval = prices[0]; i < prices.size(); i++)
        {
            // minval : 0...i范围上的最小值
            minval = min(minval, prices[i]);
            ans = max(ans, prices[i] - minval);
        }
        return ans;
    }
};