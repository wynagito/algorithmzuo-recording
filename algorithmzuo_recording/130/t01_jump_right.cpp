// 向右跳跃获得最大得分
// 给定长度为n+1的数组arr，下标编号0 ~ n，给定正数a、b
// 一开始在0位置，每次可以选择[a,b]之间的一个整数，作为向右跳跃的距离
// 每来到一个位置i，可以获得arr[i]作为得分，位置一旦大于n就停止
// 返回能获得的最大得分
// 1 <= n <= 2 * 10^5
// 1 <= a <= b <= n
// -1000 <= arr[i] <= +1000
// 测试链接 : https://www.luogu.com.cn/problem/P1725

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <queue>

using namespace std;

const int MAXN = 200001;
const int NA = INT_MIN;

int arr[MAXN];
int dp[MAXN];
int qu[MAXN]; // 单调队列
int l, r;
int n, a, b;

// 入队
void add(int j)
{
    if (j >= 0 && dp[j] != NA)
    {
        while (l < r && dp[qu[r - 1]] <= dp[j])
        {
            r--;
        }
        qu[r++] = j;
    }
}

// 出队
void overdue(int t)
{
    if (l < r && qu[l] == t)
    {
        l++;
    }
}

int compute()
{
    dp[0] = arr[0];
    l = r = 0;
    for (int i = 1; i <= n; i++)
    {
        add(i - a);
        overdue(i - b - 1);
        dp[i] = (l < r) ? dp[qu[l]] + arr[i] : NA;
    }
    int ans = NA;
    for (int i = n + 1 - b; i <= n; i++)
    {
        ans = max(ans, dp[i]);
    }
    return ans;
}

int main()
{
    cin >> n >> a >> b;
    for (int i = 0; i <= n; i++)
    {
        cin >> arr[i];
    }
    cout << compute() << endl;
    return 0;
}
