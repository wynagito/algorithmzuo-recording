// 逆康托展开
// 数字从1到n，可以有很多排列，给定一个长度为n的数组s，表示具体的一个排列
// 求出这个排列的排名假设为x，打印第x+m名的排列是什么
// 1 <= n <= 10^5
// 1 <= m <= 10^15
// 题目保证s是一个由1~n数字组成的正确排列，题目保证x+m不会超过排列的总数
// 测试链接 : https://www.luogu.com.cn/problem/U72177

#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN = 100001;

long long arr[MAXN];
// 线段树
int sum[MAXN << 2];
int n;
long long m;

// 初始化线段树，单点范围的初始累加和为1，认为所有数字都可用
void build(int l, int r, int i)
{
    if (l == r)
    {
        sum[i] = 1;
    }
    else
    {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
    }
}

// 单点jobi上，增加jobv，因为是单点更新，所以不需要建立懒更新机制
void add(int jobi, int jobv, int l, int r, int i)
{
    if (l == r)
    {
        sum[i] += jobv;
    }
    else
    {
        int mid = (l + r) >> 1;
        if (jobi <= mid)
        {
            add(jobi, jobv, l, mid, i << 1);
        }
        else
        {
            add(jobi, jobv, mid + 1, r, i << 1 | 1);
        }
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
    }
}

// 查询jobl~jobr范围的累加和
int sumfuc(int jobl, int jobr, int l, int r, int i)
{
    if (jobl <= l && r <= jobr)
    {
        return sum[i];
    }
    int mid = (l + r) >> 1;
    int ans = 0;
    if (jobl <= mid)
    {
        ans += sumfuc(jobl, jobr, l, mid, i << 1);
    }
    if (jobr > mid)
    {
        ans += sumfuc(jobl, jobr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}

// 线段树上找到第k名的是什么，找到后删掉词频，返回的过程修改累加和
int getAndDelete(int k, int l, int r, int i)
{
    int ans;
    if (l == r)
    {
        sum[i]--;
        ans = l;
    }
    else
    {
        int mid = (l + r) >> 1;
        if (sum[i << 1] >= k)
        {
            ans = getAndDelete(k, l, mid, i << 1);
        }
        else
        {
            ans = getAndDelete(k - sum[i << 1], mid + 1, r, i << 1 | 1);
        }
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
    }
    return ans;
}

void compute()
{
    // 当前排列转化为阶乘进制的排名
    build(1, n, 1);
    for (int i = 1, x; i <= n; i++)
    {
        x = (int)arr[i];
        if (x == 1)
        {
            arr[i] = 0;
        }
        else
        {
            arr[i] = sumfuc(1, x - 1, 1, n, 1);
        }
        add(x, -1, 1, n, 1);
    }
    // 当前排名加上m之后，得到新的排名，用阶乘进制表示
    arr[n] += m; // 最低位获得增加的幅度
    for (int i = n; i >= 1; i--)
    {
        // 往上进位多少
        arr[i - 1] += arr[i] / (n - i + 1);
        // 当前位是多少
        arr[i] %= n - i + 1;
    }
    // 根据阶乘进制转化为具体的排列
    build(1, n, 1);
    for (int i = 1; i <= n; i++)
    {
        arr[i] = getAndDelete((int)arr[i] + 1, 1, n, 1);
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", arr + i);
    }
    compute();
    for (int i = 1; i <= n; i++)
    {
        printf("%lld ", arr[i]);
    }
    return 0;
}