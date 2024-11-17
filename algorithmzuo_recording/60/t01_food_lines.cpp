// 利用拓扑排序的过程，上游节点逐渐推送消息给下游节点的技巧

// 最大食物链计数
// a -> b，代表a在食物链中被b捕食
// 给定一个有向无环图，返回
// 这个图中从最初级动物到最顶级捕食者的食物链有几条
// 测试链接 : https://www.luogu.com.cn/problem/P4017

#include <iostream>

const int MAXN = 5001, MAXM = 500001, MOD = 80112002;

// 链式前向星建图
int head[MAXN], next[MAXM], to[MAXM], cnt = 1;

// 拓扑排序需要的队列
// 拓扑排序需要的入度表
// 记录每条食物链的长度
int queue[MAXN], indegree[MAXN], lines[MAXN];

int n, m;

void addEdge(int u, int v)
{
    next[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

int ways()
{
    int l = 0;
    int r = 0;
    for (int i = 1; i <= n; i++)
    {
        if (indegree[i] == 0)
        {
            queue[r++] = i;
            lines[i] = 1;
        }
    }
    int ans = 0;
    while (l < r)
    {
        int u = queue[l++];
        if (head[u] == 0)
        {
            // 当前的u节点不再有后续邻居了
            ans = (ans + lines[u]) % MOD;
        }
        else
        {
            for (int ei = head[u], v; ei > 0; ei = next[ei])
            {
                // u -> v
                v = to[ei];
                lines[v] = (lines[v] + lines[u]) % MOD;
                if (--indegree[v] == 0)
                {
                    queue[r++] = v;
                }
            }
        }
    }
    return ans;
}

int main()
{
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        std::cin >> u >> v;
        addEdge(u, v);
        indegree[v]++;
    }
    std::cout << ways() << std::endl;
    return 0;
}