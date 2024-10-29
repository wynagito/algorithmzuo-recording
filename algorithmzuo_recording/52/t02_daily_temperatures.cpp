// 每日温度
// 给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer
// 其中 answer[i] 是指对于第 i 天，下一个更高温度出现在几天后
// 如果气温在这之后都不会升高，请在该位置用 0 来代替。
// 测试链接 : https://leetcode.cn/problems/daily-temperatures/

class Solution
{
public:
    vector<int> dailyTemperatures(vector<int> &temperatures)
    {
        int st[100010];
        int r = 0;
        vector<int> ans(temperatures.size(), 0);
        for (int i = 0; i < temperatures.size(); ++i)
        {
            // 小压大 
            // 相等时候的处理，相等也加入单调栈
            // 确保右侧答案正确
            while (r > 0 && temperatures[st[r - 1]] < temperatures[i])
            {
                int a = st[--r];
                ans[a] = i - a;
            }
            st[r++] = i;
        }
        return ans;
    }
};