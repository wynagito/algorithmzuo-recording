// 尝试函数有1个可变参数可以完全决定返回值，进而可以改出1维动态规划表的实现
// 同理
// 尝试函数有2个可变参数可以完全决定返回值，那么就可以改出2维动态规划的实现

// 一维、二维、三维甚至多维动态规划问题，大体过程都是：
// 写出尝试递归
// 记忆化搜索(从顶到底的动态规划)
// 严格位置依赖的动态规划(从底到顶的动态规划)
// 空间、时间的更多优化

// 动态规划表的大小：每个可变参数的可能性数量相乘
// 动态规划方法的时间复杂度：动态规划表的大小 * 每个格子的枚举代价

// 二维动态规划依然需要去整理 动态规划表的格子之间的依赖关系
// 找寻依赖关系，往往 通过画图来建立空间感，使其更显而易见
// 然后依然是 从简单格子填写到复杂格子 的过程，即严格位置依赖的动态规划(从底到顶)

// 二维动态规划的压缩空间技巧原理不难，会了之后千篇一律
// 但是不同题目依赖关系不一样，需要 很细心的画图来整理具体题目的依赖关系
// 最后进行空间压缩的实现

// 能改成动态规划的递归，统一特征：
// 决定返回值的可变参数类型往往都比较简单，一般不会比int类型更复杂。为什么？

// 从这个角度，可以解释 带路径的递归（可变参数类型复杂），不适合或者说没有必要改成动态规划
// 题目2就是说明这一点的

// 一定要 写出可变参数类型简单（不比int类型更复杂），并且 可以完全决定返回值的递归，
// 保证做到 这些可变参数可以完全代表之前决策过程对后续过程的影响！再去改动态规划！

// 不管几维动态规划
// 经常从递归的定义出发，避免后续进行很多边界讨论
// 这需要一定的经验来预知

// 最小路径和
// 给定一个包含非负整数的 m x n 网格 grid
// 请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
// 说明：每次只能向下或者向右移动一步。
// 测试链接 : https://leetcode.cn/problems/minimum-path-sum/

class Solution
{
public:
    // 暴力递归
    int minPathSum1(vector<vector<int>> &grid)
    {
        return f1(grid, grid.size() - 1, grid[0].size() - 1);
    }

    // 从(0,0)到(i,j)最小路径和
    // 一定每次只能向右或者向下
    int f1(vector<vector<int>> &grid, int i, int j)
    {
        if (i == 0 && j == 0)
        {
            return grid[0][0];
        }
        int up = INT_MAX;
        int left = INT_MAX;
        if (i - 1 >= 0)
        {
            up = f1(grid, i - 1, j);
        }
        if (j - 1 >= 0)
        {
            left = f1(grid, i, j - 1);
        }
        return grid[i][j] + min(up, left);
    }

    // 记忆化搜索
    int minPathSum2(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return f2(grid, n - 1, m - 1, dp);
    }

    int f2(vector<vector<int>> &grid, int i, int j, vector<vector<int>> &dp)
    {
        if (dp[i][j] != -1)
        {
            return dp[i][j];
        }
        int ans;
        if (i == 0 && j == 0)
        {
            ans = grid[0][0];
        }
        else
        {
            int up = INT_MAX;
            int left = INT_MAX;
            if (i - 1 >= 0)
            {
                up = f2(grid, i - 1, j, dp);
            }
            if (j - 1 >= 0)
            {
                left = f2(grid, i, j - 1, dp);
            }
            ans = grid[i][j] + min(up, left);
        }
        dp[i][j] = ans;
        return ans;
    }

    // 严格位置依赖的动态规划
    int minPathSum3(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> dp(n, vector<int>(m, 0));
        dp[0][0] = grid[0][0];
        for (int i = 1; i < n; i++)
        {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }
        for (int j = 1; j < m; j++)
        {
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        }
        for (int i = 1; i < n; i++)
        {
            for (int j = 1; j < m; j++)
            {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }
        return dp[n - 1][m - 1];
    }

    // 严格位置依赖的动态规划 + 空间压缩技巧
    int minPathSum4(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        // 先让dp表，变成想象中的表的第0行的数据
        vector<int> dp(m, 0);
        dp[0] = grid[0][0];
        for (int j = 1; j < m; j++)
        {
            dp[j] = dp[j - 1] + grid[0][j];
        }
        for (int i = 1; i < n; i++)
        {
            // i = 1，dp表变成想象中二维表的第1行的数据
            // i = 2，dp表变成想象中二维表的第2行的数据
            // i = 3，dp表变成想象中二维表的第3行的数据
            // ...
            // i = n-1，dp表变成想象中二维表的第n-1行的数据
            dp[0] += grid[i][0];
            for (int j = 1; j < m; j++)
            {
                dp[j] = min(dp[j - 1], dp[j]) + grid[i][j];
            }
        }
        return dp[m - 1];
    }
};
