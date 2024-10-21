// 格子全变成0的操作方案
// 有一个n*m的二维网格，给定每个网格的初始值，一定是0、1、2中的一个
// 如果某个网格获得了一些数值加成，也会用%3的方式变成0、1、2中的一个
// 比如有个网格一开始值是1，获得4的加成之后，值为(1+4)%3 = 2
// 有一个神奇的刷子，一旦在某个网格处刷一下，该网格会获得2的加成
// 并且该网格上、下、左、右的格子，都会获得1的加成
// 最终目标是所有网格都变成0，题目保证一定有解，但不保证唯一解
// 得到哪一种方案都可以，打印一共需要刷几下，并且把操作方案打印出来
// 1 <= n、m <= 30
// 测试链接 : https://acm.hdu.edu.cn/showproblem.php?pid=5755

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MOD = 3;
const int MAXS = 1001;

int mat[MAXS][MAXS];
int dir[5] = {0, -1, 0, 1, 0}; // 上、左、下、右
int n, m, s;
int inv[MOD];

// 计算逆元
void computeInverse()
{
    inv[1] = 1;
    for (int i = 2; i < MOD; i++)
    {
        inv[i] = (MOD - (long long)inv[MOD % i] * (MOD / i) % MOD) % MOD;
    }
}

// 求最大公约数
int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}

// 准备矩阵
void prepare()
{
    memset(mat, 0, sizeof(mat));
    int cur, row, col;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cur = i * m + j + 1;
            mat[cur][cur] = 2; // 自己的系数为2
            for (int d = 0; d < 4; d++)
            {
                row = i + dir[d];
                col = j + dir[d + 1];
                if (row >= 0 && row < n && col >= 0 && col < m)
                {
                    mat[cur][row * m + col + 1] = 1; // 与邻接的格子
                }
            }
        }
    }
}

// 高斯消元
void gauss(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (j < i && mat[j][j] != 0)
            {
                continue;
            }
            if (mat[j][i] != 0)
            {
                swap(mat[i], mat[j]);
                break;
            }
        }
        if (mat[i][i] != 0)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i != j && mat[j][i] != 0)
                {
                    int GCD = gcd(mat[j][i], mat[i][i]);
                    int a = mat[i][i] / GCD;
                    int b = mat[j][i] / GCD;
                    if (j < i && mat[j][j] != 0)
                    {
                        mat[j][j] = (mat[j][j] * a) % MOD;
                    }
                    for (int k = i; k <= n + 1; k++)
                    {
                        mat[j][k] = ((mat[j][k] * a - mat[i][k] * b) % MOD + MOD) % MOD;
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (mat[i][i] != 0)
        {
            mat[i][n + 1] = (mat[i][n + 1] * inv[mat[i][i]]) % MOD;
        }
    }
}

int main()
{
    computeInverse();

    int test;
    cin >> test;
    for (int t = 1; t <= test; t++)
    {
        cin >> n >> m;
        s = n * m;
        prepare();
        for (int i = 1; i <= s; i++)
        {
            int value;
            cin >> value;
            mat[i][s + 1] = (3 - value) % MOD; // 右侧常数项
        }
        gauss(s);

        int ans = 0;
        for (int i = 1; i <= s; i++)
        {
            ans += mat[i][s + 1];
        }
        cout << ans << endl;

        for (int i = 1, id = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++, id++)
            {
                while (mat[id][s + 1]-- > 0)
                {
                    cout << i << " " << j << endl;
                }
            }
        }
    }

    return 0;
}
