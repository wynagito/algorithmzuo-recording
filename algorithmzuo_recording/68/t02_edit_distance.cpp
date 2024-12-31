// 编辑距离
// 给你两个单词 word1 和 word2
// 请返回将 word1 转换成 word2 所使用的最少代价
// 你可以对一个单词进行如下三种操作：
// 插入一个字符，代价a
// 删除一个字符，代价b
// 替换一个字符，代价c
// 测试链接 : https://leetcode.cn/problems/edit-distance/

class Solution
{
public:
    int minDistance(string word1, string word2)
    {
        return editDistance2(word1, word2, 1, 1, 1);
    }

    // 原初尝试版
    // a : s1中插入1个字符的代价
    // b : s1中删除1个字符的代价
    // c : s1中改变1个字符的代价
    // 返回从s1转化成s2的最低代价
    int editDistance1(string s1, string s2, int a, int b, int c)
    {

        int n = s1.size();
        int m = s2.size();
        // dp[i][j] :
        // s1[前缀长度为i]想变成s2[前缀长度为j]，至少付出多少代价
        // 1. s1[i-1]参与
        // 1.1 s1[i-1] 变成 s2[j-1]
        // 1.1.1 s1[i-1] == s2[j-1]，不用操作，dp[i-1][j-1]
        // 1.1.2 s1[i-1]!= s2[j-1]，需要操作，dp[i-1][j-1] + c
        // 1.2 s1[i-1] 不变成 s2[j-1]
        // s1[i-1] 参与在s2[0...j-2] 所以最后将s2[j-1]插入即可 dp[i][j-1]+a
        // 2. s1[i-1] 不参与
        // s1[0...i-2] 变成 s2[0...j-1] 所以最后将s1[i-1]删除 dp[i-1][j]+b
        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        for (int i = 1; i <= n; i++)
        {
            dp[i][0] = i * b;
        }
        for (int j = 1; j <= m; j++)
        {
            dp[0][j] = j * a;
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                int p1 = INT_MAX;
                if (s1[i - 1] == s2[j - 1])
                {
                    p1 = dp[i - 1][j - 1];
                }
                int p2 = INT_MAX;
                if (s1[i - 1] != s2[j - 1])
                {
                    p2 = dp[i - 1][j - 1] + c;
                }
                int p3 = dp[i][j - 1] + a;
                int p4 = dp[i - 1][j] + b;
                dp[i][j] = min(min(p1, p2), min(p3, p4));
            }
        }
        return dp[n][m];
    }

    // 枚举小优化版
    // a : s1中插入1个字符的代价
    // b : s1中删除1个字符的代价
    // c : s1中改变1个字符的代价
    // 返回从s1转化成s2的最低代价
    int editDistance2(string s1, string s2, int a, int b, int c)
    {
        int n = s1.size();
        int m = s2.size();
        // dp[i][j] :
        // s1[前缀长度为i]想变成s2[前缀长度为j]，至少付出多少代价
        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        for (int i = 1; i <= n; i++)
        {
            dp[i][0] = i * b;
        }
        for (int j = 1; j <= m; j++)
        {
            dp[0][j] = j * a;
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (s1[i - 1] == s2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else
                {
                    dp[i][j] = min(min(dp[i - 1][j] + b, dp[i][j - 1] + a), dp[i - 1][j - 1] + c);
                }
            }
        }
        return dp[n][m];
    }

    // 空间压缩
    int editDistance3(string s1, string s2, int a, int b, int c)
    {
        int n = s1.size();
        int m = s2.size();
        vector<int> dp(m + 1);
        for (int j = 1; j <= m; j++)
        {
            dp[j] = j * a;
        }
        for (int i = 1, leftUp, backUp; i <= n; i++)
        {
            leftUp = (i - 1) * b;
            dp[0] = i * b;
            for (int j = 1; j <= m; j++)
            {
                backUp = dp[j];
                if (s1[i - 1] == s2[j - 1])
                {
                    dp[j] = leftUp;
                }
                else
                {
                    dp[j] = min(min(dp[j] + b, dp[j - 1] + a), leftUp + c);
                }
                leftUp = backUp;
            }
        }
        return dp[m];
    }
};