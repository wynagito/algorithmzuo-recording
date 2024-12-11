// 最低票价
// 在一个火车旅行很受欢迎的国度，你提前一年计划了一些火车旅行
// 在接下来的一年里，你要旅行的日子将以一个名为 days 的数组给出
// 每一项是一个从 1 到 365 的整数
// 火车票有 三种不同的销售方式
// 一张 为期1天 的通行证售价为 costs[0] 美元
// 一张 为期7天 的通行证售价为 costs[1] 美元
// 一张 为期30天 的通行证售价为 costs[2] 美元
// 通行证允许数天无限制的旅行
// 例如，如果我们在第 2 天获得一张 为期 7 天 的通行证
// 那么我们可以连着旅行 7 天(第2~8天)
// 返回 你想要完成在给定的列表 days 中列出的每一天的旅行所需要的最低消费
// 测试链接 : https://leetcode.cn/problems/minimum-cost-for-tickets/

class Solution
{
public:
    // 无论提交什么方法都带着这个数组
    int durations[3] = {1, 7, 30};
    int mincostTickets1(vector<int> &days, vector<int> &costs)
    {
        return f1(days, costs, 0);
    }

    // days[i.....] 最少花费是多少
    int f1(vector<int> &days, vector<int> &costs, int i)
    {
        if (i == days.size())
        {
            // 后续已经无旅行了
            return 0;
        }
        // i下标 : 第days[i]天，有一场旅行
        // i.... 最少花费是多少
        int ans = INT_MAX;
        for (int k = 0, j = i; k < 3; k++)
        {
            // k是方案编号 : 0 1 2
            while (j < days.size() && days[i] + durations[k] > days[j])
            {
                // 因为方案2持续的天数最多，30天
                // 所以while循环最多执行30次
                // 枚举行为可以认为是O(1)
                j++;
            }
            ans = min(ans, costs[k] + f1(days, costs, j));
        }
        return ans;
    }

    // 暴力尝试改记忆化搜索
    // 从顶到底的动态规划
    int mincostTickets2(vector<int> &days, vector<int> &costs)
    {
        vector<int> dp(days.size(), INT_MAX);
        return f2(days, costs, 0, dp);
    }

    int f2(vector<int> &days, vector<int> &costs, int i, vector<int> &dp)
    {
        if (i == days.size())
        {
            return 0;
        }
        if (dp[i] != INT_MAX)
        {
            return dp[i];
        }
        int ans = INT_MAX;
        for (int k = 0, j = i; k < 3; k++)
        {
            while (j < days.size() && days[i] + durations[k] > days[j])
            {
                j++;
            }
            ans = min(ans, costs[k] + f2(days, costs, j, dp));
        }
        dp[i] = ans;
        return ans;
    }

    // 严格位置依赖的动态规划
    // 从底到顶的动态规划
    int mincostTickets3(vector<int> &days, vector<int> &costs)
    {
        int n = days.size();
        vector<int> dp(n + 1, INT_MAX);
        dp[n] = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            for (int k = 0, j = i; k < 3; k++)
            {
                while (j < days.size() && days[i] + durations[k] > days[j])
                {
                    j++;
                }
                dp[i] = min(dp[i], costs[k] + dp[j]);
            }
        }
        return dp[0];
    }
};
