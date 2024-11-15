// 火星词典
// 现有一种使用英语字母的火星语言
// 这门语言的字母顺序对你来说是未知的。
// 给你一个来自这种外星语言字典的字符串列表 words
// words 中的字符串已经 按这门新语言的字母顺序进行了排序 。
// 如果这种说法是错误的，并且给出的 words 不能对应任何字母的顺序，则返回 ""
// 否则，返回一个按新语言规则的 字典递增顺序 排序的独特字符串
// 如果有多个解决方案，则返回其中任意一个
// words中的单词一定都是小写英文字母组成的
// 测试链接 : https://leetcode.cn/problems/alien-dictionary/
// 测试链接(不需要会员) : https://leetcode.cn/problems/Jf1JuT/

class Solution
{
public:
    string alienOrder(vector<string> &words)
    {
        int indegree[26];
        memset(indegree, -1, sizeof(indegree));
        for (string w : words)
        {
            for (int i = 0; i < w.size(); i++)
            {
                indegree[w[i] - 'a'] = 0;
            }
        }
        // 'a' -> 0
        // 'b' -> 1
        // 'z' -> 25
        // x -> x - 'a'
        vector<vector<int>> graph(26, vector<int>());
        for (int i = 0, j, len; i < words.size() - 1; i++)
        {
            string cur = words[i];
            string next = words[i + 1];
            j = 0;
            len = min(cur.size(), next.size());
            for (; j < len; j++)
            {
                if (cur[j] != next[j])
                {
                    graph[cur[j] - 'a'].push_back(next[j] - 'a');
                    indegree[next[j] - 'a']++;
                    break;
                }
            }
            if (j < cur.size() && j == next.size())
            {
                return "";
            }
        }
        int queue[26];
        int l = 0, r = 0;
        int kinds = 0;
        for (int i = 0; i < 26; i++)
        {
            if (indegree[i] != -1)
            {
                kinds++;
            }
            if (indegree[i] == 0)
            {
                queue[r++] = i;
            }
        }
        string ans = "";
        while (l < r)
        {
            int cur = queue[l++];
            ans += (char)(cur + 'a');
            for (int next : graph[cur])
            {
                if (--indegree[next] == 0)
                {
                    queue[r++] = next;
                }
            }
        }
        return ans.size() == kinds ? ans : "";
    }
};