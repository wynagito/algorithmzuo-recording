// 一开始1~n范围上的数字都是0，一共有m个操作，每次操作为(l,r,s,e,d)
// 表示在l~r范围上依次加上首项为s、末项为e、公差为d的数列
// m个操作做完之后，统计1~n范围上所有数字的最大值和异或和
// 测试链接 : https://www.luogu.com.cn/problem/P4231

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 10000005;
long long arr[MAXN];
int n, m;

void set(int l, int r, int s, int e, int d)
{
    arr[l] += s;
    arr[l + 1] += d - s;
    arr[r + 1] -= d + e;
    arr[r + 2] += e;
}

void build()
{
    for (int i = 1; i <= n; i++)
    {
        arr[i] += arr[i - 1];
    }
    for (int i = 1; i <= n; i++)
    {
        arr[i] += arr[i - 1];
    }
}

int main()
{
    while (scanf("%d%d", &n, &m) == 2)
    {
        for (int i = 0; i < m; i++)
        {
            int l, r, s, e;
            scanf("%d%d%d%d", &l, &r, &s, &e);
            int d = (e - s) / (r - l);
            set(l, r, s, e, d);
        }
        build();

        long long max_val = 0, xor_val = 0;
        for (int i = 1; i <= n; i++)
        {
            max_val = max(max_val, arr[i]);
            xor_val ^= arr[i];
        }
        cout << xor_val << " " << max_val << "\n";
    }

    return 0;
}
