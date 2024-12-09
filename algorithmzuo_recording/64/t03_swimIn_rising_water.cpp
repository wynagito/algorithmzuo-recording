// 水位上升的泳池中游泳
// 在一个 n x n 的整数矩阵 grid 中
// 每一个方格的值 grid[i][j] 表示位置 (i, j) 的平台高度
// 当开始下雨时，在时间为 t 时，水池中的水位为 t
// 你可以从一个平台游向四周相邻的任意一个平台，但是前提是此时水位必须同时淹没这两个平台
// 假定你可以瞬间移动无限距离，也就是默认在方格内部游动是不耗时的
// 当然，在你游泳的时候你必须待在坐标方格里面。
// 你从坐标方格的左上平台 (0，0) 出发
// 返回 你到达坐标方格的右下平台 (n-1, n-1) 所需的最少时间
// 测试链接 : https://leetcode.cn/problems/swim-in-rising-water/

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
    int move[5] = {-1, 0, 1, 0, -1};
    int distance[110][110];
    bool visited[110][110];
    int swimInWater(vector<vector<int>> &heights)
    {
        int n = heights.size();
        int m = heights[0].size();
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                distance[i][j] = INT_MAX;
                visited[i][j] = false;
            }
        }
        distance[0][0] = heights[0][0];
        // 0 : 格子的行
        // 1 : 格子的列
        // 2 : 源点到当前格子的代价
        priority_queue<vector<int>, vector<vector<int>>, cmp> heap;
        heap.push({0, 0, heights[0][0]});
        while (!heap.empty())
        {
            auto record = heap.top();
            heap.pop();
            int x = record[0];
            int y = record[1];
            int c = record[2];
            if (visited[x][y])
            {
                continue;
            }
            if (x == n - 1 && y == m - 1)
            {
                // 常见剪枝
                // 发现终点直接返回
                // 不用等都结束
                return c;
            }
            visited[x][y] = true;
            for (int i = 0; i < 4; i++)
            {
                int nx = x + move[i];
                int ny = y + move[i + 1];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny])
                {
                    int nc = max(c, heights[nx][ny]);
                    if (nc < distance[nx][ny])
                    {
                        distance[nx][ny] = nc;
                        heap.push({nx, ny, nc});
                    }
                }
            }
        }
        return -1;
    }
};