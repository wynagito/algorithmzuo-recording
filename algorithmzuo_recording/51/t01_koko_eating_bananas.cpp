// 二分答案法
// 1）估计 最终答案可能的范围 是什么，可以定的粗略，反正二分不了几次
// 2）分析 问题的答案 和 给定条件 之间的 单调性，大部分时候只需要用到 自然智慧
// 3）建立一个f函数，当答案固定的情况下，判断 给定的条件是否达标
// 4）在 最终答案可能的范围上不断二分搜索，每次用f函数判断，直到二分结束，找到最合适的答案
// 核心点：分析单调性、建立f函数

// 爱吃香蕉的珂珂
// 珂珂喜欢吃香蕉。这里有 n 堆香蕉，第 i 堆中有 piles[i] 根香蕉
// 警卫已经离开了，将在 h 小时后回来。
// 珂珂可以决定她吃香蕉的速度 k （单位：根/小时)
// 每个小时，她将会选择一堆香蕉，从中吃掉 k 根
// 如果这堆香蕉少于 k 根，她将吃掉这堆的所有香蕉，然后这一小时内不会再吃更多的香蕉
// 珂珂喜欢慢慢吃，但仍然想在警卫回来前吃掉所有的香蕉。
// 返回她可以在 h 小时内吃掉所有香蕉的最小速度 k（k 为整数）
// 测试链接 : https://leetcode.cn/problems/koko-eating-bananas/

class Solution
{
public:
    int minEatingSpeed(vector<int> &piles, int h)
    {
        // 最小且达标的速度，范围[l,r]
        int l = 1;
        int r = 0;
        for (int pile : piles)
        {
            r = max(r, pile);
        }
        // [l,r]不停二分
        int ans = 0;
        int m = 0;
        while (l <= r)
        {
            // m = (l + r) / 2
            m = l + ((r - l) >> 1);
            // 速度越大，时间越少
            if (f(piles, m) <= h)
            {
                // 达标！
                // 记录答案，去左侧二分
                ans = m;
                // l....m....r
                // l..m-1
                r = m - 1;
            }
            else
            {
                // 不达标
                l = m + 1;
            }
        }
        return ans;
    }

    // 香蕉重量都在piles
    // 速度就定成speed
    // 返回吃完所有的香蕉，耗费的小时数量
    long long f(vector<int> &piles, int speed)
    {
        long long ans = 0;
        for (int pile : piles)
        {
            // (a/b)结果向上取整，如果a和b都是非负数，可以写成(a+b-1)/b
            ans += (pile + speed - 1) / speed;
        }
        return ans;
    }
};