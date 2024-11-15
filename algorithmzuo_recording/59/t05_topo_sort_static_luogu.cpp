// 字典序最小的拓扑排序
// 要求返回所有正确的拓扑排序中 字典序最小 的结果
// 建图请使用链式前向星方式，因为比赛平台用其他建图方式会卡空间
// 测试链接 : https://www.luogu.com.cn/problem/U107394

#include <iostream>
#include <queue>

using namespace std;

const int MAXN = 200010;

int head[MAXN], nxt[MAXN], to[MAXN], cnt;
int indegree[MAXN];
int ans[MAXN];
priority_queue<int, vector<int>, greater<int>> q;
int n, m;

void addEdge(int u, int v)
{
    nxt[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

bool topoSort()
{
    for (int i = 1; i <= n; i++)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
        }
    }
    int fill = 0;
    while (!q.empty())
    {
        int cur = q.top();
        q.pop();
        ans[fill++] = cur;
        for (int i = head[cur]; i > 0; i = nxt[i])
        {
            if (--indegree[to[i]] == 0)
            {
                q.push(to[i]);
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
    return 0;
}