// 最佳团体
// 给定一棵树，节点编号0~n，0号节点是整棵树的头
// 编号1~n的节点，每个节点都有招募花费和战斗值，0号节点这两个值都是0
// 给定每条边(a,b)，表示节点a的父节点是b，有些节点的父节点是0节点
// 当招募了某个节点，那么该节点及其上方的所有祖先节点都需要招募
// 除了0号节点之外，一共可以招募k个人，希望让
// 战斗值之和 / 招募花费之和，这个比值尽量大，答案只需保留三位小数，更大的精度舍弃
// 1 <= k <= n <= 2500
// 0 <= 招募花费、战斗值 <= 10^4
// 测试链接 : https://www.luogu.com.cn/problem/P4322

#include <iostream>
#include <vector>
#include <cstring>
#include <iomanip>
#include <algorithm>

using namespace std;

const int MAXN = 3001;
const double NA = -1e9;
const double sml = 1e-6;
int head[MAXN], nextarr[MAXN], to[MAXN], edgeCnt;
int cost[MAXN], strength[MAXN], dfn[MAXN], dfnCnt;
double value[MAXN], dp[MAXN][MAXN];
int sizearr[MAXN], k, n;

void prepare();
void addEdge(int u, int v);
int dfs(int u);
bool check(double x);

void prepare()
{
    edgeCnt = 1;
    dfnCnt = 0;
    memset(head, 0, sizeof(head));
}

void addEdge(int u, int v)
{
    nextarr[edgeCnt] = head[u];
    to[edgeCnt] = v;
    head[u] = edgeCnt++;
}

int dfs(int u)
{
    int i = ++dfnCnt;
    dfn[u] = i;
    sizearr[i] = 1;
    for (int e = head[u], v; e != 0; e = nextarr[e])
    {
        v = to[e];
        sizearr[i] += dfs(v);
    }
    return sizearr[i];
}

bool check(double x)
{
    for (int i = 0; i <= n; i++)
    {
        value[dfn[i]] = (double)strength[i] - x * cost[i];
    }
    for (int j = 1; j <= k; j++)
    {
        dp[dfnCnt + 1][j] = NA;
    }
    for (int i = dfnCnt; i >= 2; i--)
    {
        for (int j = 1; j <= k; j++)
        {
            dp[i][j] = max(dp[i + sizearr[i]][j], value[i] + dp[i + 1][j - 1]);
        }
    }
    return dp[2][k] >= 0;
}

int main()
{
    cout << fixed << setprecision(3);

    cin >> k >> n;
    prepare();
    for (int i = 1; i <= n; i++)
    {
        cin >> cost[i] >> strength[i];
        int parent;
        cin >> parent;
        addEdge(parent, i);
    }
    dfs(0);

    double l = 0, r = 10000, x, ans = 0;
    while (l < r && r - l >= sml)
    {
        x = (l + r) / 2;
        if (check(x))
        {
            ans = x;
            l = x + sml;
        }
        else
        {
            r = x - sml;
        }
    }
    cout << ans << "\n";
    return 0;
}