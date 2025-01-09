// 有一次修改机会的最长不下降子序列
// 给定一个长度为n的数组arr，和一个整数k
// 只有一次机会可以将其中连续的k个数全修改成任意一个值
// 这次机会你可以用也可以不用，请返回最长不下降子序列长度
// 1 <= k, n <= 10^5
// 1 <= arr[i] <= 10^6
// 测试链接 : https://www.luogu.com.cn/problem/P8776

#include <iostream>

const int MAXN = 100001;

int n, k, arr[MAXN], ends[MAXN], right[MAXN];

int compute();
void rightfunc();
int bs1(int len, int num);
int bs2(int len, int num);

int compute()
{
    rightfunc();
    int len = 0;
    int ans = 0;
    for (int i = 0, j = k, find, left; j < n; i++, j++)
    {
        find = bs2(len, arr[j]);
        left = find == -1 ? len : find;
        // 以i结尾的最长不下降子序列长度 + i到j范围内随意刷k个数 + j开头的最长不下降子序列长度
        ans = std::max(ans, left + k + right[j]);
        find = bs2(len, arr[i]);
        if (find == -1)
        {
            ends[len++] = arr[i];
        }
        else
        {
            ends[find] = arr[i];
        }
    }
    ans = std::max(ans, len + k);
    return ans;
}

// 生成辅助数组right
// right[j] :
// 一定以arr[j]做开头的情况下，arr[j...]上最长不下降子序列长度是多少
// 关键逻辑 :
// 一定以arr[i]做开头的情况下，arr[i...]上最长不下降子序列
// 就是！从n-1出发来看(从右往左遍历)，以arr[i]做结尾的情况下的最长不上升子序列
void rightfunc()
{
    int len = 0;
    for (int i = n - 1, find; i >= 0; i--)
    {
        find = bs1(len, arr[i]);
        if (find == -1)
        {
            ends[len++] = arr[i];
            right[i] = len;
        }
        else
        {
            ends[find] = arr[i];
            right[i] = find + 1;
        }
    }
}

// 求最长不上升子序列长度的二分
// ends[0...len-1]是降序的，找到<num的最左位置
// 不存在返回-1
int bs1(int len, int num)
{
    int l = 0, r = len - 1, m, ans = -1;
    while (l <= r)
    {
        m = (l + r) / 2;
        if (ends[m] < num)
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

// 求最长不下降子序列长度的二分
// ends[0...len-1]是升序的，找到>num的最左位置
// 不存在返回-1
int bs2(int len, int num)
{
    int l = 0, r = len - 1, m, ans = -1;
    while (l <= r)
    {
        m = (l + r) / 2;
        if (ends[m] > num)
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

int main()
{
    std::cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }
    std::cout << compute() << std::endl;
    return 0;
}