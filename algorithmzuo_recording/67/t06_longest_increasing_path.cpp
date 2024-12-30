// 矩阵中的最长递增路径
// 给定一个 m x n 整数矩阵 matrix ，找出其中 最长递增路径 的长度
// 对于每个单元格，你可以往上，下，左，右四个方向移动
// 你 不能 在 对角线 方向上移动或移动到 边界外（即不允许环绕）
// 测试链接 : https://leetcode.cn/problems/longest-increasing-path-in-a-matrix/

class Solution
{
public:
    int longestIncreasingPath1(vector<vector<int>> &grid)
    {
        int ans = 0;
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[0].size(); j++)
            {
                ans = max(ans, f1(grid, i, j));
            }
        }
        return ans;
    }

    // 从(i,j)出发，能走出来多长的递增路径，返回最长长度
    int f1(vector<vector<int>> &grid, int i, int j)
    {
        int next = 0;
        if (i > 0 && grid[i][j] < grid[i - 1][j])
        {
            next = max(next, f1(grid, i - 1, j));
        }
        if (i + 1 < grid.size() && grid[i][j] < grid[i + 1][j])
        {
            next = max(next, f1(grid, i + 1, j));
        }
        if (j > 0 && grid[i][j] < grid[i][j - 1])
        {
            next = max(next, f1(grid, i, j - 1));
        }
        if (j + 1 < grid[0].size() && grid[i][j] < grid[i][j + 1])
        {
            next = max(next, f1(grid, i, j + 1));
        }
        return next + 1;
    }

    int longestIncreasingPath2(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> dp(n, vector<int>(m, 0));
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                ans = max(ans, f2(grid, i, j, dp));
            }
        }
        return ans;
    }

    int f2(vector<vector<int>> &grid, int i, int j, vector<vector<int>> &dp)
    {
        if (dp[i][j] != 0)
        {
            return dp[i][j];
        }
        int next = 0;
        if (i > 0 && grid[i][j] < grid[i - 1][j])
        {
            next = max(next, f2(grid, i - 1, j, dp));
        }
        if (i + 1 < grid.size() && grid[i][j] < grid[i + 1][j])
        {
            next = max(next, f2(grid, i + 1, j, dp));
        }
        if (j > 0 && grid[i][j] < grid[i][j - 1])
        {
            next = max(next, f2(grid, i, j - 1, dp));
        }
        if (j + 1 < grid[0].size() && grid[i][j] < grid[i][j + 1])
        {
            next = max(next, f2(grid, i, j + 1, dp));
        }
        dp[i][j] = next + 1;
        return next + 1;
    }
};