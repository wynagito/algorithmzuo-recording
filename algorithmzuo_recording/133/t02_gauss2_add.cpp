// 高斯消元解决加法方程组模版(区分矛盾、多解、唯一解)
// 一共有n个变量，给定n个加法方程，构成一个加法方程组
// 如果方程组存在矛盾，打印-1
// 如果方程组无法确定唯一解，打印0
// 如果方程组存在唯一解，打印每个变量的值，保留小数点后两位
// 1 <= n <= 50
// 测试链接 : https://www.luogu.com.cn/problem/P2455

#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAXN = 52;
double mat[MAXN][MAXN];
int n;
const double sml = 1e-7;

// 交换函数
void swap(int a, int b)
{
    for (int j = 0; j <= n + 1; j++)
    {
        std::swap(mat[a][j], mat[b][j]);
    }
}

// 高斯消元解决加法方程组模版
void gauss(int n)
{
    for (int i = 1; i <= n; i++)
    {
        int max = i;
        for (int j = 1; j <= n; j++)
        {
            if (j < i && fabs(mat[j][j]) >= sml)
            {
                continue;
            }
            if (fabs(mat[j][i]) > fabs(mat[max][i]))
            {
                max = j;
            }
        }
        swap(i, max);
        if (fabs(mat[i][i]) >= sml)
        {
            double tmp = mat[i][i];
            for (int j = i; j <= n + 1; j++)
            {
                mat[i][j] /= tmp;
            }
            for (int j = 1; j <= n; j++)
            {
                if (i != j)
                {
                    double rate = mat[j][i] / mat[i][i];
                    for (int k = i; k <= n + 1; k++)
                    {
                        mat[j][k] -= mat[i][k] * rate;
                    }
                }
            }
        }
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n + 1; j++)
        {
            cin >> mat[i][j];
        }
    }
    gauss(n);

    int sign = 1;
    for (int i = 1; i <= n; i++)
    {
        // 存在矛盾
        if (fabs(mat[i][i]) < sml && fabs(mat[i][n + 1]) >= sml)
        {
            sign = -1;
            break;
        }
        // 无法确定唯一解
        if (fabs(mat[i][i]) < sml)
        {
            sign = 0;
        }
    }

    if (sign == 1)
    {
        for (int i = 1; i <= n; i++)
        {
            printf("x%d=%.2lf\n", i, mat[i][n + 1]);
        }
    }
    else
    {
        cout << sign << endl;
    }
    return 0;
}
