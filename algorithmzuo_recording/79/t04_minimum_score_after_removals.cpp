// 从树中删除边的最小分数
// 存在一棵无向连通树，树中有编号从0到n-1的n个节点，以及n-1条边
// 给你一个下标从0开始的整数数组nums长度为n，其中nums[i]表示第i个节点的值
// 另给你一个二维整数数组edges长度为n-1
// 其中 edges[i] = [ai, bi] 表示树中存在一条位于节点 ai 和 bi 之间的边
// 删除树中两条不同的边以形成三个连通组件，对于一种删除边方案，定义如下步骤以计算其分数：
// 分别获取三个组件每个组件中所有节点值的异或值
// 最大 异或值和 最小 异或值的 差值 就是这种删除边方案的分数
// 返回可能的最小分数
// 测试链接 : https://leetcode.cn/problems/minimum-score-after-removals-on-a-tree/

class Solution
{
public:
    static const int MAXN = 1001;

    int dfn[MAXN], dfnCnt;
    // 下标为dfn序
    int Xor[MAXN], size[MAXN];
    int minimumScore(vector<int> &nums, vector<vector<int>> &edges)
    {
        int n = nums.size();
        vector<vector<int>> g(n);
        for (auto &e : edges)
        {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        dfnCnt = 0;
        memset(dfn, 0, sizeof(dfn));
        memset(Xor, 0, sizeof(Xor));
        memset(size, 0, sizeof(size));
        f(nums, g, 0);
        int m = edges.size();
        int ans = INT_MAX;
        // pre pos 都是dfn序 作用判断 pos是否是pre的子树
        // pre + size[pre] >= pos 说明pos是pre的子树
        for (int i = 0, a, b, pre, pos, sum1, sum2, sum3; i < m; i++)
        {
            a = max(dfn[edges[i][0]], dfn[edges[i][1]]);
            for (int j = i + 1; j < m; j++)
            {
                b = max(dfn[edges[j][0]], dfn[edges[j][1]]);
                if (a < b)
                {
                    pre = a;
                    pos = b;
                }
                else
                {
                    pre = b;
                    pos = a;
                }
                sum1 = Xor[pos];
                // xor[1] : 整棵树的异或和
                // 因为头节点是0，一定拥有最小的dfn序号1
                // f函数调用的时候，也是从0节点开始的
                if (pos < pre + size[pre])
                {
                    sum2 = Xor[pre] ^ Xor[pos];
                    sum3 = Xor[1] ^ Xor[pre];
                }
                else
                {
                    sum2 = Xor[pre];
                    sum3 = Xor[1] ^ sum1 ^ sum2;
                }
                ans = min(ans, max(max(sum1, sum2), sum3) - min(min(sum1, sum2), sum3));
            }
        }
        return ans;
    }

    // 当前来到原始编号u，遍历u的整棵树
    void f(vector<int> &nums, vector<vector<int>> &g, int u)
    {
        int i = ++dfnCnt;
        dfn[u] = i;
        Xor[i] = nums[u];
        size[i] = 1;
        for (int v : g[u])
        {
            if (dfn[v] == 0)
            {
                f(nums, g, v);
                Xor[i] ^= Xor[dfn[v]];
                size[i] += size[dfn[v]];
            }
        }
    }
};