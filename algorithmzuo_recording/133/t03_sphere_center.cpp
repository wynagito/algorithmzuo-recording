// 球形空间的中心点
// 如果在n维空间中，那么表达一个点的位置，需要n个坐标的值
// 现在给定n+1个点，每个点都有n个坐标的值，代表在n维空间中的位置
// 假设这n+1个点都在n维空间的球面上，请返回球心的位置
// 球心的位置当然也是n个坐标的值，打印出来
// 在n维空间中，计算任意两点的距离，请用经典的欧式距离
// 1 <= n <= 10
// 坐标信息精确到小数点后6位，绝对值都不超过20000
// 测试链接 : https://www.luogu.com.cn/problem/P4035

#include <iostream>
#include <cmath>
#include <cstdio>

const int MAXN = 12;
double mat[MAXN][MAXN];
double data[MAXN][MAXN];
int n;

// 0.0000001 == 1e-7
// 因为double类型有精度问题，所以认为
// 如果一个数字绝对值 < sml，则认为该数字是0
// 如果一个数字绝对值 >= sml，则认为该数字不是0
const double sml = 1e-7;

void swap(int a, int b)
{
    for (int i = 1; i <= MAXN; i++)
    {
        std::swap(mat[a][i], mat[b][i]);
    }
}

// 高斯消元解决加法方程组模版
// 需要保证变量有n个，表达式也有n个
void gauss(int n)
{
    for (int i = 1; i <= n; i++)
    {
        // 如果想严格区分矛盾、多解、唯一解，一定要这么写
        int max = i;
        for (int j = 1; j <= n; j++)
        {
            if (j < i && std::abs(mat[j][j]) >= sml)
            {
                continue;
            }
            if (std::abs(mat[j][i]) > std::abs(mat[max][i]))
            {
                max = j;
            }
        }
        swap(i, max);
        if (std::abs(mat[i][i]) >= sml)
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
    std ::cin >> n;
    for (int i = 1; i <= n + 1; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            std ::cin >> data[i][j];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            mat[i][j] = 2 * (data[i][j] - data[i + 1][j]);
            mat[i][n + 1] += data[i][j] * data[i][j] - data[i + 1][j] * data[i + 1][j];
        }
    }
    gauss(n);
    for (int i = 1; i <= n; i++)
    {
        printf("%.3f ", mat[i][n + 1]);
    }
    return 0;
}
