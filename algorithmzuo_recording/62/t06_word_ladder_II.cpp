// 单词接龙 II
// 按字典 wordList 完成从单词 beginWord 到单词 endWord 转化
// 一个表示此过程的 转换序列 是形式上像
// beginWord -> s1 -> s2 -> ... -> sk 这样的单词序列，并满足：
// 每对相邻的单词之间仅有单个字母不同
// 转换过程中的每个单词 si（1 <= i <= k）必须是字典 wordList 中的单词
// 注意，beginWord 不必是字典 wordList 中的单词
// sk == endWord
// 给你两个单词 beginWord 和 endWord ，以及一个字典 wordList
// 请你找出并返回所有从 beginWord 到 endWord 的 最短转换序列
// 如果不存在这样的转换序列，返回一个空列表
// 每个序列都应该以单词列表 [beginWord, s1, s2, ..., sk] 的形式返回
// 测试链接 : https://leetcode.cn/problems/word-ladder-ii/

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <queue>

using namespace std;

class Solution
{
public:
    // 单词表 ： list -> unordered_set
    unordered_set<string> dict;
    unordered_set<string> curLevel;
    unordered_set<string> nextLevel;

    // 反向图
    // 记录每个单词的反向路径
    // 例如：graph["hit"] = {"hot"} 代表 "hit" 到 "hot" 的反向路径 "hot" -> "hit"
    unordered_map<string, vector<string>> graph;

    // 记录路径,当生成一条有效路的时候，拷贝进ans！
    list<string> path;
    vector<vector<string>> ans;

    void build(const vector<string> &wordList)
    {
        dict.clear();
        for (const auto &word : wordList)
        {
            dict.insert(word);
        }

        graph.clear();
        ans.clear();
        curLevel.clear();
        nextLevel.clear();
    }

    vector<vector<string>> findLadders(const string &beginWord, const string &endWord, const vector<string> &wordList)
    {
        build(wordList);
        // 字典中不存在endWord
        // 直接返回空列表
        if (dict.find(endWord) == dict.end())
        {
            return ans;
        }

        if (bfs(beginWord, endWord))
        {
            dfs(endWord, beginWord);
        }
        return ans;
    }

    // begin -> end ，一层层bfs去，建图
    // 返回值：真的能找到end，返回true；false
    bool bfs(const string &begin, const string &end)
    {
        bool find = false;
        curLevel.insert(begin);

        while (!curLevel.empty())
        {
            // 从字典中移除当前层的单词
            for (const auto &word : curLevel)
            {
                dict.erase(word);
            }

            for (const auto &word : curLevel)
            {
                // word : 去扩
                // 每个位置，字符a~z，换一遍！检查在词表中是否存在
                // 避免，加工出自己
                string w = word;
                for (int i = 0; i < w.length(); i++)
                {
                    char old = w[i];
                    for (char ch = 'a'; ch <= 'z'; ch++)
                    {
                        w[i] = ch;
                        if (dict.find(w) != dict.end() && w != word)
                        {
                            if (w == end)
                            {
                                find = true;
                            }
                            graph[w].push_back(word);
                            nextLevel.insert(w);
                        }
                    }
                    w[i] = old; // 恢复原字符
                }
            }

            if (find)
            {
                return true;
            }
            else
            {
                curLevel = nextLevel;
                nextLevel.clear();
            }
        }
        return false;
    }

    void dfs(const string &word, const string &aim)
    {
        path.push_front(word);
        if (word == aim)
        {
            ans.push_back(vector<string>(path.begin(), path.end()));
        }
        else if (graph.find(word) != graph.end())
        {
            for (const auto &next : graph[word])
            {
                dfs(next, aim);
            }
        }
        path.pop_front();
    }
};