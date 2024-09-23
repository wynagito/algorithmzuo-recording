// 不超过连续k个元素的最大累加和
// 给定一个长度为n的数组arr，你可以随意选择数字
// 要求选择的方案中，连续选择的个数不能超过k个
// 返回能得到的最大累加和
// 1 <= n、k <= 10^5
// 0 <= arr[i] <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/P2627

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

const int MAXN = 100001;

int arr[MAXN];
long long sum[MAXN];
long long dp[MAXN];
deque<int> queue;

int n, k;

// 不要i位置的数字产生的指标
long long value(int i)
{
    return (i == 0) ? 0 : (dp[i - 1] - sum[i]);
}

long long compute()
{
    for (int i = 1; i <= n; i++)
    {
        sum[i] = sum[i - 1] + arr[i];
    }

    queue.clear();
    queue.push_back(0);

    for (int i = 1; i <= n; i++)
    {
        while (!queue.empty() && (value(queue.back()) <= value(i)))
        {
            queue.pop_back();
        }
        queue.push_back(i);
        if (!queue.empty() && queue.front() == i - k - 1)
        {
            queue.pop_front();
        }
        dp[i] = value(queue.front()) + sum[i];
    }
    return dp[n];
}

int main()
{

    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }

    cout << compute() << endl;
    return 0;
}
