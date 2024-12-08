// 双向广搜常见用途1：小优化
// bfs的剪枝策略，分两侧展开分支，哪侧数量少就从哪侧展开

// 双向广搜常见用途2：重要！本体！用于解决特征很明显的一类问题
// 特征：全量样本不允许递归完全展开，但是半量样本可以完全展开
// 过程：把数据分成两部分，每部分 各自展开 计算结果，然后设计两部分结果的 整合逻辑

// 单词接龙
// 字典 wordList 中从单词 beginWord 和 endWord 的 转换序列
// 是一个按下述规格形成的序列 beginWord -> s1 -> s2 -> ... -> sk ：
// 每一对相邻的单词只差一个字母。
// 对于 1 <= i <= k 时，每个 si 都在 wordList 中
// 注意， beginWord 不需要在 wordList 中。sk == endWord
// 给你两个单词 beginWord 和 endWord 和一个字典 wordList
// 返回 从 beginWord 到 endWord 的 最短转换序列 中的 单词数目
// 如果不存在这样的转换序列，返回 0 。
// 测试链接 : https://leetcode.cn/problems/word-ladder/

class Solution
{
public:
    int ladderLength(string beginWord, string endWord,
                     vector<string> &wordList)
    {
        // 总词表
        unordered_set<string> dict(wordList.begin(), wordList.end());
        // 没有endWord，返回0
        if (!dict.count(endWord))
        {
            return 0;
        }
        unordered_set<string> smallLevel, bigLevel, nextLevel;
        smallLevel.insert(beginWord);
        bigLevel.insert(endWord);
        for (int len = 2; !smallLevel.empty(); len++)
        {
            for (string word : smallLevel)
            {
                // 从小侧扩展
                for (int j = 0; j < word.size(); j++)
                {
                    // 每一位字符都试
                    char old = word[j];
                    for (char change = 'a'; change <= 'z'; change++)
                    {
                        // 每一位字符都从a到z换一遍
                        if (change != old)
                        {
                            word[j] = change;
                            string next = word;
                            if (bigLevel.count(next))
                            {
                                return len;
                            }
                            if (dict.count(next))
                            {
                                dict.erase(next);
                                nextLevel.insert(next);
                            }
                        }
                    }
                    word[j] = old;
                }
            }
            // 每次都从小侧扩展，所以这里要交换smallLevel和bigLevel
            if (nextLevel.size() <= bigLevel.size())
            {
                smallLevel = nextLevel;
            }
            else
            {
                smallLevel = bigLevel;
                bigLevel = nextLevel;
            }
            nextLevel.clear();
        }
        return 0;
    }
};