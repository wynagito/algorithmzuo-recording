// dfn序
// 用深度优先遍历的方式遍历整棵树
// 给每个节点依次标记序号
// 编号从小到大的顺序就是dfn序

// dfn序 + 每颗子树的大小，可以起到定位子树节点的作用
// 如果某个节点的dfn序号是x，以这个节点为头的子树大小为y
// 那么可知，dfn序号从x ~ x+y-1所代表的节点，都属于这个节点的子树
// 利用这个性质， 节点间的关系判断（题目3、4），跨子树的讨论（题目5） 就会变得方便

// 移除子树后的二叉树高度
// 给你一棵 二叉树 的根节点 root ，树中有 n 个节点
// 每个节点都可以被分配一个从 1 到 n 且互不相同的值
// 另给你一个长度为 m 的数组 queries
// 你必须在树上执行 m 个 独立 的查询，其中第 i 个查询你需要执行以下操作：
// 从树中 移除 以 queries[i] 的值作为根节点的子树
// 题目所用测试用例保证 queries[i] 不等于根节点的值
// 返回一个长度为 m 的数组 answer
// 其中 answer[i] 是执行第 i 个查询后树的高度
// 注意：
// 查询之间是独立的，所以在每个查询执行后，树会回到其初始状态
// 树的高度是从根到树中某个节点的 最长简单路径中的边数
// 测试链接 : https://leetcode.cn/problems/height-of-binary-tree-after-subtree-removal-queries/

class Solution
{
public:
    static const int MAXN = 100010;
    // 节点的值 : dfn序号
    int dfn[MAXN];
    // 下标为都dfn序号 , 值分别是 , 深度 , 子树大小
    // 从左到右每个节点的最大深度
    // , 后者从右到左
    // maxl 和 maxr 是 deep 数组的左右前缀和
    // maxl[i] 表示0...i内的最大深度(离根节点的距离)
    // maxr[i] 表示i...n-1内的最大深度(离根节点的距离)
    int deep[MAXN], size[MAXN], maxl[MAXN], maxr[MAXN];
    int dfnCnt = 0;
    // 来到x节点，从头节点到x节点经过了k条边
    void f(TreeNode *x, int k)
    {
        int i = ++dfnCnt;
        dfn[x->val] = i;
        deep[i] = k;
        size[i] = 1;
        if (x->left != nullptr)
        {
            f(x->left, k + 1);
            size[i] += size[dfn[x->left->val]];
        }
        if (x->right != nullptr)
        {
            f(x->right, k + 1);
            size[i] += size[dfn[x->right->val]];
        }
    }
    vector<int> treeQueries(TreeNode *root, vector<int> &queries)
    {
        f(root, 0);
        // 辅助数组
        for (int i = 1; i <= dfnCnt; i++)
        {
            maxl[i] = max(maxl[i - 1], deep[i]);
        }
        maxr[dfnCnt + 1] = 0;
        for (int i = dfnCnt; i >= 1; i--)
        {
            maxr[i] = max(maxr[i + 1], deep[i]);
        }
        int m = queries.size();
        vector<int> ans(m);
        for (int i = 0; i < m; i++)
        {
            // eg queries[i] = 17 ->  4 dfn -> (0..3) l (4..8) r (9...)
            int leftMax = maxl[dfn[queries[i]] - 1];
            int rightMax = maxr[dfn[queries[i]] + size[dfn[queries[i]]]];
            ans[i] = max(leftMax, rightMax);
        }
        return ans;
    }
};