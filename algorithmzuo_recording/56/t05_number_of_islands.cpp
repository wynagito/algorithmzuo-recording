// 岛屿数量
// 给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量
// 岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成
// 此外，你可以假设该网格的四条边均被水包围
// 测试链接 : https://leetcode.cn/problems/number-of-islands/

class Solution
{
public:
    int numIslands(vector<vector<char>> &board)
    {
        int n = board.size();
        int m = board[0].size();
        build(n, m, board);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (board[i][j] == '1')
                {
                    if (j > 0 && board[i][j - 1] == '1')
                    {
                        merge(i, j, i, j - 1);
                    }
                    if (i > 0 && board[i - 1][j] == '1')
                    {
                        merge(i, j, i - 1, j);
                    }
                }
            }
        }
        return sets;
    }

    static const int MAXSIZE = 100001;
    // 矩阵按行存储
    int father[MAXSIZE];

    int cols;

    int sets;

    void build(int n, int m, vector<vector<char>> &board)
    {
        cols = m;
        sets = 0;
        for (int a = 0; a < n; a++)
        {
            for (int b = 0, idx; b < m; b++)
            {
                if (board[a][b] == '1')
                {
                    idx = index(a, b);
                    father[idx] = idx;
                    sets++;
                }
            }
        }
    }

    int index(int a, int b)
    {
        return a * cols + b;
    }

    int find(int i)
    {
        if (i != father[i])
        {
            father[i] = find(father[i]);
        }
        return father[i];
    }

    void merge(int a, int b, int c, int d)
    {
        int fx = find(index(a, b));
        int fy = find(index(c, d));
        if (fx != fy)
        {
            father[fx] = fy;
            sets--;
        }
    }
};