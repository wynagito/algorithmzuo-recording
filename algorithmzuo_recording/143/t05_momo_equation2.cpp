// 墨墨的等式(两次转圈法)
// 一共有n种正数，每种数可以选择任意个，个数不能是负数
// 那么一定有某些数值可以由这些数字累加得到
// 请问在[l...r]范围上，有多少个数能被累加得到
// 0 <= n <= 12
// 0 <= 数值范围 <= 5 * 10^5
// 1 <= l <= r <= 10^12
// 测试链接 : https://www.luogu.com.cn/problem/P2371

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

const int MAXN = 500001;
const long long inf = numeric_limits<long long>::max();

int v[MAXN];
long long dist[MAXN];
int n, x;
long long l, r;

int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}

long long compute()
{
    sort(v + 1, v + n + 1);
    int size = 0;
    for (int i = 1; i <= n; i++)
    {
        if (v[i] != 0)
        {
            v[++size] = v[i];
        }
    }
    if (size == 0)
    {
        return 0;
    }

    x = v[1];
    fill(dist, dist + x, inf);
    dist[0] = 0;

    for (int i = 2, d; i <= size; i++)
    {                     // 遇到基准数之外的其他数，更新最短路
        d = gcd(v[i], x); // 求最大公约数
        for (int j = 0; j < d; j++)
        { // j是每个子环的起点
            for (int cur = j, next, circle = 0; circle < 2; circle += cur == j ? 1 : 0)
            {
                next = (cur + v[i]) % x;
                if (dist[cur] != inf)
                {
                    dist[next] = min(dist[next], dist[cur] + v[i]);
                }
                cur = next;
            }
        }
    }

    long long ans = 0;
    for (int i = 0; i < x; i++)
    {
        if (r >= dist[i])
        {
            ans += max(0LL, (r - dist[i]) / x + 1);
        }
        if (l >= dist[i])
        {
            ans -= max(0LL, (l - dist[i]) / x + 1);
        }
    }
    return ans;
}

int main()
{

    cin >> n;
    cin >> l;
    l--; // 根据原代码 l = (long)in.nval - 1
    cin >> r;

    for (int i = 1; i <= n; i++)
    {
        cin >> v[i];
    }

    cout << compute() << '\n';
    return 0;
}