// Kruskal算法模版（洛谷）
// 静态空间实现
// 测试链接 : https://www.luogu.com.cn/problem/P3366

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 5001, MAXM = 200001;

int father[MAXN];

// u, v, w
vector<vector<int>> edges(MAXM, vector<int>(3, 0));

int n, m;

void build()
{
    for (int i = 1; i <= n; i++)
    {
        father[i] = i;
    }
}

int find(int i)
{
    if (i != father[i])
    {
        father[i] = find(father[i]);
    }
    return father[i];
}

// 如果x和y本来就是一个集合，返回false
// 如果x和y不是一个集合，合并之后返回true
bool merge(int x, int y)
{
    int fx = find(x);
    int fy = find(y);
    if (fx != fy)
    {
        father[fx] = fy;
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    cin >> n >> m;
    build();
    for (int i = 0; i < m; i++)
    {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }
    sort(edges.begin(), edges.begin() + m, [](vector<int> a, vector<int> b)
         { return a[2] < b[2]; });
    int ans = 0;
    int cnt = 0;
    for (int i = 0; i < m; i++)
    {
        int x = edges[i][0];
        int y = edges[i][1];
        int w = edges[i][2];
        if (merge(x, y))
        {
            cnt++;
            ans += w;
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