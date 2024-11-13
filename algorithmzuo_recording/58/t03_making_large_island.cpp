// 最大人工岛
// 给你一个大小为 n * n 二进制矩阵 grid 。最多 只能将一格 0 变成 1 。
// 返回执行此操作后，grid 中最大的岛屿面积是多少？
// 岛屿 由一组上、下、左、右四个方向相连的 1 形成
// 测试链接 : https://leetcode.cn/problems/making-a-large-island/

class Solution
{
public:
    void dfs(vector<vector<int>> &grid, int r, int c, int id)
    {
        if (r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size() || grid[r][c] != 1)
        {
            return;
        }
        grid[r][c] = id;
        dfs(grid, r - 1, c, id);
        dfs(grid, r + 1, c, id);
        dfs(grid, r, c - 1, id);
        dfs(grid, r, c + 1, id);
    }
    int largestIsland(vector<vector<int>> &grid)
    {
        int id = 2;
        for (int i = 0; i < grid.size(); ++i)
        {
            for (int j = 0; j < grid[i].size(); ++j)
            {
                if (grid[i][j] == 1)
                {
                    dfs(grid, i, j, id++);
                }
            }
        }
        int ans = 0;
        vector<int> sizes(id, 0);
        for (int i = 0; i < grid.size(); ++i)
        {
            for (int j = 0; j < grid[i].size(); ++j)
            {
                if (grid[i][j] > 1)
                    ans = max(ans, ++sizes[grid[i][j]]);
            }
        }
        // 讨论所有的0，变成1，能带来的最大岛的大小
        vector<bool> visited(id, false);
        int up, down, left, right, merge;
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[i].size(); j++)
            {
                if (grid[i][j] == 0)
                {
                    up = i > 0 ? grid[i - 1][j] : 0;
                    down = i + 1 < grid.size() ? grid[i + 1][j] : 0;
                    left = j > 0 ? grid[i][j - 1] : 0;
                    right = j + 1 < grid[0].size() ? grid[i][j + 1] : 0;
                    merge = 1;
                    if (!visited[up])
                    {
                        merge += sizes[up];
                        visited[up] = true;
                    }
                    // visited[up] = true;
                    // merge = 1 + sizes[up];
                    if (!visited[down])
                    {
                        merge += sizes[down];
                        visited[down] = true;
                    }
                    if (!visited[left])
                    {
                        merge += sizes[left];
                        visited[left] = true;
                    }
                    if (!visited[right])
                    {
                        merge += sizes[right];
                        visited[right] = true;
                    }
                    ans = max(ans, merge);
                    visited[up] = false;
                    visited[down] = false;
                    visited[left] = false;
                    visited[right] = false;
                }
            }
        }
        return ans;
    }
};