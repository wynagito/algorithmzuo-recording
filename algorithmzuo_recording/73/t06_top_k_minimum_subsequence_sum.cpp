// 非负数组前k个最小的子序列累加和
// 给定一个数组nums，含有n个数字，都是非负数
// 给定一个正数k，返回所有子序列中累加和最小的前k个累加和
// 子序列是包含空集的
// 1 <= n <= 10^5
// 1 <= nums[i] <= 10^6
// 1 <= k <= 10^5
// 注意这个数据量，用01背包的解法是不行的，时间复杂度太高了
// 对数器验证

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstdlib>
#include <ctime>
using namespace std;

// 暴力方法：枚举所有子序列的和
void f1(vector<int> &nums, int index, int sum, vector<int> &allSubsequences)
{
    if (index == nums.size())
    {
        allSubsequences.push_back(sum);
    }
    else
    {
        f1(nums, index + 1, sum, allSubsequences);               // 不选当前数
        f1(nums, index + 1, sum + nums[index], allSubsequences); // 选当前数
    }
}

vector<int> topKSum1(vector<int> &nums, int k)
{
    vector<int> allSubsequences;
    f1(nums, 0, 0, allSubsequences);
    sort(allSubsequences.begin(), allSubsequences.end()); // 排序
    vector<int> ans(k);
    for (int i = 0; i < k; ++i)
    {
        ans[i] = allSubsequences[i];
    }
    return ans;
}

// 01 背包方法：动态规划计算所有可能的子序列和
vector<int> topKSum2(vector<int> &nums, int k)
{
    int sum = 0;
    for (int num : nums)
        sum += num;
    vector<int> dp(sum + 1, 0);
    dp[0] = 1;
    for (int num : nums)
    {
        for (int j = sum; j >= num; --j)
        {
            dp[j] += dp[j - num];
        }
    }
    vector<int> ans;
    for (int j = 0; j <= sum && ans.size() < k; ++j)
    {
        for (int i = 0; i < dp[j] && ans.size() < k; ++i)
        {
            ans.push_back(j);
        }
    }
    return ans;
}

// 堆优化方法：使用小根堆
vector<int> topKSum3(vector<int> &nums, int k)
{
    sort(nums.begin(), nums.end());
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
    heap.push({nums[0], 0});
    vector<int> ans(k);
    for (int i = 1; i < k; ++i)
    {
        auto cur = heap.top();
        heap.pop();
        int sum = cur.first;
        int index = cur.second;
        ans[i] = sum;
        if (index + 1 < nums.size())
        {
            heap.push({sum - nums[index] + nums[index + 1], index + 1});
            heap.push({sum + nums[index + 1], index + 1});
        }
    }
    return ans;
}

// 测试工具：随机数组生成
vector<int> randomArray(int len, int value)
{
    vector<int> ans(len);
    for (int i = 0; i < len; ++i)
    {
        ans[i] = rand() % value;
    }
    return ans;
}

// 测试工具：数组比较
bool equals(vector<int> &ans1, vector<int> &ans2)
{
    if (ans1.size() != ans2.size())
        return false;
    for (int i = 0; i < ans1.size(); ++i)
    {
        if (ans1[i] != ans2[i])
        {
            return false;
        }
    }
    return true;
}

// 主函数：测试验证
int main()
{
    srand(time(nullptr));
    int n = 15;
    int v = 40;
    int testTime = 5000;
    cout << "测试开始" << endl;
    for (int i = 0; i < testTime; ++i)
    {
        int len = rand() % n + 1;
        vector<int> nums = randomArray(len, v);
        int k = rand() % ((1 << len) - 1) + 1;
        vector<int> ans1 = topKSum1(nums, k);
        vector<int> ans2 = topKSum2(nums, k);
        vector<int> ans3 = topKSum3(nums, k);
        if (!equals(ans1, ans2) || !equals(ans2, ans3))
        {
            cout << "出错了！" << endl;
            return -1;
        }
    }
    cout << "测试结束" << endl;
    return 0;
}
