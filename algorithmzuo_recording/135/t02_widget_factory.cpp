// 工具工厂
// 一共有n种工具，编号1~n，一共有m条记录，其中一条记录格式如下：
// 4 WED SUN 13 18 1 13
// 表示有个工人一共加工了4件工具，从某个星期三开始工作，到某个星期天结束工作
// 加工的工具依次为13号、18号、1号、13号
// 每个工人在工作期间不休息，每件工具都是串行加工的，完成一件后才开始下一件
// 每种工具制作天数是固定的，并且任何工具的制作天数最少3天、最多9天
// 但该数据丢失了，所以现在需要根据记录，推断出每种工具的制作天数
// 如果记录之间存在矛盾，打印"Inconsistent data."
// 如果记录无法确定每种工具的制作天数，打印"Multiple solutions."
// 如果记录能够确定每种工具的制作天数，打印所有结果
// 1 <= n、m <= 300
// 测试链接 : http://poj.org/problem?id=2947

#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MOD = 7;

const int MAXN = 302;

int mat[MAXN][MAXN];
int inv[MOD];
string days[7] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};

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
void prepare(int s)
{
    for (int i = 1; i <= s; i++)
    {
        for (int j = 1; j <= s + 1; j++)
        {
            mat[i][j] = 0;
        }
    }
}

// 将字符串转换为对应的星期几
int day(const string &str)
{
    for (int i = 0; i < 7; i++)
    {
        if (str == days[i])
        {
            return i;
        }
    }
    return -1;
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
                        for (int k = j; k < i; k++)
                        {
                            mat[j][k] = (mat[j][k] * a) % MOD;
                        }
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
            bool flag = false;
            for (int j = i + 1; j <= n; j++)
            {
                if (mat[i][j] != 0)
                {
                    flag = true;
                    break;
                }
            }
            if (!flag)
            {
                mat[i][n + 1] = (mat[i][n + 1] * inv[mat[i][i]]) % MOD; // 使用逆元
                mat[i][i] = 1;
            }
        }
    }
}

int main()
{
    computeInverse();

    int n, m;
    while (cin >> n >> m)
    {
        if (n == 0 && m == 0)
        {
            break;
        }

        int s = max(n, m);
        prepare(s);

        for (int i = 1; i <= m; i++)
        {
            int k;
            cin >> k;
            string st, et;
            cin >> st >> et;

            for (int j = 1; j <= k; j++)
            {
                int tool;
                cin >> tool;
                mat[i][tool] = (mat[i][tool] + 1) % MOD; // 更新工具数量
            }

            mat[i][s + 1] = ((day(et) - day(st) + 1) % MOD + MOD) % MOD; // 计算时间差
        }

        gauss(s);

        int sign = 1;
        for (int i = 1; i <= s; i++)
        {
            if (mat[i][i] == 0 && mat[i][s + 1] != 0)
            {
                sign = -1; // 发现矛盾
                break;
            }
            if (i <= n && mat[i][i] == 0)
            {
                sign = 0; // 多解
            }
        }

        if (sign == -1)
        {
            cout << "Inconsistent data." << endl;
        }
        else if (sign == 0)
        {
            cout << "Multiple solutions." << endl;
        }
        else
        {
            for (int i = 1; i <= n; i++)
            {
                if (mat[i][s + 1] < 3)
                {
                    mat[i][s + 1] += 7; // 确保结果大于等于0
                }
            }
            for (int i = 1; i < n; i++)
            {
                cout << mat[i][s + 1] << " ";
            }
            cout << mat[n][s + 1] << endl;
        }
    }

    return 0;
}
