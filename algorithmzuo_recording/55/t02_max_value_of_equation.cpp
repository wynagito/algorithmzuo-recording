// 满足不等式的最大值
// 给你一个数组 points 和一个整数 k
// 数组中每个元素都表示二维平面上的点的坐标，并按照横坐标 x 的值从小到大排序
// 也就是说 points[i] = [xi, yi]
// 并且在 1 <= i < j <= points.length 的前提下，xi < xj 总成立
// 请你找出 yi + yj + |xi - xj| 的 最大值，
// 其中 |xi - xj| <= k 且 1 <= i < j <= points.length
// 题目测试数据保证至少存在一对能够满足 |xi - xj| <= k 的点。
// 测试链接 : https://leetcode.cn/problems/max-value-of-equation/

class Solution
{
public:
    int deque[100010][2]; // (x , y) : y - x 从大到小
    // 已知所有的点都是根据x值排序的！
    // 任何两个点，组成指标，要求 : 后x - 前x <= k
    // 返回最大指标
    int findMaxValueOfEquation(vector<vector<int>> &points, int k)
    {
        int h = 0, t = 0;
        int n = points.size();
        int ans = INT_MIN;
        // yi + yj + |xi - xj| == yj + xj + yi - xi
        for (int i = 0, x, y; i < n; i++)
        {
            // i号点是此时的点，当前的后面点，看之前哪个点的y-x值最大，x距离又不能超过k
            x = points[i][0];
            y = points[i][1];
            while (h < t && x - deque[h][0] > k)
            {
                // 单调队列头部的可能性过期了，头部点的x与当前点x的距离超过了k
                h++;
            }
            if (h < t)
            {
                ans = max(ans, x + y + deque[h][1] - deque[h][0]);
            }
            // i号点的x和y，该从尾部进入单调队列
            // 大 -> 小
            while (h < t && deque[t - 1][1] - deque[t - 1][0] <= y - x)
            {
                t--;
            }
            deque[t][0] = x;
            deque[t++][1] = y;
        }
        return ans;
    }
};