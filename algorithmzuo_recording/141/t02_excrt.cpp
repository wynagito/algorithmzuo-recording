// 讲解扩展中国剩余定理之前，先介绍一个关于扩展欧几里得算法的小结论

// 如果ax + by = d，d为gcd(a,b)，其中一个特解是(x0, y0)
// 那么通解可以表示为： x = x0 + (b/d) * n       y = y0 - (a/d) * n       n为任意整数

// 如果ax + by = c，c为d的整数倍，根据上面的特解，可以得到该等式的一个特解(x0’, y0’)
// 其中，x0’ = x0 * (c / d)，y0’ = y0 * (c / d)
// 那么通解可以表示为： x = x0’ + (b/d) * n      y = y0’ - (a/d) * n      n为任意整数

// 以上都是，讲解140 - 扩展欧几里得和二元一次不定方程，讲的内容

// 其中通解x = x0’ + (b/d) * n，如何得到最小非负特解？利用如下公式

// 最小非负特解 = x0’ % (b / d)，取非负余数

// 扩展中国剩余定理
// 给出n个同余方程，求满足同余方程的最小正数解x，所有Mi之间可能并不互质
// x ≡ R1 (% M1)  x ≡ R2 (% M2)   x ≡ R3 (% M3) ..  x ≡ Rn (% Mn)

// 求解过程，课上重点图解
// 1，补充初始模数m0 = 1，lcm = 1，tail = 0，那么，ans = lcm * x + tail，这必然成立
// 2，当前来到模数mi，余数ri，新的方程，ans = mi * y + ri，两个方程相减得到新表达式
// 3，lcm * x + mi * y = ri - tail，记为 ax + by = c，扩展欧几里得算法求解
// 4，如果不存在解，过程结束，说明不存在这样的ans。如果存在解，得到最小非负特解x0
// 5，通解x = x0 + (b/d) * n，带入ans = lcm * x + tail
// 6，得到ans = lcm * (b/d) * n + (lcm * x0 + tail)
// 7，令 lcm * (b/d) 记为 lcm’, 令 (lcm * x0 + tail) % lcm’ 记为 tail’
// 8，表达式又是，ans = lcm’ * x + tail’，去往下一组方程，继续迭代ans
// 9，直到所有方程计算完毕，最终返回tail就是答案

// 扩展中国剩余定理模版
// 给出n个同余方程，求满足同余方程的最小正数解x
// 一共n个同余方程，x ≡ ri(% mi)
// 1 <= n <= 10^5
// 0 <= ri、mi <= 10^12
// 所有mi不一定互质
// 所有mi的最小公倍数 <= 10^18
// 测试链接 : https://www.luogu.com.cn/problem/P4777
// 测试链接 : https://www.luogu.com.cn/problem/P1495

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

const int MAXN = 100001;
long m[MAXN];
long r[MAXN];

// 扩展中国剩余定理模版
long gcd, x, y;

void exgcd(long a, long b)
{
    if (b == 0)
    {
        gcd = a;
        x = 1;
        y = 0;
    }
    else
    {
        exgcd(b, a % b);
        long px = x;
        long py = y;
        x = py;
        y = px - py * (a / b);
    }
}

// 讲解033 - 位运算实现乘法
long multiply(long a, long b, long mod)
{
    a = (a % mod + mod) % mod;
    b = (b % mod + mod) % mod;
    long ans = 0;
    while (b != 0)
    {
        if ((b & 1) != 0)
        {
            ans = (ans + a) % mod;
        }
        a = (a + a) % mod;
        b >>= 1;
    }
    return ans;
}

long excrt(int n)
{
    long tail = 0, lcm = 1, tmp, b, c, x0;

    for (int i = 1; i <= n; i++)
    {
        b = m[i];
        c = ((r[i] - tail) % b + b) % b;
        exgcd(lcm, b);
        if (c % gcd != 0)
        {
            return -1;
        }

        x0 = multiply(x, c / gcd, b / gcd);
        tmp = lcm * (b / gcd);
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
        cin >> m[i];
        cin >> r[i];
    }

    cout << excrt(n) << endl;
    return 0;
}