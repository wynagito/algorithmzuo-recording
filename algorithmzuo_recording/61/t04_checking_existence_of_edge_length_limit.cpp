// 检查边长度限制的路径是否存在
// 给你一个 n 个点组成的无向图边集 edgeList
// 其中 edgeList[i] = [ui, vi, disi] 表示点 ui 和点 vi 之间有一条长度为 disi 的边
// 请注意，两个点之间可能有 超过一条边 。
// 给你一个查询数组queries ，其中 queries[j] = [pj, qj, limitj]
// 你的任务是对于每个查询 queries[j] ，判断是否存在从 pj 到 qj 的路径
// 且这条路径上的每一条边都 严格小于 limitj 。
// 请你返回一个 布尔数组 answer ，其中 answer.length == queries.length
// 当 queries[j] 的查询结果为 true 时， answer 第 j 个值为 true ，否则为 false
// 测试链接 : https://leetcode.cn/problems/checking-existence-of-edge-length-limited-paths/

class Solution
{
public:
    int father[100010];

    void build(int n)
    {
        for (int i = 0; i < n; i++)
        {
            father[i] = i;
        }
    }

    int find(int i)
    {
        if (i != father[i])
        {
            father[i] = find(father[i]);
        }
        return father[i];
    }

    bool isSameSet(int x, int y) { return find(x) == find(y); }

    void merge(int x, int y) { father[find(x)] = find(y); }
    static bool cmp(const vector<int> &a, const vector<int> &b)
    {
        return a[2] < b[2];
    }
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>> &edges,
                                           vector<vector<int>> &queries)
    {
        sort(edges.begin(), edges.end(), cmp);
        int m = edges.size();
        int k = queries.size();
        vector<vector<int>> questions(k);
        for (int i = 0; i < k; i++)
        {
            questions[i].push_back(queries[i][0]);
            questions[i].push_back(queries[i][1]);
            questions[i].push_back(queries[i][2]);
            questions[i].push_back(i);
        }
        sort(questions.begin(), questions.end(), cmp);
        build(n);
        vector<bool> ans(k);
        for (int i = 0, j = 0; i < k; i++)
        {
            // i : 问题编号
            // j : 边的编号
            for (; j < m && edges[j][2] < questions[i][2]; j++)
            {
                merge(edges[j][0], edges[j][1]);
            }
            ans[questions[i][3]] = isSameSet(questions[i][0], questions[i][1]);
        }
        return ans;
    }
};