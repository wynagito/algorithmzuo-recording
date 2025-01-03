// 删掉1个数字后长度为k的子数组最大累加和
// 给定一个数组nums，求必须删除一个数字后的新数组中
// 长度为k的子数组最大累加和，删除哪个数字随意
// 对数器验证

#include <iostream>
#include <vector>
#include <deque>
#include <climits>
#include <cstdlib>
#include <ctime>
using namespace std;

// 删除数组中指定索引的元素，返回新数组
vector<int> deleteIndex(const vector<int> &nums, int index)
{
    vector<int> result;
    for (int i = 0; i < nums.size(); i++)
    {
        if (i != index)
        {
            result.push_back(nums[i]);
        }
    }
    return result;
}

// 枚举每一个长度为k的子数组，找到最大累加和
int lenKmaxSum(const vector<int> &nums, int k)
{
    int n = nums.size();
    int ans = INT_MIN;
    for (int i = 0; i <= n - k; i++)
    {
        int cur = 0;
        for (int j = i, cnt = 0; cnt < k; j++, cnt++)
        {
            cur += nums[j];
        }
        ans = max(ans, cur);
    }
    return ans;
}

// 暴力方法
// 删除一个元素后，求长度为k的子数组最大累加和
int maxSum1(vector<int> &nums, int k)
{
    int n = nums.size();
    if (n <= k)
    {
        return 0;
    }
    int ans = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        vector<int> rest = deleteIndex(nums, i);
        ans = max(ans, lenKmaxSum(rest, k));
    }
    return ans;
}

// 正式方法，时间复杂度O(N)
int maxSum2(vector<int> &nums, int k)
{
    int n = nums.size();
    if (n <= k)
    {
        return 0;
    }
    deque<int> window; // 单调队列，维护窗口内的最小值索引
    long long sum = 0; // 当前窗口的累加和
    int ans = INT_MIN;

    for (int i = 0; i < n; i++)
    {
        // 单调队列：移除比当前值大的元素，维持递增顺序
        while (!window.empty() && nums[window.back()] >= nums[i])
        {
            window.pop_back();
        }
        window.push_back(i);
        sum += nums[i];

        if (i >= k)
        {
            // 更新答案，窗口内的最小值为nums[window.front()]
            ans = max(ans, static_cast<int>(sum - nums[window.front()]));
            if (window.front() == i - k)
            {
                window.pop_front(); // 移除过期的元素
            }
            sum -= nums[i - k]; // 移除窗口左边界的值
        }
    }
    return ans;
}

// 生成长度为n，值在[-v, +v]之间的随机数组
vector<int> randomArray(int n, int v)
{
    vector<int> result(n);
    for (int i = 0; i < n; i++)
    {
        result[i] = rand() % (2 * v + 1) - v;
    }
    return result;
}

// 主函数，测试代码
int main()
{
    srand(time(0));
    int n = 200;
    int v = 1000;
    int testTimes = 10000;
    cout << "测试开始" << endl;
    for (int i = 0; i < testTimes; i++)
    {
        int len = rand() % n + 1;
        vector<int> nums = randomArray(len, v);
        int k = rand() % len + 1;
        int ans1 = maxSum1(nums, k);
        int ans2 = maxSum2(nums, k);
        if (ans1 != ans2)
        {
            cout << "出错了!" << endl;
        }
    }
    cout << "测试结束" << endl;
    return 0;
}
