// 高斯消元解决异或方程组模版题
// 有一个长度为n的数组arr，可能有重复值，数字都是long类型的正数
// 每个数拥有的质数因子一定不超过2000，每个数最多挑选一次
// 在至少要选一个数的情况下，你可以随意挑选数字乘起来
// 乘得的结果需要是完全平方数，请问有几种挑选数字的方法
// 方法数可能很大，结果对1000000007取余
// 1 <= n <= 300
// 1 <= arr[i] <= 10^18
// 测试链接 : https://acm.hdu.edu.cn/showproblem.php?pid=5833

#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>

using namespace std;

const int MOD = 1000000007;
const int MAXV = 2000;
const int MAXN = 305;

long arr[MAXN];
int mat[MAXN][MAXN];

// 收集2000以内的质数
int prime[MAXV + 1];
int cnt;

// 埃氏筛需要
bool visit[MAXV + 1];

// pow2[i] : 2的i次方 % MOD
int pow2[MAXN];
int n;

// 准备函数
void prepare()
{
    // 得到2000以内的质数
    for (int i = 2; i * i <= MAXV; i++)
    {
        if (!visit[i])
        {
            for (int j = i * i; j <= MAXV; j += i)
            {
                visit[j] = true;
            }
        }
    }

    cnt = 0;
    for (int i = 2; i <= MAXV; i++)
    {
        if (!visit[i])
        {
            prime[++cnt] = i;
        }
    }

    // 2的i次方 % MOD 的结果
    pow2[0] = 1;
    for (int i = 1; i < MAXN; i++)
    {
        pow2[i] = (1LL * pow2[i - 1] * 2) % MOD;
    }
}

// 高斯消元解决异或方程组模版
void gauss(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (j < i && mat[j][j] == 1)
            {
                continue;
            }
            if (mat[j][i] == 1)
            {
                swap(mat[i], mat[j]);
                break;
            }
        }
        if (mat[i][i] == 1)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i != j && mat[j][i] == 1)
                {
                    for (int k = i; k <= n + 1; k++)
                    {
                        mat[j][k] ^= mat[i][k];
                    }
                }
            }
        }
    }
}

// 计算主元和自由元
int compute()
{
    memset(mat, 0, sizeof(mat));
    long cur;
    for (int i = 1; i <= n; i++)
    {
        cur = arr[i];
        for (int j = 1; j <= cnt && cur != 0; j++)
        {
            while (cur % prime[j] == 0)
            {
                mat[j][i] ^= 1;
                cur /= prime[j];
            }
        }
    }
    gauss(cnt);

    int main = 0; // 主元的数量
    for (int i = 1; i <= cnt; i++)
    {
        if (mat[i][i] == 1)
        {
            main++;
        }
    }

    return (pow2[n - main] - 1 + MOD) % MOD; // 返回方法数 - 1
}

int main()
{
    prepare();
    int test;
    cin >> test;

    for (int t = 1; t <= test; t++)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> arr[i];
        }
        cout << "Case #" << t << ":\n";
        cout << compute() << endl;
    }

    return 0;
}
