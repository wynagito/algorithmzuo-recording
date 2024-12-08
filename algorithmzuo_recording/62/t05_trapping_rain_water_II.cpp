// 二维接雨水
// 给你一个 m * n 的矩阵，其中的值均为非负整数，代表二维高度图每个单元的高度
// 请计算图中形状最多能接多少体积的雨水。
// 测试链接 : https://leetcode.cn/problems/trapping-rain-water-ii/

struct cmp
{
    bool operator()(const vector<int> &a, const vector<int> &b)
    {
        return a[2] > b[2];
    }
};

class Solution
{
public:
    bool visited[210][210] = {false};
    int trapRainWater(vector<vector<int>> &height)
    {
        int move[5] = {-1, 0, 1, 0, -1};
        int n = height.size();
        int m = height[0].size();
        // 0 : 行
        // 1 : 列
        // 2 : 水线
        priority_queue<vector<int>, vector<vector<int>>, cmp> heap;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (i == 0 || i == n - 1 || j == 0 || j == m - 1)
                {
                    // 边界
                    heap.push({i, j, height[i][j]});
                    visited[i][j] = true;
                }
                else
                {
                    visited[i][j] = false;
                }
            }
        }
        int ans = 0;
        while (!heap.empty())
        {
            auto record = heap.top();
            heap.pop();
            int r = record[0];
            int c = record[1];
            int w = record[2];
            ans += w - height[r][c];
            for (int i = 0, nr, nc; i < 4; i++)
            {
                nr = r + move[i];
                nc = c + move[i + 1];
                if (nr >= 0 && nr < n && nc >= 0 && nc < m && !visited[nr][nc])
                {
                    heap.push({nr, nc, max(height[nr][nc], w)});
                    visited[nr][nc] = true;
                }
            }
        }
        return ans;
    }
};