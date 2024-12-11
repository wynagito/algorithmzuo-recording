// Bellman-Ford + SPFA优化（Shortest Path Faster Algorithm）
// 很轻易就能发现，每一轮考察所有的边看看能否做松弛操作是不必要的
// 因为只有上一次被某条边松弛过的节点，所连接的边，才有可能引起下一次的松弛操作
// 所以用队列来维护 “这一轮哪些节点的distance变小了”
// 下一轮只需要对这些点的所有边，考察有没有松弛操作即可

// SPFA只优化了常数时间，在大多数情况下跑得很快，但时间复杂度为O(n*m)
// 看复杂度就知道只适用于小图，根据数据量谨慎使用，在没有负权边时要使用Dijkstra算法

// Bellman-Ford + SPFA优化的用途
// 1）适用于小图
// 2）解决有负边（没有负环）的图的单源最短路径问题
// 3）可以判断从某个点出发是否能遇到负环，如果想判断整张有向图有没有负环，需要设置虚拟源点
// 4）并行计算时会有很大优势，因为每一轮多点判断松弛操作是相互独立的，可以交给多线程处理

// Bellman-Ford + SPFA优化模版（洛谷）
// 给定n个点的有向图，请求出图中是否存在从顶点1出发能到达的负环
// 负环的定义是：一条边权之和为负数的回路
// 测试链接 : https://www.luogu.com.cn/problem/P3385

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using std::cin;
using std::cout;
using std::endl;
using std::fill;
using std::numeric_limits;
using std::queue;

const int MAXN = 2001;
const int MAXM = 6001;
const int MAXQ = 4000001;

// 链式前向星建图需要
int head[MAXN];
int next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt;

// SPFA需要
// 源点出发到每个节点的距离表
int distance[MAXN];
// 节点被松弛的次数
int updateCnt[MAXN];
// 节点是否已经在队列中
bool enter[MAXN];
// 哪些节点被松弛了放入队列
queue<int> q;

// 建图函数
void build(int n)
{
    cnt = 1;
    while (!q.empty())
        q.pop();
    fill(head + 1, head + n + 1, 0);
    fill(enter + 1, enter + n + 1, false);
    fill(distance + 1, distance + n + 1, numeric_limits<int>::max());
    fill(updateCnt + 1, updateCnt + n + 1, 0);
}

// 添加边函数
void addEdge(int u, int v, int w)
{
    next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

// Bellman-Ford + SPFA优化的模版
bool spfa(int n)
{
    distance[1] = 0;
    updateCnt[1]++;
    q.push(1);
    enter[1] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        enter[u] = false;
        for (int ei = head[u]; ei > 0; ei = next[ei])
        {
            int v = to[ei];
            int w = weight[ei];
            if (distance[u] + w < distance[v])
            {
                distance[v] = distance[u] + w;
                if (!enter[v])
                {
                    // 松弛次数超过n-1就有负环
                    if (++updateCnt[v] > n - 1)
                    {
                        return true;
                    }
                    q.push(v);
                    enter[v] = true;
                }
            }
        }
    }
    return false;
}

int main()
{
    int cases;
    cin >> cases;
    for (int i = 0; i < cases; i++)
    {
        int n, m;
        cin >> n >> m;
        build(n);
        for (int j = 0; j < m; j++)
        {
            int u, v, w;
            cin >> u >> v >> w;
            if (w >= 0)
            {
                addEdge(u, v, w);
                addEdge(v, u, w);
            }
            else
            {
                addEdge(u, v, w);
            }
        }
        cout << (spfa(n) ? "YES" : "NO") << endl;
    }
    return 0;
}