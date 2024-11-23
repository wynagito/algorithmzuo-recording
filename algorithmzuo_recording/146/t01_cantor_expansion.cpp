// 康托展开
// 数字从1到n，可以有很多排列，给出具体的一个排列，求该排列的名次，答案对 998244353 取模
// 1 <= n <= 10^6
// 测试链接 : https://www.luogu.com.cn/problem/P5367

#include <iostream>

using namespace std;

const int MAXN = 1000001, MOD = 998244353;

// fac : 阶乘数组
// tree : 树状数组
int arr[MAXN], fac[MAXN], tree[MAXN];

int n;

int lowbit(int i)
{
    return i & -i;
}

int sum(int i)
{
    int ans = 0;
    while (i > 0)
    {
        ans = (ans + tree[i]) % MOD;
        i -= lowbit(i);
    }
    return ans;
}

void add(int i, int v)
{
    while (i <= n)
    {
        tree[i] += v;
        i += lowbit(i);
    }
}

long long compute()
{
    fac[0] = 1;
    for (int i = 1; i < n; i++)
    {
        fac[i] = (int)((long long)fac[i - 1] * i % MOD);
    }
    for (int i = 1; i <= n; i++)
    {
        add(i, 1);
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans = (ans + (long long)sum(arr[i] - 1) * fac[n - i] % MOD) % MOD;
        add(arr[i], -1);
    }
    // 求的排名从0开始，但是题目要求从1开始，所以最后+1再返回
    ans = (ans + 1) % MOD;
    return ans;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    cout << compute() << endl;
    return 0;
}