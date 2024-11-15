// 拓扑排序模版（牛客）
// 邻接表建图（动态方式）
// 测试链接 : https://www.nowcoder.com/practice/88f7e156ca7d43a1a535f619cd3f495c

#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 200001;

int queue[MAXN];
int indegree[MAXN];
int ans[MAXN];
int l, r;
int n, m;

bool topoSort(vector<vector<int>> &graph)
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
        for (int next : graph[cur])
        {
            if (--indegree[next] == 0)
            {
                queue[r++] = next;
            }
        }
    }
    return fill == n;
}

int main()
{
    cin >> n >> m;
    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        indegree[v]++;
    }
    if (topoSort(graph))
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