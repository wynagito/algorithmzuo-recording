// 计算等位时间
// 给定一个数组arr长度为n，表示n个服务员，每服务一个人的时间
// 给定一个正数m，表示有m个人等位，每一个客人都遵循有空位就上的原则，
// 如果你是刚来的人，请问你需要等多久？
// 假设m远远大于n，比如n <= 10^3, m <= 10^9，该怎么做是最优解？
// 谷歌的面试，这个题连考了2个月
// 找不到测试链接，所以用对数器验证

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits.h>

using namespace std;

// 完成旅途的最少时间(题目6的在线测试)
// 有同学找到了在线测试链接，和课上讲的题目6几乎是一个意思，但是有细微差别
// 实现的代码，除了一些变量需要改成long类型之外，仅有两处关键逻辑不同，都打上了注释
// 除此之外，和课上讲的题目6的实现，再无区别
// 可以仔细阅读如下测试链接里的题目，重点关注此题和题目6，在题意上的差别
// 测试链接 : https://leetcode.cn/problems/minimum-time-to-complete-trips/
class Solution
{
public:
    long long minimumTime(vector<int> &arr, int w)
    {
        int minval = INT_MAX;
        for (int x : arr)
        {
            minval = min(minval, x);
        }
        long long ans = 0;
        for (long long l = 0, r = (long long)minval * w, m; l <= r;)
        {
            m = l + ((r - l) >> 1);
            // 这里逻辑和课上讲的不同
            // 课上讲的题意，是需要等多少人才能获得服务，你是第w+1个
            // 在线测试的题意，是需要完成w趟旅行
            if (f(arr, m) >= w)
            {
                ans = m;
                r = m - 1;
            }
            else
            {
                l = m + 1;
            }
        }
        return ans;
    }

    long long f(vector<int> &arr, long long time)
    {
        long long ans = 0;
        for (int num : arr)
        {
            // 这里逻辑和课上讲的不同
            // 课上讲的题意，计算time时间内，(完成 + 开始)服务的人数，需要+1
            // 在线测试的题意，计算time时间内，能完成多少旅行，不需要+1
            ans += (time / num);
        }
        return ans;
    }
};

int f(vector<int> &arr, int time);

// 堆模拟
// 验证方法，不是重点
// 如果m很大，该方法会超时
// 时间复杂度O(m * log(n))，额外空间复杂度O(n)
int waitingTime1(vector<int> &arr, int m)
{
    // 一个一个对象vector<int>
    // [醒来时间，服务一个客人要多久]
    // 按照醒来时间排序
    // 堆顶元素，表示最早醒来的人
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> heap;
    int n = arr.size();
    for (int i = 0; i < n; i++)
    {
        heap.push({0, arr[i]});
    }
    for (int i = 0; i < m; i++)
    {
        vector<int> cur = heap.top();
        heap.pop();
        cur[0] += cur[1];
        heap.push(cur);
    }
    return heap.top()[0];
}

// 二分答案法
// 最优解
// 时间复杂度O(n * log(min_time * w))，额外空间复杂度O(1)
int waitingTime2(vector<int> &arr, int w)
{
    int min_time = INT_MAX;
    for (int x : arr)
    {
        min_time = min(min_time, x);
    }
    int ans = 0;
    for (int l = 0, r = min_time * w, m; l <= r;)
    {
        // m中点，表示一定要让服务员工作的时间！
        m = l + ((r - l) / 2);
        // 能够给几个客人提供服务
        if (f(arr, m) >= w + 1)
        {
            ans = m;
            r = m - 1;
        }
        else
        {
            l = m + 1;
        }
    }
    return ans;
}

// 如果每个服务员工作time，可以接待几位客人（结束的、开始的客人都算）
int f(vector<int> &arr, int time)
{
    int ans = 0;
    for (int num : arr)
    {
        ans += (time / num) + 1;
    }
    return ans;
}

// 对数器测试
int main()
{
    cout << "测试开始" << endl;
    int N = 50;
    int V = 30;
    int M = 3000;
    int testTime = 20000;
    for (int i = 0; i < testTime; i++)
    {
        int n = rand() % N + 1;
        vector<int> arr(n);
        for (int j = 0; j < n; j++)
        {
            arr[j] = rand() % V + 1;
        }
        int m = rand() % M;
        int ans1 = waitingTime1(arr, m);
        int ans2 = waitingTime2(arr, m);
        if (ans1 != ans2)
        {
            cout << "出错了!" << endl;
        }
    }
    cout << "测试结束" << endl;
    return 0;
}