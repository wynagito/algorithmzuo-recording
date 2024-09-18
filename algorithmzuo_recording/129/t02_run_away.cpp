// 跑路
// 一共有n个节点，编号1~n，一共有m条有向边，每条边1公里
// 有一个空间跑路器，每秒你都可以直接移动2^k公里，每秒钟可以随意决定k的值
// 题目保证1到n之间一定可以到达，返回1到n最少用几秒
// 2 <= n <= 50
// m <= 10^4
// k <= 64
// 测试链接 : https://www.luogu.com.cn/problem/P1613

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int MAXN = 61;
const int MAXP = 64;
const int NA = INT_MAX;

// st[i][j][p] : i到j的距离是不是2^p
bool st[MAXN][MAXN][MAXP + 1];

// timearr[i][j] : i到j的最短时间
int timearr[MAXN][MAXN];

int n, m;

void build()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            st[i][j][0] = false;
            timearr[i][j] = NA;
        }
    }
}

// Floyd算法
int compute()
{
    // 先枚举次方
    // 再枚举跳板
    // 最后枚举每一组(i,j)
    for (int p = 1; p <= MAXP; p++)
    {
        for (int jump = 1; jump <= n; jump++)
        {
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    if (st[i][jump][p - 1] && st[jump][j][p - 1])
                    {
                        st[i][j][p] = true;
                        timearr[i][j] = 1;
                    }
                }
            }
        }
    }

    if (timearr[1][n] != 1)
    {
        // 先枚举跳板
        // 最后枚举每一组(i,j)
        for (int jump = 1; jump <= n; jump++)
        {
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    if (timearr[i][jump] != NA && timearr[jump][j] != NA)
                    {
                        timearr[i][j] = min(timearr[i][j], timearr[i][jump] + timearr[jump][j]);
                    }
                }
            }
        }
    }
    return timearr[1][n];
}

int main()
{

    cin >> n;
    build();
    cin >> m;

    for (int i = 1, u, v; i <= m; i++)
    {
        cin >> u >> v;
        st[u][v][0] = true;
        timearr[u][v] = 1;
    }

    cout << compute() << endl;

    return 0;
}