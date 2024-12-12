// 环绕字符串中唯一的子字符串
// 定义字符串 base 为一个 "abcdefghijklmnopqrstuvwxyz" 无限环绕的字符串
// 所以 base 看起来是这样的：
// "..zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd.."
// 给你一个字符串 s ，请你统计并返回 s 中有多少 不同非空子串 也在 base 中出现
// 测试链接 : https://leetcode.cn/problems/unique-substrings-in-wraparound-string/

class Solution
{
public:
    int s[100010], dp[26];
    int findSubstringInWraproundString(string str)
    {
        int n = str.size();
        // abcde...z -> 0, 1, 2, 3, 4....25
        for (int i = 0; i < n; i++)
        {
            s[i] = str[i] - 'a';
        }
        // s : c d e....
        //     2 3 4
        // dp[0] : s中必须以'a'为结尾的子串，最大延伸长度是多少，延伸一定要跟据base串的规则
        // dp[0] = 4 --> xyza
        // 有如下的字串
        // a ; za ; yza ; xyza
        dp[s[0]] = 1;
        for (int i = 1, cur, pre; i < n; i++)
        {
            cur = s[i];
            pre = s[i - 1];
            // pre cur
            if ((pre == 25 && cur == 0) || pre + 1 == cur)
            {
                // (前一个字符是'z' && 当前字符是'a') || 前一个字符比当前字符的ascii码少1
                dp[cur] = max(dp[cur], 1 + dp[pre]);
            }
            else
            {
                // dp[cur] 可能之前更新过 , 所以要与1比较！
                dp[cur] = max(dp[cur], 1);
            }
        }
        int ans = 0;
        for (int i = 0; i < 26; i++)
        {
            ans += dp[i];
        }
        return ans;
    }
};