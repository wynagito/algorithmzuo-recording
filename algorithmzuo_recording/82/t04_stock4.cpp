// 买卖股票的最佳时机 IV
// 给你一个整数数组 prices 和一个整数 k ，其中 prices[i] 是某支给定的股票在第 i 天的价格
// 设计一个算法来计算你所能获取的最大利润。你最多可以完成 k 笔交易
// 也就是说，你最多可以买 k 次，卖 k 次
// 注意：你不能同时参与多笔交易，你必须在再次购买前出售掉之前的股票
// 测试链接 : https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iv/

class Solution
{
public:
    // 就是股票问题2
    int free(vector<int> &prices)
    {
        int ans = 0;
        for (int i = 1; i < prices.size(); i++)
        {
            ans += max(prices[i] - prices[i - 1], 0);
        }
        return ans;
    }

    int maxProfit1(int k, vector<int> &prices)
    {
        int n = prices.size();
        if (k >= n / 2)
        {
            // 这是一个剪枝
            // 如果k >= n / 2，那么代表所有上坡都可以抓到
            // 所有上坡都可以抓到 == 交易次数无限，所以回到股票问题2
            return free(prices);
        }

        // dp[i][j] : 一定要进行i次交易，在0到j范围上的最大利润
        vector<vector<int>> dp(k + 1, vector<int>(n));
        for (int i = 1; i <= k; i++)
        {
            for (int j = 1; j < n; j++)
            {
                // 1. i次交易，不在第j天卖出
                dp[i][j] = dp[i][j - 1];
                // 2. 第i次交易，在第j天卖出 前i-1次交易在0到j-1天内完成
                for (int p = 0; p < j; p++)
                {
                    dp[i][j] = max(dp[i][j], dp[i - 1][p] + prices[j] - prices[p]);
                }
            }
        }
        return dp[k][n - 1];
    }

    int maxProfit2(int k, vector<int> &prices)
    {
        int n = prices.size();
        if (k >= n / 2)
        {
            // 这是一个剪枝
            // 如果k >= n / 2，那么代表所有上坡都可以抓到
            // 所有上坡都可以抓到 == 交易次数无限，所以回到股票问题2
            return free(prices);
        }
        vector<vector<int>> dp(k + 1, vector<int>(n));
        for (int i = 1, best; i <= k; i++)
        {
            best = dp[i - 1][0] - prices[0];
            for (int j = 1; j < n; j++)
            {
                // 用best变量替代了枚举行为
                dp[i][j] = max(dp[i][j - 1], best + prices[j]);
                best = max(best, dp[i - 1][j] - prices[j]);
            }
        }
        return dp[k][n - 1];
    }

    // 对方法2进行空间压缩的版本
    int maxProfit3(int k, vector<int> &prices)
    {
        int n = prices.length;
        if (k >= n / 2)
        {
            // 这是一个剪枝
            // 如果k >= n / 2，那么代表所有上坡都可以抓到
            // 所有上坡都可以抓到 == 交易次数无限，所以回到股票问题2
            return free(prices);
        }
        vector<int> dp(n);
        for (int i = 1, best, tmp; i <= k; i++)
        {
            best = dp[0] - prices[0];
            for (int j = 1; j < n; j++)
            {
                tmp = dp[j];
                dp[j] = max(dp[j - 1], best + prices[j]);
                best = max(best, tmp - prices[j]);
            }
        }
        return dp[n - 1];
    }
};