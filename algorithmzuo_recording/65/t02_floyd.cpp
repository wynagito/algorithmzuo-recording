// Floyd算法，得到图中任意两点之间的最短距离
// 时间复杂度O(n^3)，空间复杂度O(n^2)，常数时间小，容易实现
// 适用于任何图，不管有向无向、不管边权正负、但是不能有负环（保证最短路存在）

// 过程简述:
// distance[i][j]表示i和j之间的最短距离
// distance[i][j] = min ( distance[i][j] , distance[i][k] + distance[k][j])
// 枚举所有的k即可，实现时一定要最先枚举跳板！

// Floyd算法模版（洛谷）
// 测试链接 : https://www.luogu.com.cn/problem/P2910

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int MAXN = 101;
const int MAXM = 10001;
vector<int> path(MAXM);
vector<vector<int>> dist(MAXN, vector<int>(MAXN, numeric_limits<int>::max()));
int n, m, ans;

// 初始时设置任意两点之间的最短距离为无穷大，表示任何路不存在
void build()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            dist[i][j] = numeric_limits<int>::max();
        }
    }
}

void floyd()
{
    // O(N^3)的过程
    // 枚举每个跳板
    // 注意，跳板要最先枚举！跳板要最先枚举！跳板要最先枚举！
    for (int bridge = 0; bridge < n; bridge++)
    { // 跳板
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                // i -> .....bridge .... -> j
                // distance[i][j]能不能缩短
                // distance[i][j] = min ( distance[i][j] , distance[i][bridge] + distance[bridge][j])
                if (dist[i][bridge] != numeric_limits<int>::max() && dist[bridge][j] != numeric_limits<int>::max() &&
                    dist[i][j] > dist[i][bridge] + dist[bridge][j])
                {
                    dist[i][j] = dist[i][bridge] + dist[bridge][j];
                }
            }
        }
    }
}

int main()
{

    while (cin >> n >> m)
    {
        for (int i = 0; i < m; i++)
        {
            cin >> path[i];
            path[i]--; // 转换为 0-index
        }
        // 这道题给的图是邻接矩阵的形式
        build();
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> dist[i][j];
            }
        }
        floyd();
        ans = 0;
        for (int i = 1; i < m; i++)
        {
            ans += dist[path[i - 1]][path[i]];
        }
        cout << ans << endl;
    }

    return 0;
}