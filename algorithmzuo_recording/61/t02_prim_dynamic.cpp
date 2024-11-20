// Prim算法（不算常用）
// 1 解锁的点的集合叫set（普通集合）、解锁的边的集合叫heap（小根堆）。set和heap都为空。
// 2 可从任意点开始，开始点加入到set，开始点的所有边加入到heap
// 3 从heap中弹出权值最小的边e，查看边e所去往的点x
//    A. 如果x已经在set中，边e舍弃，重复步骤3
//    B. 如果x不在set中，边e属于最小生成树，把x加入set，重复步骤3
// 4 当heap为空，最小生成树的也就得到了
// 时间复杂度O(n + m) + O(m * log m)

// Prim算法的优化（比较难，不感兴趣可以跳过）请一定要对堆很熟悉！
// 1 小根堆里放(节点，到达节点的花费)，根据 到达节点的花费 来组织小根堆
// 2 小根堆弹出(u节点，到达u节点的花费y)，y累加到总权重上去，然后考察u出发的每一条边
//   假设，u出发的边，去往v节点，权重w
//   A. 如果v已经弹出过了（发现过），忽略该边
//   B. 如果v从来没有进入过堆，向堆里加入记录(v, w)
//   C. 如果v在堆里，且记录为(v, x)
//      1）如果w < x，则记录更新成(v, w)，然后调整该记录在堆中的位置（维持小根堆）
//      2）如果w >= x，忽略该边
// 3 重复步骤2，直到小根堆为空

// 时间复杂度O(n+m) + O((m+n) * log n)

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