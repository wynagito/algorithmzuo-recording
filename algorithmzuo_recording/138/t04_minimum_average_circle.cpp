// 最小圈
// 一共有n个节点，m条有向边，每条边有权值
// 这个有向带权图中，可能有若干环，规定环的平均值为
// 环中边的权值和 / 环中边的数量
// 返回所有环的平均值中最少的平均值，结果保留小数点后8位，其余部分舍弃
// 1 <= n <= 3000
// 1 <= m <= 10000
// -10^7 <= 边权 <= 10^7
// 测试链接 : https://www.luogu.com.cn/problem/P3199

#include <iostream>
#include <vector>
#include <cstring>
#include <limits>
#include <iomanip>

using namespace std;

const int MAXN = 3001;
const int MAXM = 10001;
const double MAXE = 1e7;
const double sml = 1e-9;

vector<int> head(MAXN);
vector<int> nextarr(MAXM);
vector<int> to(MAXM);
vector<double> weight(MAXM);
int cnt;

vector<double> value(MAXN);
vector<bool> path(MAXN);
int n, m;

void prepare();
void addEdge(int u, int v, double w);
bool dfs(int u, double x);
bool check(double x);

void prepare()
{
    cnt = 1;
    fill(head.begin() + 1, head.begin() + n + 1, 0);
}

void addEdge(int u, int v, double w)
{
    nextarr[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

bool dfs(int u, double x)
{
    if (u == 0)
    {
        // 认为0号点是超级源点，具有通往所有点的有向边
        for (int i = 1; i <= n; i++)
        {
            if (dfs(i, x))
            {
                return true;
            }
        }
    }
    else
    {
        path[u] = true;
        for (int e = head[u]; e != 0; e = nextarr[e])
        {
            int v = to[e];
            double w = weight[e] - x;
            // 只有v的累积边权变小，才会递归，非常强的剪枝
            if (value[v] > value[u] + w)
            {
                value[v] = value[u] + w;
                if (path[v] || dfs(v, x))
                {
                    return true;
                }
            }
        }
        path[u] = false;
    }
    return false;
}

bool check(double x)
{
    fill(value.begin() + 1, value.begin() + n + 1, 0);
    fill(path.begin() + 1, path.begin() + n + 1, false);
    return dfs(0, x);
}

int main()
{
    cout << fixed << setprecision(8);

    cin >> n >> m;
    prepare();

    for (int i = 1; i <= m; i++)
    {
        int u, v;
        double w;
        cin >> u >> v >> w;
        addEdge(u, v, w);
    }

    double l = -MAXE, r = MAXE, x, ans = 0;
    while (l < r && r - l >= sml)
    {
        x = (l + r) / 2;
        if (check(x))
        {
            r = x - sml;
        }
        else
        {
            ans = x;
            l = x + sml;
        }
    }

    cout << ans << endl;
    return 0;
}