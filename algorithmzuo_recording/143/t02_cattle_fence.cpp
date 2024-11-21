// 牛场围栏
// 给定一个长度为n的数组arr, arr[i]代表第i种木棍的长度，每种木棍有无穷多个
// 给定一个正数m，表示你可以把任何一根木棍消去最多m的长度，同一种木棍可以消去不同的长度
// 你可以随意拼接木棍形成一个长度，返回不能拼出来的长度中，最大值是多少
// 如果你可以拼出所有的长度，返回-1
// 如果不能拼出来的长度有无穷多，返回-1
// 1 <= n <= 100
// 1 <= arr[i] <= 3000
// 1 <= m <= 3000
// 测试链接 : https://www.luogu.com.cn/problem/P2662

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
#include <climits>

using namespace std;

const int MAXN = 101;
const int MAXV = 3001;
const int MAXM = 30001;
const int inf = INT_MAX;

int n, m, x;
int arr[MAXN];
bool set[MAXV];
int head[MAXV], nxt[MAXM], to[MAXM], weight[MAXM];
int cnt;

// Dijkstra 算法需要
vector<int> dist(MAXV);
bool visited[MAXV];

// 准备函数
void prepare()
{
    cnt = 1;
    dist.assign(MAXV, inf);
    fill(set, set + MAXV, false);
    memset(head, 0, sizeof(head));
    memset(visited, 0, sizeof(visited));
}

// 添加边
void addEdge(int u, int v, int w)
{
    nxt[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

// Dijkstra 算法
void dijkstra()
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
    heap.push({0, 0});
    dist[0] = 0;

    while (!heap.empty())
    {
        auto cur = heap.top();
        heap.pop();
        int w = cur.first;
        int u = cur.second;

        if (visited[u])
        {
            continue;
        }
        visited[u] = true;

        for (int ei = head[u]; ei > 0; ei = nxt[ei])
        {
            int v = to[ei];
            if (!visited[v] && dist[v] > w + weight[ei])
            {
                dist[v] = w + weight[ei];
                heap.push({dist[v], v});
            }
        }
    }
}

int compute()
{
    int ans = 0;
    if (x == 1)
    {
        ans = -1;
    }
    else
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = max(1, arr[i] - m); j <= arr[i]; j++)
            {
                if (!set[j])
                {
                    set[j] = true;
                    for (int k = 0; k < x; k++)
                    {
                        addEdge(k, (k + j) % x, j);
                    }
                }
            }
        }
        dijkstra();
        for (int i = 1; i < x; i++)
        {
            if (dist[i] == inf)
            {
                ans = -1;
                break;
            }
            ans = max(ans, dist[i] - x);
        }
    }
    return ans;
}

int main()
{

    cin >> n >> m;
    x = inf;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
        x = min(x, max(1, arr[i] - m));
    }

    prepare();
    cout << compute() << endl;

    return 0;
}