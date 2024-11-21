// 墨墨的等式(dijkstra算法)
// 一共有n种正数，每种数可以选择任意个，个数不能是负数
// 那么一定有某些数值可以由这些数字累加得到
// 请问在[l...r]范围上，有多少个数能被累加得到
// 0 <= n <= 12
// 0 <= 数值范围 <= 5 * 10^5
// 1 <= l <= r <= 10^12
// 测试链接 : https://www.luogu.com.cn/problem/P2371

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>

using namespace std;

const int MAXN = 500001;
const int MAXM = 5000001;

int n, x;
long l, r;

// 链式前向星需要
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
long weight[MAXM];
int cnt;

// dijkstra算法需要
// 0 : 当前节点
// 1 : 源点到当前点距离
priority_queue<pair<long, int>, vector<pair<long, int>>, greater<pair<long, int>>> heap;
long dist[MAXN];
bool visited[MAXN];

void prepare()
{
    cnt = 1;
    heap = priority_queue<pair<long, int>, vector<pair<long, int>>, greater<pair<long, int>>>();
    memset(head, 0, sizeof(head));
    fill(dist, dist + x, LONG_MAX);
    memset(visited, false, sizeof(visited));
}

void addEdge(int u, int v, long w)
{
    nxt[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

void dijkstra()
{
    heap.push({0, 0});
    dist[0] = 0;
    while (!heap.empty())
    {
        auto cur = heap.top();
        heap.pop();
        int u = cur.second;
        long w = cur.first;

        if (visited[u])
        {
            continue;
        }

        visited[u] = true;
        for (int ei = head[u], v; ei > 0; ei = nxt[ei])
        {
            v = to[ei];
            if (!visited[v] && dist[v] > w + weight[ei])
            {
                dist[v] = w + weight[ei];
                heap.push({dist[v], v});
            }
        }
    }
}

long compute()
{
    dijkstra();
    long ans = 0;
    for (int i = 0; i < x; i++)
    {
        if (r >= dist[i])
        {
            ans += (r - dist[i]) / x + 1;
        }
        if (l >= dist[i])
        {
            ans -= (l - dist[i]) / x + 1;
        }
    }
    return ans;
}

int main()
{

    cin >> n >> l >> r >> x;
    l--; // 转换为0索引

    prepare();
    for (int i = 2; i <= n; i++)
    {
        int vi;
        cin >> vi;
        for (int j = 0; j < x; j++)
        {
            addEdge(j, (j + vi) % x, vi);
        }
    }
    cout << compute() << endl;

    return 0;
}
