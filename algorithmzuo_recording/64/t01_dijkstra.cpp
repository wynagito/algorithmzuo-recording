// Dijkstra算法：给定一个源点，求解从源点到每个点的最短路径长度。单源最短路径算法。
// 适用范围：有向图、边的权值没有负数

// 彻底暴力的Dijkstra算法，不讲、时间复杂度太差、无意义

// 普通堆实现的Dijkstra算法，最普遍、最常用
// 算法核心过程：
// 节点弹出过就忽略
// 节点没弹出过，让其它没弹出节点距离变小的记录加入堆

// 反向索引堆实现的Dijkstra算法，最快速、最极致
// 核心在于掌握反向索引堆

// 普通堆实现的Dijkstra算法，时间复杂度O(m * log m)，m为边数

// 1，distance[i]表示从源点到i点的最短距离，visited[i]表示i节点是否从小根堆弹出过
// 2，准备好小根堆，小根堆存放记录：(x点，源点到x的距离)，小根堆根据距离组织
// 3，令distance[源点]=0，(源点，0)进入小根堆
// 4，从小根堆弹出(u点，源点到u的距离)
//    a. 如果visited[u] == true，不做任何处理，重复步骤4
//    b. 如果visited[u] == false，令visited[u] = true，u就算弹出过了
//       然后考察u的每一条边，假设某边去往v，边权为w
//       1）如果visited[v] == false 并且 distance[u] + w < distance[v]
//          令distance[v] = distance[u] + w，把(v, distance[u] + w)加入小根堆
//       2）处理完u的每一条边之后，重复步骤4
// 5，小根堆为空过程结束，distance表记录了源点到每个节点的最短距离。

// 反向索引堆实现的Dijkstra算法，时间复杂度O(m * log n)，n为节点数，m为边数

// 1，准备好反向索引堆，根据源点到当前点的距离组织小根堆，可以做到如下操作
//    a. 新增记录(x, 源点到x的距离)   b. 当源点到x的距离更新时，可以进行堆的调整
//    c. x点一旦弹出，以后忽略x       d. 弹出堆顶的记录(u, 源点到u的距离)
// 2，把(源点，0)加入反向索引堆，过程开始
// 3，反向索引堆弹出(u，源点到u的距离)，考察u的每一条边，假设某边去往v，边权为w
//    1）如果v没有进入过反向索引堆里，新增记录(v, 源点到u的距离 + w)
//    2）如果v曾经从反向索引堆弹出过，忽略
//    3）如果v在反向索引堆里，看看源点到v的距离能不能变得更小，如果能，调整堆；不能，忽略
//    4）处理完u的每一条边，重复步骤3
// 4 反向索引堆为空过程结束。反向索引堆里记录了源点到每个节点的最短距离。

// Dijkstra算法模版（Leetcode）
// 网络延迟时间
// 有 n 个网络节点，标记为 1 到 n
// 给你一个列表 times，表示信号经过 有向 边的传递时间
// times[i] = (ui, vi, wi)，表示从ui到vi传递信号的时间是wi
// 现在，从某个节点 s 发出一个信号
// 需要多久才能使所有节点都收到信号
// 如果不能使所有节点收到信号，返回 -1
// 测试链接 : https://leetcode.cn/problems/network-delay-time

struct cmp
{
    bool operator()(const pair<int, int> &a, const pair<int, int> &b)
    {
        return a.second > b.second;
    }
};

class Solution
{
public:
    int networkDelayTime(vector<vector<int>> &times, int n, int k)
    {
        bool visit[110] = {false};
        int dis[110];
        for (int i = 1; i <= n; ++i)
        {
            dis[i] = INT_MAX;
            visit[i] = false;
        }
        vector<vector<pair<int, int>>> graph(n + 1);
        for (auto vv : times)
        {
            graph[vv[0]].push_back({vv[1], vv[2]});
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> qu;
        qu.push({k, 0});
        dis[k] = 0;
        while (!qu.empty())
        {
            auto f = qu.top();
            qu.pop();
            if (visit[f.first])
                continue;
            visit[f.first] = true;
            for (auto e : graph[f.first])
            {
                if (!visit[e.first] && dis[f.first] + e.second < dis[e.first])
                {
                    dis[e.first] = dis[f.first] + e.second;
                    qu.push({e.first, dis[e.first]});
                }
            }
        }
        int ans = INT_MIN;
        for (int i = 1; i <= n; ++i)
        {
            if (dis[i] == INT_MAX)
                return -1;
            ans = max(ans, dis[i]);
        }
        return ans;
    }
};

// Dijkstra算法模版（洛谷）
// 静态空间实现 : 链式前向星 + 反向索引堆
// 测试链接 : https://www.luogu.com.cn/problem/P4779

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 100001;
const int MAXM = 200001;

// 链式前向星
vector<int> head(MAXN, -1);
vector<int> nextEdge(MAXM);
vector<int> to(MAXM);
vector<int> weight(MAXM);
int cnt = 1;

// 反向索引堆
vector<int> heap(MAXN);

// where[v] = -1，表示v这个节点，从来没有进入过堆
// where[v] = -2，表示v这个节点，已经弹出过了
// where[v] = i(>=0)，表示v这个节点，在堆上的i位置
vector<int> where(MAXN, -1);
vector<int> dist(MAXN, INT_MAX);
int heapSize = 0;

void build(int n);
void addEdge(int u, int v, int w);
void addOrUpdateOrIgnore(int v, int w);
void heapInsert(int i);
int pop();
void heapify(int i);
void swap(int i, int j);
bool isEmpty();

void build(int n)
{
    cnt = 1;
    heapSize = 0;
    fill(head.begin(), head.begin() + n + 1, -1);
    fill(where.begin(), where.begin() + n + 1, -1);
    fill(dist.begin(), dist.begin() + n + 1, INT_MAX);
}

// Add an edge to the graph
void addEdge(int u, int v, int w)
{
    nextEdge[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

// Insert or update distance of a node in the priority queue
void addOrUpdateOrIgnore(int v, int w)
{
    if (where[v] == -1)
    {
        heap[heapSize] = v;
        where[v] = heapSize++;
        dist[v] = w;
        heapInsert(where[v]);
    }
    else if (where[v] >= 0)
    {
        dist[v] = min(dist[v], w);
        heapInsert(where[v]);
    }
}

// Maintain heap property by inserting an element at index i
void heapInsert(int i)
{
    while (dist[heap[i]] < dist[heap[(i - 1) / 2]])
    {
        swap(i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

// Pop the smallest element from the heap
int pop()
{
    int ans = heap[0];
    swap(0, --heapSize);
    heapify(0);
    where[ans] = -2;
    return ans;
}

// Restore the heap property by recursively heapifying
void heapify(int i)
{
    int l = i * 2 + 1;
    while (l < heapSize)
    {
        int best = (l + 1 < heapSize && dist[heap[l + 1]] < dist[heap[l]]) ? l + 1 : l;
        best = (dist[heap[best]] < dist[heap[i]]) ? best : i;
        if (best == i)
            break;
        swap(best, i);
        i = best;
        l = i * 2 + 1;
    }
}

// Swap two elements in the heap
void swap(int i, int j)
{
    int tmp = heap[i];
    heap[i] = heap[j];
    heap[j] = tmp;
    where[heap[i]] = i;
    where[heap[j]] = j;
}

// Check if the heap is empty
bool isEmpty()
{
    return heapSize == 0;
}

// Dijkstra's algorithm
void dijkstra(int s, int n)
{
    addOrUpdateOrIgnore(s, 0);
    while (!isEmpty())
    {
        int v = pop();
        for (int ei = head[v]; ei != -1; ei = nextEdge[ei])
        {
            addOrUpdateOrIgnore(to[ei], dist[v] + weight[ei]);
        }
    }
}

int main()
{
    int n, m, s;
    while (cin >> n >> m >> s)
    {
        build(n);
        for (int i = 0, u, v, w; i < m; i++)
        {
            cin >> u >> v >> w;
            addEdge(u, v, w);
        }
        dijkstra(s, n);
        cout << dist[1];
        for (int i = 2; i <= n; i++)
        {
            cout << " " << dist[i];
        }
        cout << endl;
    }
    return 0;
}
