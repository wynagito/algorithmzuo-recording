// 01bfs，适用于 图中所有边的权重只有0和1两种值，求源点到目标点的最短距离
// 时间复杂度为 O(节点数量+边的数量)，为什么不能用传统bfs？
// 1，distance[i]表示从源点到i点的最短距离，初始时所有点的distance设置为无穷大
// 2，源点进入双端队列，distance[源点]=0
// 3，双端队列 头部弹出 x，
//    A，如果x是目标点，返回distance[x]表示源点到目标点的最短距离
//    B，考察从x出发的每一条边，假设某边去y点，边权为w
//       1）如果 distance[y] > distance[x] + w，处理该边；否则忽略该边
//       2）处理时，更新distance[y] = distance[x] + w
//          如果w==0，y从头部进入双端队列；如果w==1，y从尾部进入双端队列
//       3）考察完x出发的所有边之后，重复步骤3
// 4，双端队列为空停止

// 01bfs为什么不用visited数组？
// 因为队列里任意两个元素之间差值都不会超过1
// 且0在对头 1在队尾
// 保证从队头出去时起到修正作用

// 宽度优先遍历与深度优先遍历结合，去生成路径
// 1，bfs建图
// 2，dfs利用图生成路径

// 到达角落需要移除障碍物的最小数目
// 给你一个下标从 0 开始的二维整数数组 grid ，数组大小为 m x n
// 每个单元格都是两个值之一：
// 0 表示一个 空 单元格，
// 1 表示一个可以移除的 障碍物
// 你可以向上、下、左、右移动，从一个空单元格移动到另一个空单元格。
// 现在你需要从左上角 (0, 0) 移动到右下角 (m - 1, n - 1)
// 返回需要移除的障碍物的最小数目
// 测试链接 : https://leetcode.cn/problems/minimum-obstacle-removal-to-reach-corner/

class Solution
{
public:
    int minimumObstacles(vector<vector<int>> &grid)
    {
        int move[5] = {-1, 0, 1, 0, -1};
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> distance = grid;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                distance[i][j] = INT_MAX;
            }
        }
        deque<pair<int, int>> dq;
        dq.push_front({0, 0});
        distance[0][0] = 0;
        while (!dq.empty())
        {
            auto record = dq.front();
            dq.pop_front();
            int x = record.first;
            int y = record.second;
            if (x == m - 1 && y == n - 1)
            {
                return distance[x][y];
            }
            for (int i = 0; i < 4; i++)
            {
                int nx = x + move[i], ny = y + move[i + 1];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n &&
                    distance[x][y] + grid[nx][ny] < distance[nx][ny])
                {
                    distance[nx][ny] = distance[x][y] + grid[nx][ny];
                    if (grid[nx][ny] == 0)
                    {
                        dq.push_front({nx, ny});
                    }
                    else
                    {
                        dq.push_back({nx, ny});
                    }
                }
            }
        }
        return -1;
    }
};