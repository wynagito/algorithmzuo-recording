// Prim算法模版（洛谷）
// 动态空间实现
// 测试链接 : https://www.luogu.com.cn/problem/P3366

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define x first
#define y second
typedef pair<int, int> PII;

struct cmp
{
    bool operator()(PII a, PII b)
    {
        return a.y > b.y;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<PII>> g(n + 1);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    priority_queue<PII, vector<PII>, cmp> pq;
    vector<bool> vis(n + 1, false);
    for (PII p : g[1])
    {
        pq.push(p);
    }
    vis[1] = true;
    int ans = 0;
    int cnt = 0;
    while (!pq.empty())
    {
        PII p = pq.top();
        pq.pop();
        if (vis[p.x])
            continue;
        ans += p.y;
        cnt++;
        vis[p.x] = true;
        for (PII q : g[p.x])
        {
            if (!vis[q.x])
            {
                pq.push(q);
            }
        }
    }
    if (cnt < n - 1)
    {
        cout << "orz" << endl;
    }
    else
    {
        cout << ans << endl;
    }
    return 0;
}