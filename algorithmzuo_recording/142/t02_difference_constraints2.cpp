// 负环和差分约束模版题(转化成形式2进而转化成判断无限增加的环)
// 一共有n个变量，编号1~n，给定m个不等式，每个不等式的形式为
// Xi - Xj <= Ci，其中Xi和Xj为变量，Ci为常量
// 如果不等式存在矛盾导致无解，打印"NO"
// 如果有解，打印满足所有不等式的其中一组解(X1, X2...)
// 1 <= n、m <= 5 * 10^3
// -10^4 <= Ci <= +10^4
// 测试链接 : https://www.luogu.com.cn/problem/P5960

#include <iostream>
#include <limits>
#include <cstring>

using namespace std;

const int MAXN = 5001;
const int MAXM = 10001;
const int MAXQ = 5000001;

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt;

// spfa需要的
int dist[MAXN];
int update[MAXN];

int queue[MAXQ];
int h, t;

bool enter[MAXN];
int n, m;

void prepare()
{
    cnt = 1;
    h = t = 0;
    memset(head, 0, sizeof(head[0]) * (n + 1));
    // 所有距离先设置成最大值
    fill(dist, dist + n + 1, numeric_limits<int>::min());
    fill(update, update + n + 1, 0);
    fill(enter, enter + n + 1, false);
}

void addEdge(int u, int v, int w)
{
    nxt[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

// 来自讲解065，spfa判断负环，s是超级源点
bool spfa(int s)
{
    dist[s] = 0;
    update[s] = 1;
    queue[t++] = s;
    enter[s] = true;

    while (h < t)
    {
        int u = queue[h++];
        enter[u] = false;
        for (int ei = head[u]; ei > 0; ei = nxt[ei])
        {
            int v = to[ei];
            int w = weight[ei];
            if (dist[v] < dist[u] + w)
            { // 变大才更新
                dist[v] = dist[u] + w;
                if (!enter[v])
                {
                    // 注意判断逻辑和讲解065的代码不一样
                    // 因为节点0是额外增加的超级源点
                    // 所以节点数量增加了1个，所以这么判断
                    if (++update[v] > n)
                    {
                        return true;
                    }
                    queue[t++] = v;
                    enter[v] = true;
                }
            }
        }
    }
    return false;
}

int main()
{

    cin >> n >> m;
    prepare();

    // 0号点是连通超级源点，保证图的连通性
    for (int i = 1; i <= n; i++)
    {
        addEdge(0, i, 0);
    }

    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        // 形式2的连边方式
        addEdge(u, v, -w);
    }

    if (spfa(0))
    {
        cout << "NO\n";
    }
    else
    {
        for (int i = 1; i <= n; i++)
        {
            cout << dist[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}