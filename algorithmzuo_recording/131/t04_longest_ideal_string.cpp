// 最长理想子序列
// 给定一个长度为n，只由小写字母组成的字符串s，给定一个非负整数k
// 字符串s可以生成很多子序列，下面给出理想子序列的定义
// 子序列中任意相邻的两个字符，在字母表中位次的差值绝对值<=k
// 返回最长理想子序列
// 1 <= n <= 10^5
// 0 <= k <= 25
// s只由小写字母组成
// 测试链接 : https://leetcode.cn/problems/longest-ideal-subsequence/

// 数据量太小，线段树的优势不明显
// 时间复杂度O(n * log e)，n为字符串长度，e为字符集大小
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution
{
public:
    static const int n = 26;
    vector<int> maxarr;

    int longestIdealString(string s, int k)
    {
        maxarr.resize((n + 1) << 2);
        fill(maxarr.begin(), maxarr.end(), 0);
        int v, p;
        int ans = 0;
        for (char cha : s)
        {
            v = cha - 'a' + 1;
            p = getMax(max(v - k, 1), min(v + k, n), 1, n, 1);
            ans = max(ans, p + 1);
            update(v, p + 1, 1, n, 1);
        }
        return ans;
    }

    void up(int i)
    {
        maxarr[i] = max(maxarr[i << 1], maxarr[i << 1 | 1]);
    }

    // 只有单点更新不需要定义down方法
    // 因为单点更新的任务一定会从线段树头节点直插到某个叶节点
    // 根本没有懒更新这回事
    void update(int jobi, int jobv, int l, int r, int i)
    {
        if (l == r && jobi == l)
        {
            maxarr[i] = jobv;
        }
        else
        {
            int m = (l + r) >> 1;
            if (jobi <= m)
            {
                update(jobi, jobv, l, m, i << 1);
            }
            else
            {
                update(jobi, jobv, m + 1, r, i << 1 | 1);
            }
            up(i);
        }
    }

    int getMax(int jobl, int jobr, int l, int r, int i)
    {
        if (jobl <= l && r <= jobr)
        {
            return maxarr[i];
        }
        int m = (l + r) >> 1;
        int ans = 0;
        if (jobl <= m)
        {
            ans = max(ans, getMax(jobl, jobr, l, m, i << 1));
        }
        if (jobr > m)
        {
            ans = max(ans, getMax(jobl, jobr, m + 1, r, i << 1 | 1));
        }
        return ans;
    }
};
