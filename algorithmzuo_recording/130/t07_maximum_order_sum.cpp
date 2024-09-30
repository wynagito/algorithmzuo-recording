// 子数组最大变序和
// 给定一个长度为n的数组arr，变序和定义如下
// 数组中每个值都可以减小或者不变，必须把整体变成严格升序的
// 所有方案中，能得到的最大累加和，叫做数组的变序和
// 比如[1,100,7]，变序和14，方案为变成[1,6,7]
// 比如[5,4,9]，变序和16，方案为变成[3,4,9]
// 比如[1,4,2]，变序和3，方案为变成[0,1,2]
// 返回arr所有子数组的变序和中，最大的那个
// 1 <= n、arr[i] <= 10^6
// 来自真实大厂笔试，对数器验证

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

long long maxSum1(const vector<int> &arr);
long long f1(const vector<int> &arr, int i, int p, vector<vector<long long>> &dp);
long long maxSum2(const vector<int> &arr);
long long sum(int max, int n);
vector<int> randomArray(int n, int v);

// 最大变序和的暴力方法
long long maxSum1(const vector<int> &arr)
{
    int n = arr.size();
    int maxVal = *max_element(arr.begin(), arr.end());
    long long ans = 0;
    vector<vector<long long>> dp(n, vector<long long>(maxVal + 1, -1));

    for (int i = 0; i < n; i++)
    {
        ans = max(ans, f1(arr, i, arr[i], dp));
    }
    return ans;
}

// 暴力方法中的辅助函数
long long f1(const vector<int> &arr, int i, int p, vector<vector<long long>> &dp)
{
    if (p <= 0 || i == -1)
    {
        return 0;
    }
    if (dp[i][p] != -1)
    {
        return dp[i][p];
    }
    int cur = min(arr[i], p);
    long long next = f1(arr, i - 1, cur - 1, dp);
    dp[i][p] = cur + next;
    return dp[i][p];
}

// 正式方法，时间复杂度O(n)
long long maxSum2(const vector<int> &arr)
{
    int n = arr.size();
    vector<int> stack(n);
    int size = 0;
    vector<long long> dp(n, 0);
    long long ans = 0;

    for (int i = 0; i < n; i++)
    {
        int curIdx = i;
        int curVal = arr[curIdx];
        while (curVal > 0 && size > 0)
        {
            int topIdx = stack[size - 1];
            int topVal = arr[topIdx];
            if (topVal >= curVal)
            {
                size--;
            }
            else
            {
                int idxDiff = curIdx - topIdx;
                int valDiff = curVal - topVal;
                if (valDiff >= idxDiff)
                {
                    dp[i] += sum(curVal, idxDiff) + dp[topIdx];
                    curVal = 0;
                    curIdx = 0;
                    break;
                }
                else
                {
                    dp[i] += sum(curVal, idxDiff);
                    curVal -= idxDiff;
                    curIdx = topIdx;
                    size--;
                }
            }
        }
        if (curVal > 0)
        {
            dp[i] += sum(curVal, curIdx + 1);
        }
        stack[size++] = i;
        ans = max(ans, dp[i]);
    }
    return ans;
}

// 计算从max开始的累加和
long long sum(int max, int n)
{
    n = min(max, n);
    return (((long long)max * 2 - n + 1) * n) / 2;
}

// 随机生成数组用于验证
vector<int> randomArray(int n, int v)
{
    vector<int> ans(n);
    for (int i = 0; i < n; i++)
    {
        ans[i] = rand() % v;
    }
    return ans;
}

int main()
{
    srand(time(0)); // 设置随机种子
    int n = 100;
    int v = 100;
    int testTimes = 50000;
    cout << "功能测试开始" << endl;
    for (int i = 0; i < testTimes; i++)
    {
        int size = rand() % n + 1;
        vector<int> arr = randomArray(size, v);
        long long ans1 = maxSum1(arr);
        long long ans2 = maxSum2(arr);
        if (ans1 != ans2)
        {
            cout << "出错了!" << endl;
        }
    }
    cout << "功能测试结束" << endl;

    cout << "性能测试开始" << endl;
    n = 1000000;
    v = 1000000;
    cout << "数组长度 : " << n << endl;
    cout << "数值范围 : " << v << endl;
    vector<int> arr = randomArray(n, v);
    clock_t start = clock();
    maxSum2(arr);
    clock_t end = clock();
    cout << "运行时间 : " << (double)(end - start) / CLOCKS_PER_SEC * 1000 << " 毫秒" << endl;
    cout << "性能测试结束" << endl;

    return 0;
}
