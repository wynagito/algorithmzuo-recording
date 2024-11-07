// 单调队列最经典的用法是解决如下问题：
// 滑动窗口在滑动时，r++代表右侧数字进窗口，l++代表左侧数字出窗口
// 这个过程中，想随时得到当前滑动窗口的 最大值 或者 最小值
// 窗口滑动的过程中，单调队列所有调整的总代价为O(n)，单次操作的均摊代价为O(1)

// 滑动窗口最大值（单调队列经典用法模版）
// 给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧
// 你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。
// 返回 滑动窗口中的最大值 。
// 测试链接 : https://leetcode.cn/problems/sliding-window-maximum/

class Solution
{
public:
    static const int MAXN = 100001;
    int deque[MAXN]; // 单调队列
    int h, t;        // 队列头尾指针
    vector<int> maxSlidingWindow(vector<int> &arr, int k)
    {
        h = t = 0;
        int n = arr.size();
        // 先形成长度为k-1的窗口
        for (int i = 0; i < k - 1; i++)
        {
            // 大 -> 小
            while (h < t && arr[deque[t - 1]] <= arr[i])
            {
                t--;
            }
            deque[t++] = i;
        }
        int m = n - k + 1;
        vector<int> ans(m);
        // 当前窗口k-1长度
        for (int l = 0, r = k - 1; l < m; l++, r++)
        {
            // 少一个，要让r位置的数进来
            while (h < t && arr[deque[t - 1]] <= arr[r])
            {
                t--;
            }
            deque[t++] = r;
            // 收集答案
            ans[l] = arr[deque[h]];
            // l位置的数出去
            if (deque[h] == l)
            {
                h++;
            }
        }
        return ans;
    }
};