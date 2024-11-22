// 宽度优先遍历基本内容

// bfs的特点是逐层扩散，从源头点到目标点扩散了几层，最短路就是多少
// bfs可以使用的特征是 任意两个节点之间的相互距离相同（无向图）
// bfs开始时，可以是 单个源头、也可以是 多个源头
// bfs频繁使用队列，形式可以是 单点弹出 或者 整层弹出
// bfs进行时，进入队列的节点需要标记状态，防止 同一个节点重复进出队列
// bfs进行时，可能会包含 剪枝策略 的设计
// bfs是一个理解难度很低的算法，难点在于 节点如何找到路、路的展开 和 剪枝设计

// 地图分析
// 你现在手里有一份大小为 n x n 的 网格 grid
// 上面的每个 单元格 都用 0 和 1 标记好了其中 0 代表海洋，1 代表陆地。
// 请你找出一个海洋单元格，这个海洋单元格到离它最近的陆地单元格的距离是最大的
// 并返回该距离。如果网格上只有陆地或者海洋，请返回 -1。
// 我们这里说的距离是「曼哈顿距离」（ Manhattan Distance）：
// (x0, y0) 和 (x1, y1) 这两个单元格之间的距离是 |x0 - x1| + |y0 - y1| 。
// 测试链接 : https://leetcode.cn/problems/as-far-from-land-as-possible/

class Solution
{
public:
    static const int MAXN = 101, MAXM = 101;

    int queue[MAXN * MAXM][2];

    int l, r;

    bool visited[MAXN][MAXM];

    // 0:上，1:右，2:下，3:左
    int move[5] = {-1, 0, 1, 0, -1};
    //                                      0  1  2  3   4
    //                                               i
    // (x,y)  i来到0位置 : x + move[i], y + move[i+1] -> x - 1, y
    // (x,y)  i来到1位置 : x + move[i], y + move[i+1] -> x, y + 1
    // (x,y)  i来到2位置 : x + move[i], y + move[i+1] -> x + 1, y
    // (x,y)  i来到3位置 : x + move[i], y + move[i+1] -> x, y - 1
    int maxDistance(vector<vector<int>> &grid)
    {
        l = r = 0;
        int n = grid.size();
        int m = grid[0].size();
        int seas = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] == 1)
                {
                    visited[i][j] = true;
                    queue[r][0] = i;
                    queue[r++][1] = j;
                }
                else
                {
                    visited[i][j] = false;
                    seas++;
                }
            }
        }
        if (seas == 0 || seas == n * m)
        {
            return -1;
        }
        int level = 0;
        while (l < r)
        {
            level++;
            int size = r - l;
            for (int k = 0, x, y, nx, ny; k < size; k++)
            {
                x = queue[l][0];
                y = queue[l++][1];
                for (int i = 0; i < 4; i++)
                {
                    // 上、右、下、左
                    nx = x + move[i];
                    ny = y + move[i + 1];
                    if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny])
                    {
                        visited[nx][ny] = true;
                        queue[r][0] = nx;
                        queue[r++][1] = ny;
                    }
                }
            }
        }
        return level - 1;
    }
};