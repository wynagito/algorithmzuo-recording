// 交错字符串
// 给定三个字符串 s1、s2、s3
// 请帮忙验证s3是否由s1和s2交错组成
// 测试链接 : https://leetcode.cn/problems/interleaving-string/

class Solution
{
public:
    bool isInterleave1(string s1, string s2, string s3)
    {
        if (s1.size() + s2.size() != s3.size())
        {
            return false;
        }
        int n = s1.size();
        int m = s2.size();
        // dp[i][j]:
        // s1[前缀长度为i]和s2[前缀长度为j]，能否交错组成出s3[前缀长度为i+j]
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
        dp[0][0] = true;
        for (int i = 1; i <= n; i++)
        {
            if (s1[i - 1] != s3[i - 1])
            {
                break;
            }
            dp[i][0] = true;
        }
        for (int j = 1; j <= m; j++)
        {
            if (s2[j - 1] != s3[j - 1])
            {
                break;
            }
            dp[0][j] = true;
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                dp[i][j] = (s1[i - 1] == s3[i + j - 1] && dp[i - 1][j]) || (s2[j - 1] == s3[i + j - 1] && dp[i][j - 1]);
            }
        }
        return dp[n][m];
    }

    // 空间压缩
    bool isInterleave2(string s1, string s2, string s3)
    {
        if (s1.size() + s2.size() != s3.size())
        {
            return false;
        }
        int n = s1.size();
        int m = s2.size();
        vector<bool> dp(m + 1, false);
        dp[0] = true;
        for (int j = 1; j <= m; j++)
        {
            if (s2[j - 1] != s3[j - 1])
            {
                break;
            }
            dp[j] = true;
        }
        for (int i = 1; i <= n; i++)
        {
            dp[0] = s1[i - 1] == s3[i - 1] && dp[0];
            for (int j = 1; j <= m; j++)
            {
                dp[j] = (s1[i - 1] == s3[i + j - 1] && dp[j]) || (s2[j - 1] == s3[i + j - 1] && dp[j - 1]);
            }
        }
        return dp[m];
    }
};