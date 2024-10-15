// 表现良好的最长时间段
// 给你一份工作时间表 hours，上面记录着某一位员工每天的工作小时数
// 我们认为当员工一天中的工作小时数大于 8 小时的时候，那么这一天就是 劳累的一天
// 所谓 表现良好的时间段 ，意味在这段时间内，「劳累的天数」是严格 大于 不劳累的天数
// 请你返回 表现良好时间段 的最大长度
// 测试链接 : https://leetcode.cn/problems/longest-well-performing-interval/

class Solution
{
public:
    int longestWPI(vector<int> &hours)
    {
        // 某个前缀和，最早出现的位置
        unordered_map<int, int> hh;
        // 0这个前缀和，最早出现在-1，一个数也没有的时候
        hh[0] = -1;
        int ans = 0;
        for (int i = 0, s = 0; i < hours.size(); ++i)
        {
            s += (hours[i] > 8 ? 1 : -1);
            if (s > 0)
            {
                ans = i + 1;
            }
            else
            {
                if (hh.find(s - 1) != hh.end())
                {
                    ans = max(ans, i - hh[s - 1]);
                }
            }
            if (hh.find(s) == hh.end())
            {
                hh[s] = i;
            }
        }
        return ans;
    }
};