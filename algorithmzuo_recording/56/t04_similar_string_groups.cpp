// 相似字符串组
// 如果交换字符串 X 中的两个不同位置的字母，使得它和字符串 Y 相等
// 那么称 X 和 Y 两个字符串相似
// 如果这两个字符串本身是相等的，那它们也是相似的
// 例如，"tars" 和 "rats" 是相似的 (交换 0 与 2 的位置)；
// "rats" 和 "arts" 也是相似的，但是 "star" 不与 "tars"，"rats"，或 "arts" 相似
// 总之，它们通过相似性形成了两个关联组：{"tars", "rats", "arts"} 和 {"star"}
// 注意，"tars" 和 "arts" 是在同一组中，即使它们并不相似
// 形式上，对每个组而言，要确定一个单词在组中，只需要这个词和该组中至少一个单词相似。
// 给你一个字符串列表 strs列表中的每个字符串都是 strs 中其它所有字符串的一个字母异位词。
// 返回 strs 中有多少字符串组
// 测试链接 : https://leetcode.cn/problems/similar-string-groups/

class Solution
{
public:
    int f[310];
    int sets;

    int find(int x) { return f[x] == x ? x : find(f[x]); }

    void merge(int x, int y)
    {
        int fx = find(x), fy = find(y);
        if (fx != fy)
        {
            f[fx] = fy;
            sets--;
        }
    }
    int numSimilarGroups(vector<string> &strs)
    {
        int n = strs.size();
        for (int i = 0; i < n; ++i)
            f[i] = i;
        sets = n;
        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                if (find(i) != find(j))
                {
                    int d = 0; // 两个字符串对应不同字母的个数
                    for (int k = 0; k < strs[i].size() && d < 3; ++k)
                    {
                        if (strs[i][k] != strs[j][k])
                        {
                            d++;
                        }
                    }
                    // 只能至多交换一次
                    if (d == 0 || d == 2)
                    {
                        merge(i, j);
                    }
                }
            }
        }
        return sets;
    }
};