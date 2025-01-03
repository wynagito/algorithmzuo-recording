// 可以翻转1次的情况下子数组最大累加和
// 给定一个数组nums，
// 现在允许你随意选择数组连续一段进行翻转，也就是子数组逆序的调整
// 比如翻转[1,2,3,4,5,6]的[2~4]范围，得到的是[1,2,5,4,3,6]
// 返回必须随意翻转1次之后，子数组的最大累加和
// 对数器验证

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <ctime>
using namespace std;

// 暴力方法
// 为了验证
int maxSum(const vector<int> &nums);

int maxSumReverse1(vector<int> &nums)
{
    int ans = INT_MIN;
    int n = nums.size();
    for (int l = 0; l < n; l++)
    {
        for (int r = l; r < n; r++)
        {
            reverse(nums.begin() + l, nums.begin() + r + 1);
            ans = max(ans, maxSum(nums));
            reverse(nums.begin() + l, nums.begin() + r + 1);
        }
    }
    return ans;
}

// nums[l...r]范围上的数字进行逆序调整
void reverseRange(vector<int> &nums, int l, int r)
{
    while (l < r)
    {
        swap(nums[l++], nums[r--]);
    }
}

// 返回子数组最大累加和
int maxSum(const vector<int> &nums)
{
    int n = nums.size();
    int ans = nums[0];
    int pre = nums[0];
    for (int i = 1; i < n; i++)
    {
        pre = max(nums[i], pre + nums[i]);
        ans = max(ans, pre);
    }
    return ans;
}

// 正式方法
// 时间复杂度O(n)
int maxSumReverse2(vector<int> &nums)
{
    // 反转区间和最大累加和区间不可能是包含关系，也不可能没有交集
    // 所以只有部分交集的情况
    int n = nums.size();
    // start[i] : 所有必须以i开头的子数组中，最大累加和是多少
    vector<int> start(n);
    start[n - 1] = nums[n - 1];
    for (int i = n - 2; i >= 0; i--)
    {
        // nums[i]
        // nums[i] + start[i+1]
        start[i] = max(nums[i], nums[i] + start[i + 1]);
    }
    int ans = start[0];
    // end : 子数组必须以i-1结尾，其中的最大累加和
    int end = nums[0];
    // maxEnd :
    // 0~i-1范围上，
    // 子数组必须以0结尾，其中的最大累加和
    // 子数组必须以1结尾，其中的最大累加和
    // ...
    // 子数组必须以i-1结尾，其中的最大累加和
    // 所有情况中，最大的那个累加和就是maxEnd
    int maxEnd = nums[0];
    for (int i = 1; i < n; i++)
    {
        // 枚举划分点 i...
        // 0 ... j ... maxEnd ... i ... n-1
        // j...maxEnd 的累加和最大
        // 那么反转 j ... i-1 范围上的数字
        // 0 ... i-1 ... maxEnd ... j i ... n-1
        // 反转后最大累加和是 = start[i] + maxEnd
        ans = max(ans, maxEnd + start[i]);
        // 子数组必须以i结尾，其中的最大累加和
        end = max(nums[i], end + nums[i]);
        maxEnd = max(maxEnd, end);
    }
    // 不用反转的情况
    ans = max(ans, maxEnd);
    return ans;
}

// 生成随机数组
vector<int> randomArray(int n, int v)
{
    vector<int> ans(n);
    for (int i = 0; i < n; i++)
    {
        ans[i] = rand() % (2 * v + 1) - v;
    }
    return ans;
}

// 主函数
int main()
{
    srand(time(0));
    int n = 50;
    int v = 200;
    int testTime = 20000;
    cout << "测试开始" << endl;
    for (int i = 0; i < testTime; i++)
    {
        int len = rand() % n + 1;
        vector<int> arr = randomArray(len, v);
        int ans1 = maxSumReverse1(arr);
        int ans2 = maxSumReverse2(arr);
        if (ans1 != ans2)
        {
            cout << "出错了!" << endl;
        }
    }
    cout << "测试结束" << endl;
    return 0;
}
