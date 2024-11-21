// 墨墨的等式(不排序+两次转圈法)
// 不排序也一样能通过，本文件实现没有任何新内容，只是去掉了排序逻辑
// 一共有n种正数，每种数可以选择任意个，个数不能是负数
// 那么一定有某些数值可以由这些数字累加得到
// 请问在[l...r]范围上，有多少个数能被累加得到
// 0 <= n <= 12
// 0 <= 数值范围 <= 5 * 10^5
// 1 <= l <= r <= 10^12
// 测试链接 : https://www.luogu.com.cn/problem/P2371

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500001;
const long long inf = LLONG_MAX;

int v[MAXN];
long long dist[MAXN];
int n, size, x;
long long l, r;

// 欧几里得算法求最大公约数
int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}

long long compute()
{
    x = v[1];
    fill(dist, dist + x, inf);
    dist[0] = 0;
    for (int i = 2, d; i <= size; i++)
    {
        d = gcd(v[i], x);
        for (int j = 0; j < d; j++)
        {
            for (int cur = j, next, circle = 0; circle < 2; circle += (cur == j ? 1 : 0))
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
    size = 0;
    cin >> l >> r;
    l--; // 因为 l 在输入中是包含的，所以要减 1
    for (int i = 1, num; i <= n; i++)
    {
        cin >> num;
        if (num != 0)
        {
            v[++size] = num;
        }
    }
    cout << compute() << "\n";

    return 0;
}