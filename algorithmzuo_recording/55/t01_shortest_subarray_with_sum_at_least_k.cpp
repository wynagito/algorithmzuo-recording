// 除了单调队列最经典的用法之外，在很多问题里单调队列还可以 维持求解答案的可能性
// 1）单调队列里的所有对象按照 规定好的单调性来组织
// 2）当某个对象从队尾进入单调队列时，
//    会从 队头 或者 队尾 依次淘汰单调队列里，对后续求解答案没有帮助 的对象
// 3）每个对象一旦从单调队列弹出，可以结算此时这个对象参与的答案，
//    随后这个对象 不再参与后续求解答案的过程
// 4）其实是 先有对题目的分析！进而发现单调性，然后利用 单调队列的特征 去实现

// 和至少为K的最短子数组
// 给定一个数组arr，其中的值有可能正、负、0
// 给定一个正数k
// 返回累加和>=k的所有子数组中，最短的子数组长度
// 测试链接 : https://leetcode.cn/problems/shortest-subarray-with-sum-at-least-k/

class Solution
{
public:
    // sum[0] : 前0个数的前缀和
    // sum[i] : 前i个数的前缀和
    long long sum[100010];
    int deque[100010];
    int h, t;
    int shortestSubarray(vector<int> &arr, int k)
    {
        int n = arr.size();
        for (int i = 0; i < n; i++)
        {
            // [3,4,5]
            //  0 1 2
            // sum[0] = 0
            // sum[1] = 3
            // sum[2] = 7
            // sum[3] = 12
            sum[i + 1] = sum[i] + arr[i];
        }
        h = t = 0;
        int ans = INT_MAX;
        for (int i = 0; i <= n; i++)
        {
            // 前0个数前缀和
            // 前1个数前缀和
            // 前2个数前缀和
            // ...
            // 前n个数前缀和
            while (h != t && sum[i] - sum[deque[h]] >= k)
            {
                // 如果当前的前缀和 - 头前缀和，达标！
                ans = min(ans, i - deque[h++]);
            }
            // 前i个数前缀和，从尾部加入
            // 严格 小 大
            while (h != t && sum[deque[t - 1]] >= sum[i])
            {
                t--;
            }
            deque[t++] = i;
        }
        return ans != INT_MAX ? ans : -1;
    }
};