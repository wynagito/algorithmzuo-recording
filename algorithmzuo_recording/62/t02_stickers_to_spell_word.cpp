// 贴纸拼词
// 我们有 n 种不同的贴纸。每个贴纸上都有一个小写的英文单词。
// 您想要拼写出给定的字符串 target ，方法是从收集的贴纸中切割单个字母并重新排列它们
// 如果你愿意，你可以多次使用每个贴纸，每个贴纸的数量是无限的。
// 返回你需要拼出 target 的最小贴纸数量。如果任务不可能，则返回 -1
// 注意：在所有的测试用例中，所有的单词都是从 1000 个最常见的美国英语单词中随机选择的
// 并且 target 被选择为两个随机单词的连接。
// 测试链接 : https://leetcode.cn/problems/stickers-to-spell-word/

class Solution
{
public:
    int minStickers(vector<string> &stickers, string target)
    {
        vector<vector<string>> graph(26);
        queue<string> qu;
        unordered_set<string> visited;
        // 先搞定前缀
        for (string str : stickers)
        {
            sort(str.begin(), str.end());
            for (int i = 0; i < str.size(); i++)
            {
                // 不重复加
                // aabcf
                // a -> aabcf
                // b -> aabcf
                // c -> aabcf
                // f -> aabcf
                if (i == 0 || str[i] != str[i - 1])
                {
                    graph[str[i] - 'a'].push_back(str);
                }
            }
        }
        sort(target.begin(), target.end());
        visited.insert(target);
        qu.push(target);
        int level = 1;
        // 使用队列的形式是整层弹出
        while (!qu.empty())
        {
            int size = qu.size();
            for (int i = 0; i < size; i++)
            {
                string cur = qu.front();
                qu.pop();
                for (string s : graph[cur[0] - 'a'])
                {
                    string next = nextfunc(cur, s);
                    if (next == "")
                    { // 覆盖完成
                        return level;
                    }
                    else if (!visited.count(next))
                    {
                        visited.insert(next);
                        qu.push(next);
                    }
                }
            }
            level++;
        }
        return -1;
    }
    // target 被 sticker 覆盖后返回的字符串
    // target 和 sticker 事先排好序，其作用就体现在以下代码
    // 可以使用双指针进行合并操作，因为其有序
    string nextfunc(string t, string s)
    {
        string builder = "";
        for (int i = 0, j = 0; i < t.size();)
        {
            if (j == s.size())
            {
                builder += t[i++];
            }
            else
            {
                if (t[i] < s[j])
                {
                    builder += t[i++];
                }
                else if (t[i] > s[j])
                {
                    j++;
                }
                else
                {
                    i++;
                    j++;
                }
            }
        }
        return builder;
    }
};