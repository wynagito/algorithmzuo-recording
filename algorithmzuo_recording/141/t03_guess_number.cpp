// 猜数字
// 给定两个长度为n数组，一组为r1，r2，r3...，另一组为m1，m2，m3...
// 其中第二组数字两两互质，求最小正数解x
// 要求x满足，mi | (x - ri)，即(x - ri)是mi的整数倍
// 1 <= n <= 10
// -10^9 <= ri <= +10^9
// 1 <= mi <= 6 * 10^3
// 所有mi的乘积 <= 10^18
// 测试链接 : https://www.luogu.com.cn/problem/P3868

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 11;
long long m[MAXN];
long long r[MAXN];

// 扩展欧几里得算法
long long d, x, y;

void exgcd(long long a, long long b)
{
    if (b == 0)
    {
        d = a;
        x = 1;
        y = 0;
    }
    else
    {
        exgcd(b, a % b);
        long long px = x;
        long long py = y;
        x = py;
        y = px - py * (a / b);
    }
}

// 位运算实现乘法
long long multiply(long long a, long long b, long long mod)
{
    a = (a % mod + mod) % mod;
    b = (b % mod + mod) % mod;
    long long ans = 0;
    while (b != 0)
    {
        if (b & 1)
        {
            ans = (ans + a) % mod;
        }
        a = (a + a) % mod;
        b >>= 1;
    }
    return ans;
}

// 扩展中国剩余定理
long long excrt(int n)
{
    long long tail = 0, lcm = 1, tmp, b, c, x0;
    for (int i = 1; i <= n; i++)
    {
        b = m[i];
        c = ((r[i] - tail) % b + b) % b; // 转化成非负数
        exgcd(lcm, b);
        if (c % d != 0)
        {
            return -1; // 无解
        }
        x0 = multiply(x, c / d, b / d);
        tmp = lcm * (b / d);
        tail = (tail + multiply(x0, lcm, tmp)) % tmp;
        lcm = tmp;
    }
    return tail;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> r[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> m[i];
    }
    // 题目输入的余数可能为负所以转化成非负数
    for (int i = 1; i <= n; i++)
    {
        r[i] = (r[i] % m[i] + m[i]) % m[i];
    }
    cout << excrt(n) << endl; // 扩展中国剩余定理解决
    return 0;
}