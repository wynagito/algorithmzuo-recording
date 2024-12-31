// 不同的子序列
// 给你两个字符串s和t ，统计并返回在s的子序列中t出现的个数
// 答案对 1000000007 取模
// 测试链接 : https://leetcode.cn/problems/distinct-subsequences/

class Solution
{
public:
    int numDistinct1(string s, string t)
    {
        int mod = 1000000007;
        int n = s.size();
        int m = t.size();
        // dp[i][j] :
        // s[前缀长度为i]的所有子序列中，有多少个子序列等于t[前缀长度为j]
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int i = 0; i <= n; i++)
        {
            dp[i][0] = 1;
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                // 不要s[i-1]
                dp[i][j] = dp[i - 1][j];
                // 要s[i-1]
                if (s[i - 1] == t[j - 1])
                {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % mod;
                }
            }
        }
        return dp[n][m];
    }

    // 空间压缩
    // 本题说了要取模，所以增加取模的逻辑
    int numDistinct2(string s, string t)
    {
        int mod = 1000000007;
        int n = s.size();
        int m = t.size();
        vector<int> dp(m + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= n; i++)
        {
            for (int j = m; j >= 1; j--)
            {
                if (s[i - 1] == t[j - 1])
                {
                    dp[j] = (dp[j] + dp[j - 1]) % mod;
                }
            }
        }
        return dp[m];
    }
};