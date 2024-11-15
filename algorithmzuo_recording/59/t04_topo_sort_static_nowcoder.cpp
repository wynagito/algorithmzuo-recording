// 拓扑排序模版（牛客）
// 链式前向星建图（静态方式）
// 测试链接 : https://www.nowcoder.com/practice/88f7e156ca7d43a1a535f619cd3f495c

#include <iostream>

using namespace std;

const int MAXN = 200010;

int head[MAXN], nxt[MAXN], to[MAXN], cnt;
int indegree[MAXN], queue[MAXN];
int ans[MAXN];
int l, r;
int n, m;

void addEdge(int u, int v)
{
    nxt[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

bool topoSort()
{
    l = r = 0;
    for (int i = 1; i <= n; i++)
    {
        if (indegree[i] == 0)
        {
            queue[r++] = i;
        }
    }
    int fill = 0;
    while (l < r)
    {
        int cur = queue[l++];
        ans[fill++] = cur;
        for (int i = head[cur]; i > 0; i = nxt[i])
        {
            if (--indegree[to[i]] == 0)
            {
                queue[r++] = to[i];
            }
        }
    }
    return fill == n;
}

int main()
{
    cnt = 1;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        addEdge(u, v);
        indegree[v]++;
    }
    if (topoSort())
    {
        for (int i = 0; i < n - 1; i++)
        {
            cout << ans[i] << " ";
        }
        cout << ans[n - 1];
    }
    else
    {
        cout << -1;
    }
    return 0;
}