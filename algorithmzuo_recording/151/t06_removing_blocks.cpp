// 砖块消除
// 给定一个长度为n的数组arr，arr[i]为i号砖块的重量
// 选择一个没有消除的砖块进行消除，收益为被消除砖块联通区域的重量之和，比如arr = {3,5,2,1}
// 如果先消除5，那么获得3+5+2+1的收益，arr = {3,X,2,1}
// 如果再消除1，那么获得2+1的收益，arr = {3,X,2,X}
// 如果再消除2，那么获得2的收益，arr = {3,X,X,X}
// 如果再消除3，那么获得3的收益，arr = {X,X,X,X}
// 一共有n!种消除方案，返回所有消除方案的收益总和，答案对 1000000007 取模
// 1 <= n <= 10^5    1 <= arr[i] <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/AT_agc028_b
// 测试链接 : https://atcoder.jp/contests/agc028/tasks/agc028_b

#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1000000007;
const int MAXN = 100001;

int arr[MAXN];
int inv[MAXN];
int sum[MAXN];
int n;

void build()
{
    inv[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        inv[i] = MOD - (long long)inv[MOD % i] * (MOD / i) % MOD;
    }
    for (int i = 1; i <= n; i++)
    {
        sum[i] = (sum[i - 1] + inv[i]) % MOD;
    }
}

long long compute()
{
    build();
    long long ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans = (ans + (long long)(sum[i] + sum[n - i + 1] - 1) * arr[i]) % MOD;
    }
    for (int i = 1; i <= n; ++i)
    {
        ans = ans * i % MOD;
    }
    return (ans + MOD) % MOD; // 防止负数
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
