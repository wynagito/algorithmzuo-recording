// 无重复字符的最长子串
// 给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。
// 测试链接 : https://leetcode.cn/problems/longest-substring-without-repeating-characters/

class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        // 每一种字符上次出现的位置
        unordered_map<char, int> hh;
        int ans = 0;
        for (int l = 0, r = 0; r < s.size(); ++r)
        {
            if (hh.find(s[r]) != hh.end())
                l = max(l, hh[s[r]] + 1);
            ans = max(ans, r - l + 1);
            hh[s[r]] = r;
        }
        return ans;
    }
};