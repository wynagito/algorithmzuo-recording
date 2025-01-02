// 子序列累加和必须被7整除的最大累加和
// 给定一个非负数组nums，
// 可以任意选择数字组成子序列，但是子序列的累加和必须被7整除
// 返回最大累加和
// 对数器验证

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

// 暴力方法
// 为了验证
int f(vector<int> &nums, int i, int s);

int maxSum1(vector<int> &nums)
{
    // nums形成的所有子序列的累加和都求出来
    // 其中%7==0的那些累加和中，返回最大的
    // 就是如下f函数的功能
    return f(nums, 0, 0);
}

int f(vector<int> &nums, int i, int s)
{
    if (i == nums.size())
    {
        return s % 7 == 0 ? s : 0;
    }
    return max(f(nums, i + 1, s), f(nums, i + 1, s + nums[i]));
}

// 正式方法
// 时间复杂度O(n)
int maxSum2(vector<int> &nums)
{
    int n = nums.size();
    // dp[i][j] : nums[0...i-1]
    // nums前i个数形成的子序列一定要做到，子序列累加和%7 == j
    // 这样的子序列最大累加和是多少
    // 注意 : dp[i][j] == -1代表不存在这样的子序列
    vector<vector<int>> dp(n + 1, vector<int>(7, -1));
    dp[0][0] = 0;

    for (int j = 1; j < 7; j++)
    {
        dp[0][j] = -1;
    }

    for (int i = 1; i <= n; i++)
    {
        int x = nums[i - 1];
        int cur = nums[i - 1] % 7;
        for (int j = 0; j < 7; j++)
        {
            dp[i][j] = dp[i - 1][j];
            // 这里求need是核心
            int need = cur <= j ? (j - cur) : (j - cur + 7);
            // 或者如下这种写法也对
            // int need = (7 + j - cur) % 7;
            if (dp[i - 1][need] != -1)
            {
                dp[i][j] = max(dp[i][j], dp[i - 1][need] + x);
            }
        }
    }
    return dp[n][0];
}

// 为了测试
// 生成随机数组
vector<int> randomArray(int n, int v)
{
    vector<int> ans(n);
    for (int i = 0; i < n; i++)
    {
        ans[i] = rand() % v;
    }
    return ans;
}

// 为了测试
// 对数器
int main()
{
    int n = 15;
    int v = 30;
    int testTime = 20000;
    cout << "测试开始" << endl;
    for (int i = 0; i < testTime; i++)
    {
        int len = rand() % n + 1;
        vector<int> nums = randomArray(len, v);
        int ans1 = maxSum1(nums);
        int ans2 = maxSum2(nums);
        if (ans1 != ans2)
        {
            cout << "出错了!" << endl;
        }
    }
    cout << "测试结束" << endl;
    return 0;
}
