// 好路径的数目
// 给你一棵 n 个节点的树（连通无向无环的图）
// 节点编号从0到n-1，且恰好有n-1条边
// 给你一个长度为 n 下标从 0 开始的整数数组 vals
// 分别表示每个节点的值。同时给你一个二维整数数组 edges
// 其中 edges[i] = [ai, bi] 表示节点 ai 和 bi 之间有一条 无向 边
// 好路径需要满足以下条件：开始和结束节点的值相同、 路径中所有值都小于等于开始的值
// 请你返回不同好路径的数目
// 注意，一条路径和它反向的路径算作 同一 路径
// 比方说， 0 -> 1 与 1 -> 0 视为同一条路径。单个节点也视为一条合法路径
// 测试链接 : https://leetcode.cn/problems/number-of-good-paths/

#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    // 需要保证集合中，代表节点的值，一定是整个集合的最大值
    int father[30010];

    // 集合中最大值的次数，也就是 集合中代表节点的值有几个
    int maxcnt[30010];

    void build(int n)
    {
        for (int i = 0; i < n; i++)
        {
            father[i] = i;
            maxcnt[i] = 1;
        }
    }

    // 这个并查集的优化只来自扁平化
    int find(int i)
    {
        if (i != father[i])
        {
            father[i] = find(father[i]);
        }
        return father[i];
    }

    // 核心！
    // 注意以下的写法！
    // 谁的值大，谁做代表节点
    // 同时注意 maxcnt 的更新
    int merge(int x, int y, vector<int> &vals)
    {
        // fx : x所在集团的代表节点，同时也是x所在集团的最大值下标
        int fx = find(x);
        // fy : y所在集团的代表节点，同时也是y所在集团的最大值下标
        int fy = find(y);
        int path = 0; // 代表路径数目
        if (vals[fx] > vals[fy])
        {
            // 没有好路径
            father[fy] = fx;
        }
        else if (vals[fx] < vals[fy])
        {
            // 没有好路径
            father[fx] = fy;
        }
        else
        {
            // 两个集团最大值一样！
            path = maxcnt[fx] * maxcnt[fy];
            father[fy] = fx;
            maxcnt[fx] += maxcnt[fy];
        }
        return path;
    }

    int numberOfGoodPaths(vector<int> &vals, vector<vector<int>> &edges)
    {
        int n = vals.size();
        build(n);
        int ans = n; // 初始值设为 n，因为每个节点都是一个集合
        // 课上重点讲这个核心排序！
        // 处理边的时候，依次从小节点往大节点处理
        sort(edges.begin(), edges.end(), [&](const vector<int> &e1, const vector<int> &e2)
             { return max(vals[e1[0]], vals[e1[1]]) <
                      max(vals[e2[0]], vals[e2[1]]); });
        for (auto &edge : edges)
        {
            ans += merge(edge[0], edge[1], vals);
        }
        return ans;
    }
};