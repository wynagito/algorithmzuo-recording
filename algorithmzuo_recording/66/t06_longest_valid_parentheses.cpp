// 最长有效括号
// 给你一个只包含 '(' 和 ')' 的字符串
// 找出最长有效（格式正确且连续）括号子串的长度。
// 测试链接 : https://leetcode.cn/problems/longest-valid-parentheses/

class Solution
{
public:
    int dp[30010];
    int longestValidParentheses(string s)
    {
        // dp[0...n-1]
        // dp[i] : 子串必须以i位置的字符结尾的情况下，往左整体有效的最大长度
        // 保证 s[i] 必须是 ')'
        // 否则 dp[i] = 0
        int ans = 0;
        for (int i = 1, p; i < s.size(); i++)
        {
            if (s[i] == ')')
            {
                p = i - dp[i - 1] - 1;
                // )   ?  ( ) ( )  )
                // p-1  p       i-1 i
                if (p >= 0 && s[p] == '(')
                {
                    dp[i] = dp[i - 1] + 2 + (p - 1 >= 0 ? dp[p - 1] : 0);
                }
                // p < 0 --> dp[i] = 0
            }
            // s[i] == '(' --> dp[i] = 0
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};