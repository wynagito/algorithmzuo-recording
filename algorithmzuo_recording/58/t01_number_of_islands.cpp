// 洪水填充是一种很简单的技巧，设置路径信息进行剪枝和统计，类似感染的过程
// 路径信息不撤销，来保证每一片的感染过程可以得到区分
// 看似是暴力递归过程，其实时间复杂度非常好，遍历次数和样本数量的规模一致

// 岛屿数量
// 给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量
// 岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成
// 此外，你可以假设该网格的四条边均被水包围
// 测试链接 : https://leetcode.cn/problems/number-of-islands/

class Solution
{
public:
    // 洪水填充的做法
    // board : n * m
    // O(n*m)最优解！
    int numIslands(vector<vector<char>> &board)
    {
        int n = board.size();
        int m = board[0].size();
        int islands = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (board[i][j] == '1')
                {
                    islands++;
                    dfs(board, n, m, i, j);
                }
            }
        }
        return islands;
    }

    void dfs(vector<vector<char>> &board, int n, int m, int i, int j)
    {
        if (i < 0 || i == n || j < 0 || j == m || board[i][j] != '1')
        {
            return;
        }
        // board[i][j] = '1'
        board[i][j] = 0;
        dfs(board, n, m, i - 1, j);
        dfs(board, n, m, i + 1, j);
        dfs(board, n, m, i, j - 1);
        dfs(board, n, m, i, j + 1);
    }
};