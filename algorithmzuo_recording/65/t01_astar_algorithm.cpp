// A*算法，指定源点，指定目标点，求源点到达目标点的最短距离
// 增加了当前点到终点的预估函数
// 在堆中根据 从源点出发到达当前点的距离+当前点到终点的预估距离 来进行排序
// 剩下的所有细节和Dijskra算法完全一致

// 预估函数要求：当前点到终点的预估距离 <= 当前点到终点的真实最短距离
// 预估函数是一种吸引力
// 1）合适的吸引力可以提升算法的速度，吸引力过强会出现错误
// 2）保证 预估距离 <= 真实最短距离 的情况下，尽量接近真实最短距离，可以做到功能正确 且 最快

// 预估终点距离经常选择：
// 曼哈顿距离
// 欧式距离
// 对角线距离

// A*算法模版（对数器验证）
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// 移动方向数组
// 0:上，1:右，2:下，3:左
int direction[5] = {-1, 0, 1, 0, -1};

int minDistance1(vector<vector<int>> &grid, int startX, int startY, int targetX, int targetY);
int minDistance2(vector<vector<int>> &grid, int startX, int startY, int targetX, int targetY);
int f1(int x, int y, int targetX, int targetY);
vector<vector<int>> randomGrid(int n);

// Dijkstra算法
// Dijkstra算法
// grid[i][j] == 0 代表障碍
// grid[i][j] == 1 代表道路
// 只能走上、下、左、右，不包括斜线方向
// 返回从(startX, startY)到(targetX, targetY)的最短距离
int minDistance1(vector<vector<int>> &grid, int startX, int startY, int targetX, int targetY)
{
    if (grid[startX][startY] == 0 || grid[targetX][targetY] == 0)
    {
        return -1;
    }
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
    dist[startX][startY] = 1;
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> heap;

    heap.push({1, startX, startY}); // 距离, 行, 列
    while (!heap.empty())
    {
        auto cur = heap.top();
        heap.pop();
        // 0 : 从源点出发到达当前点的距离
        // 1 : 行
        // 2 : 列
        int d = cur[0], x = cur[1], y = cur[2];
        if (visited[x][y])
        {
            continue;
        }
        visited[x][y] = true;
        if (x == targetX && y == targetY)
        {
            return dist[x][y];
        }
        for (int i = 0; i < 4; i++)
        {
            int nx = x + direction[i];
            int ny = y + direction[i + 1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 1 && !visited[nx][ny] && dist[x][y] + 1 < dist[nx][ny])
            {
                dist[nx][ny] = dist[x][y] + 1;
                heap.push({dist[nx][ny], nx, ny});
            }
        }
    }
    return -1;
}

// A*算法
// grid[i][j] == 0 代表障碍
// grid[i][j] == 1 代表道路
// 只能走上、下、左、右，不包括斜线方向
// 返回从(startX, startY)到(targetX, targetY)的最短距离
int minDistance2(vector<vector<int>> &grid, int startX, int startY, int targetX, int targetY)
{
    if (grid[startX][startY] == 0 || grid[targetX][targetY] == 0)
    {
        return -1;
    }
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
    dist[startX][startY] = 1;
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> heap;

    // 0 : 从源点出发到达当前点的距离 + 当前点到终点的预估距离
    // 1 : 行
    // 2 : 列
    heap.push({1 + f1(startX, startY, targetX, targetY), startX, startY});
    while (!heap.empty())
    {
        auto cur = heap.top();
        heap.pop();
        int d = cur[0], x = cur[1], y = cur[2];
        if (visited[x][y])
        {
            continue;
        }
        visited[x][y] = true;
        if (x == targetX && y == targetY)
        {
            return dist[x][y];
        }
        for (int i = 0; i < 4; i++)
        {
            int nx = x + direction[i];
            int ny = y + direction[i + 1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 1 && !visited[nx][ny] && dist[x][y] + 1 < dist[nx][ny])
            {
                dist[nx][ny] = dist[x][y] + 1;
                heap.push({dist[nx][ny] + f1(nx, ny, targetX, targetY), nx, ny});
            }
        }
    }
    return -1;
}

// 曼哈顿距离
int f1(int x, int y, int targetX, int targetY)
{
    return abs(targetX - x) + abs(targetY - y);
}

// 对角线距离
int f2(int x, int y, int targetX, int targetY)
{
    return max(abs(targetX - x), abs(targetY - y));
}

// 欧式距离
double f3(int x, int y, int targetX, int targetY)
{
    return sqrt(pow(targetX - x, 2) + pow(targetY - y, 2));
}

// 随机生成测试网格
vector<vector<int>> randomGrid(int n)
{
    vector<vector<int>> grid(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            grid[i][j] = (rand() % 100 < 30) ? 0 : 1; // 30%概率是0
        }
    }
    return grid;
}

// 测试
int main()
{
    srand(time(0));
    int len = 100;
    int testTime = 10000;
    cout << "功能测试开始" << endl;
    for (int i = 0; i < testTime; i++)
    {
        int n = rand() % len + 2;
        auto grid = randomGrid(n);
        int startX = rand() % n;
        int startY = rand() % n;
        int targetX = rand() % n;
        int targetY = rand() % n;
        int ans1 = minDistance1(grid, startX, startY, targetX, targetY);
        int ans2 = minDistance2(grid, startX, startY, targetX, targetY);
        if (ans1 != ans2)
        {
            cout << "出错了!" << endl;
        }
    }
    cout << "功能测试结束" << endl;

    cout << "性能测试开始" << endl;
    auto grid = randomGrid(4000);
    int startX = 0, startY = 0, targetX = 3900, targetY = 3900;
    clock_t start, end;

    start = clock();
    int ans1 = minDistance1(grid, startX, startY, targetX, targetY);
    end = clock();
    cout << "运行dijkstra算法结果: " << ans1 << ", 运行时间(毫秒): " << (double)(end - start) * 1000 / CLOCKS_PER_SEC << endl;

    start = clock();
    int ans2 = minDistance2(grid, startX, startY, targetX, targetY);
    end = clock();
    cout << "运行A*算法结果: " << ans2 << ", 运行时间(毫秒): " << (double)(end - start) * 1000 / CLOCKS_PER_SEC << endl;
    cout << "性能测试结束" << endl;

    return 0;
}
