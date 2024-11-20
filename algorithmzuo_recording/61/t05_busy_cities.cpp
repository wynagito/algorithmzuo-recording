// 繁忙的都市
// 一个非常繁忙的大都市，城市中的道路十分的拥挤，于是市长决定对其中的道路进行改造
// 城市的道路是这样分布的：城市中有n个交叉路口，有些交叉路口之间有道路相连
// 两个交叉路口之间最多有一条道路相连接，这些道路是双向的
// 且把所有的交叉路口直接或间接的连接起来了
// 每条道路都有一个分值，分值越小表示这个道路越繁忙，越需要进行改造
// 但是市政府的资金有限，市长希望进行改造的道路越少越好，于是他提出下面的要求：
// 1. 改造的那些道路能够把所有的交叉路口直接或间接的连通起来
// 2. 在满足要求1的情况下，改造的道路尽量少
// 3. 在满足要求1、2的情况下，改造的那些道路中分值最大的道路分值尽量小
// 作为市规划局的你，应当作出最佳的决策，选择哪些道路应当被修建
// 返回选出了几条道路 以及 分值最大的那条道路的分值是多少
// 测试链接 : https://www.luogu.com.cn/problem/P2330

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 301, MAXM = 8001;

int father[MAXN];
vector<vector<int>> edges(MAXM, vector<int>(3));

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
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edges[i][0] = u;
        edges[i][1] = v;
        edges[i][2] = w;
    }
    sort(edges.begin(), edges.begin() + m, [](vector<int> a, vector<int> b)
         { return a[2] < b[2]; });
    int ans = 0, cnt = 0;
    for (int i = 1; i <= m; i++)
    {
        int u = edges[i][0], v = edges[i][1], w = edges[i][2];
        if (merge(u, v))
        {
            cnt++;
            ans = max(ans, w);
        }
        if (cnt == n - 1)
        {
            break;
        }
    }
    cout << cnt << " " << ans << endl;
    return 0;
}