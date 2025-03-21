// 规划兼职工作
// 你打算利用空闲时间来做兼职工作赚些零花钱，这里有n份兼职工作
// 每份工作预计从startTime[i]开始、endTime[i]结束，报酬为profit[i]
// 返回可以获得的最大报酬
// 注意，时间上出现重叠的 2 份工作不能同时进行
// 如果你选择的工作在时间X结束，那么你可以立刻进行在时间X开始的下一份工作
// 测试链接 : https://leetcode.cn/problems/maximum-profit-in-job-scheduling/

class Solution
{
public:
    int jobScheduling(vector<int> &startTime, vector<int> &endTime, vector<int> &profit)
    {
        int n = startTime.size();
        vector<vector<int>> jobs(n, vector<int>(3));
        for (int i = 0; i < n; i++)
        {
            jobs[i][0] = startTime[i];
            jobs[i][1] = endTime[i];
            jobs[i][2] = profit[i];
        }

        // 工作按照结束时间从小到大排序
        sort(jobs.begin(), jobs.end(), [](const vector<int> &a, const vector<int> &b)
             { return a[1] < b[1]; });

        // dp[i] 表示前i个工作中的最大收益
        vector<int> dp(n, 0);
        dp[0] = jobs[0][2];
        for (int i = 1, start; i < n; i++)
        {
            start = jobs[i][0];
            // 1. 选第i个工作
            dp[i] = jobs[i][2];
            if (jobs[0][1] <= start)
            {
                dp[i] += dp[find(jobs, i - 1, start)];
            }
            // 2. 不选第i个工作
            dp[i] = max(dp[i], dp[i - 1]);
        }
        return dp[n - 1];
    }

    // job[0...i]范围上，找到结束时间 <= start，最右的下标
    int find(vector<vector<int>> &jobs, int i, int start)
    {
        int ans = 0;
        int l = 0;
        int r = i;
        int m;
        while (l <= r)
        {
            m = (l + r) / 2;
            if (jobs[m][1] <= start)
            {
                ans = m;
                l = m + 1;
            }
            else
            {
                r = m - 1;
            }
        }
        return ans;
    }
};