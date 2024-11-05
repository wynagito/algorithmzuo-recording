// 除了单调栈最经典的用法之外，在很多问题里单调栈还可以 维持求解答案的可能性
// 1）单调栈里的所有对象按照 规定好的单调性来组织
// 2）当某个对象进入单调栈时，
//    会从 栈顶开始 依次淘汰单调栈里 对后续求解答案没有帮助 的对象
// 3）每个对象从栈顶弹出的时 结算当前对象参与的答案，随后这个对象 不再参与后续求解答案的过程
// 4）其实是 先有对题目的分析！进而发现单调性，然后利用 单调栈的特征 去实现

// 最大宽度坡
// 给定一个整数数组 A，坡是元组 (i, j)，其中  i < j 且 A[i] <= A[j]
// 这样的坡的宽度为 j - i，找出 A 中的坡的最大宽度，如果不存在，返回 0
// 测试链接 : https://leetcode.cn/problems/maximum-width-ramp/

class Solution
{
public:
    int stack[50010];
    int maxWidthRamp(vector<int> &arr)
    {
        // 令r=1相当于0位置进栈了
        // stack[0] = 0，然后栈的大小变成1
        // 栈内从大到小
        int r = 1;
        int n = arr.size();
        for (int i = 1; i < n; i++)
        {
            if (arr[stack[r - 1]] > arr[i])
            { // 单调递减
                stack[r++] = i;
            }
        }
        int ans = 0;
        for (int j = n - 1; j >= 0; j--)
        {
            while (r > 0 && arr[stack[r - 1]] <= arr[j])
            {
                ans = max(ans, j - stack[--r]);
            }
        }
        return ans;
    }
};