// 高斯消元解决加法方程组模版(区分是否有唯一解)
// 一共有n个变量，给定n个加法方程，构成一个加法方程组
// 如果方程组存在矛盾或者无法确定唯一解，打印"No Solution"
// 如果方程组存在唯一解，打印每个变量的值，保留小数点后两位
// 1 <= n <= 100
// 测试链接 : https://www.luogu.com.cn/problem/P3389

#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

const int MAXN = 102;
// 0.0000001 == 1e-7
// 因为double类型有精度问题，所以认为
// 如果一个数字绝对值 <  sml，则认为该数字是0
// 如果一个数字绝对值 >= sml，则认为该数字不是0
const double sml = 1e-7;

double mat[MAXN][MAXN];
int n;

// 高斯消元法
// 需要保证变量有n个，表达式也有n个
int gauss(int n)
{
    for (int i = 1; i <= n; i++)
    {
        // 找到当前列的最大值
        int max = i;
        for (int j = i + 1; j <= n; j++)
        {
            if (fabs(mat[j][i]) > fabs(mat[max][i]))
            {
                max = j;
            }
        }
        // 交换行
        swap(mat[i], mat[max]);

        // 检查当前主元是否为零
        if (fabs(mat[i][i]) < sml)
        {
            return 0;
        }

        double tmp = mat[i][i];
        for (int j = i; j <= n + 1; j++)
        {
            mat[i][j] /= tmp; // 归一化当前行
        }

        for (int j = 1; j <= n; j++)
        {
            if (i != j)
            {
                double rate = mat[j][i] / mat[i][i];
                for (int k = i; k <= n + 1; k++)
                {
                    mat[j][k] -= mat[i][k] * rate; // 消元
                }
            }
        }
    }
    return 1;
}

int main()
{
    // 输入数据
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n + 1; j++)
        {
            cin >> mat[i][j];
        }
    }

    int sign = gauss(n);
    if (sign == 0)
    {
        cout << "No Solution" << endl;
    }
    else
    {
        // 输出结果
        for (int i = 1; i <= n; i++)
        {
            prinf("%.2lf\n", mat[i][n + 1]);
        }
    }

    return 0;
}