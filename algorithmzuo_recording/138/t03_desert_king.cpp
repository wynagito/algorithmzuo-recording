// 最优比率生成树
// 一共有n个村庄，每个村庄由(x, y, z)表示
// 其中(x,y)代表村庄在二维地图中的位置，z代表其海拔高度
// 任意两个村庄之间的距离就是二维地图中的欧式距离
// 任意两个村庄之间的修路花费就是海拔差值的绝对值
// 现在想把所有村庄连通起来，希望修路的条数尽量少，同时希望让
// 总花费 / 总距离，这个比值尽量小，返回最小的比值是多少，结果保留小数点后3位其余部分舍弃
// 2 <= n <= 10^3
// 0 <= x、y <= 10^4
// 0 <= z <= 10^7
// 测试链接 : http://poj.org/problem?id=2728

#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <iomanip>
#include <sstream>

using namespace std;

const int MAXN = 1001;
const double sml = 1e-6;
int x[MAXN], y[MAXN], z[MAXN];
double dist[MAXN][MAXN], cost[MAXN][MAXN];
bool visit[MAXN];
double value[MAXN];
int n;

// 邻接矩阵结构下的prim算法，从节点1出发得到最小生成树的权值和
double prim(double x_param)
{
    for (int i = 1; i <= n; i++)
    {
        visit[i] = false;
        value[i] = cost[1][i] - x_param * dist[1][i];
    }

    visit[1] = true;
    double sum = 0;

    for (int i = 1; i <= n - 1; i++)
    {
        double minDist = numeric_limits<double>::max();
        int next = 0;

        for (int j = 1; j <= n; j++)
        {
            if (!visit[j] && value[j] < minDist)
            {
                minDist = value[j];
                next = j;
            }
        }

        sum += minDist;
        visit[next] = true;

        for (int j = 1; j <= n; j++)
        {
            if (!visit[j] && value[j] > cost[next][j] - x_param * dist[next][j])
            {
                value[j] = cost[next][j] - x_param * dist[next][j];
            }
        }
    }
    return sum;
}

int main()
{
    while (true)
    {
        cin >> n;
        if (n == 0)
            break;

        for (int i = 1; i <= n; i++)
        {
            cin >> x[i] >> y[i] >> z[i];
        }

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i != j)
                {
                    dist[i][j] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
                    cost[i][j] = abs(z[i] - z[j]);
                }
            }
        }

        double l = 0, r = 100, ans = 0;
        while (l < r && r - l >= sml)
        {
            double mid = (l + r) / 2;
            if (prim(mid) <= 0)
            {
                ans = mid;
                r = mid - sml;
            }
            else
            {
                l = mid + sml;
            }
        }
        cout << fixed << setprecision(3) << ans << endl;
    }

    return 0;
}