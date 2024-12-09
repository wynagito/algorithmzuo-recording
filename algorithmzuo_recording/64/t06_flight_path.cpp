// 飞行路线
// Alice和Bob现在要乘飞机旅行，他们选择了一家相对便宜的航空公司
// 该航空公司一共在n个城市设有业务，设这些城市分别标记为0 ~ n−1
// 一共有m种航线，每种航线连接两个城市，并且航线有一定的价格
// Alice 和 Bob 现在要从一个城市沿着航线到达另一个城市，途中可以进行转机
// 航空公司对他们这次旅行也推出优惠，他们可以免费在最多k种航线上搭乘飞机
// 那么 Alice 和 Bob 这次出行最少花费多少
// 测试链接 : https://www.luogu.com.cn/problem/P4568

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

const int MAXN = 10001;
const int MAXM = 100001;
const int MAXK = 11;

// 链式前向星建图需要
vector<int> head(MAXN, 0);
vector<int> nxt(MAXM);
vector<int> to(MAXM);
vector<int> weight(MAXM);
int cnt;

// Dijkstra需要
vector<vector<int>> dist(MAXN, vector<int>(MAXK, INT_MAX));
vector<vector<bool>> visited(MAXN, vector<bool>(MAXK, false));

// 用语言自己提供的堆
// 动态结构，不推荐
// 0 : 到达的城市编号
// 1 : 已经使用的免单次数
// 2 : 沿途的花费
auto cmp = [](const vector<int> &a, const vector<int> &b)
{ return a[2] > b[2]; };
priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> heap(cmp);

int n, m, k, s, t;

void build()
{
    cnt = 1;
    for (int i = 0; i < n; i++)
    {
        head[i] = 0;
        for (int j = 0; j <= k; j++)
        {
            dist[i][j] = INT_MAX;
            visited[i][j] = false;
        }
    }
    while (!heap.empty())
    {
        heap.pop();
    }
}

void addEdge(int u, int v, int w)
{
    nxt[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

int dijkstra()
{
    dist[s][0] = 0;
    heap.push({s, 0, 0});

    while (!heap.empty())
    {
        auto record = heap.top();
        heap.pop();
        int u = record[0];
        int use = record[1];
        int cost = record[2];

        if (visited[u][use])
        {
            continue;
        }
        visited[u][use] = true;

        if (u == t)
        {
            // 常见剪枝
            // 发现终点直接返回
            // 不用等都结束
            return cost;
        }

        for (int ei = head[u], v, w; ei > 0; ei = nxt[ei])
        {
            v = to[ei];
            w = weight[ei];
            if (use < k && dist[v][use + 1] > dist[u][use])
            {
                // 使用免费
                dist[v][use + 1] = dist[u][use];
                heap.push({v, use + 1, dist[v][use + 1]});
            }
            if (dist[v][use] > dist[u][use] + w)
            {
                // 不用免费
                dist[v][use] = dist[u][use] + w;
                heap.push({v, use, dist[v][use]});
            }
        }
    }
    return -1;
}

int main()
{

    while (cin >> n >> m >> k >> s >> t)
    {
        build();
        for (int i = 0, a, b, c; i < m; i++)
        {
            cin >> a >> b >> c;
            addEdge(a, b, c);
            addEdge(b, a, c);
        }
        cout << dijkstra() << '\n';
    }

    return 0;
}