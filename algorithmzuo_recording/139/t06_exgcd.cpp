#include <iostream>

using namespace std;

// 扩展欧几里得算法
// 对于方程ax + by = gcd(a,b)
// 当a和b确定，那么gcd(a,b)也确定
// 扩展欧几里得算法可以给出a和b的最大公约数d、以及其中一个特解x、y
long long d, x, y, px, py;

void exgcd(long long a, long long b);
long long power(long long num, long long pow, long long mod);
long long fermat(long long num, long long mod);

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
        px = x;
        py = y;
        x = py;
        y = px - py * (a / b);
    }
}

// 费马小定理计算逆元
long long fermat(long long num, long long mod)
{
    return power(num, mod - 2, mod);
}

long long power(long long num, long long pow, long long mod)
{
    long ans = 1;
    while (pow > 0)
    {
        if ((pow & 1) == 1)
        {
            ans = (ans * num) % mod;
        }
        num = (num * num) % mod;
        pow >>= 1;
    }
    return ans;
}

int main()
{
    // 扩展欧几里得算法例子
    int a = 220;
    int b = 170;
    exgcd(a, b);
    cout << "gcd(" << a << ", " << b << ") = " << d << endl;
    cout << "x = " << x << ", y = " << y << endl;

    // 扩展欧几里得算法可以去求逆元
    cout << "求逆元测试开始" << endl;
    long long mod = 1000000007;
    long long test = 10000000;
    for (long long num = 1; num <= test; num++)
    {
        exgcd(num, mod);
        x = (x % mod + mod) % mod; // 保证x为正
        if (x != fermat(num, mod))
        {
            cout << "出错了!" << endl;
        }
    }
    cout << "求逆元测试结束" << endl;

    return 0;
}