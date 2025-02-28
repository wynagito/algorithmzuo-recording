// 树
// 头节点没有父亲，其他节点只有一个父亲的有向无环图，直观理解为发散状
// 在树上，从头节点出发到任何节点的路径是唯一的，不管二叉树还是多叉树都如此

// 树型dp在树上做动态规划，依赖关系比一般动态规划简单
// 因为绝大部分多数都是父依赖子
// 只是依赖关系简单，不代表题目简单

// 树型dp套路
// 1）分析父树得到答案需要子树的哪些信息
// 2）把子树信息的全集定义成递归返回值
// 3）通过递归让子树返回全集信息
// 4）整合子树的全集信息得到父树的全集信息并返回

// 二叉搜索子树的最大键值和
// 给你一棵以 root 为根的二叉树
// 请你返回 任意 二叉搜索子树的最大键值和
// 二叉搜索树的定义如下：
// 任意节点的左子树中的键值都 小于 此节点的键值
// 任意节点的右子树中的键值都 大于 此节点的键值
// 任意节点的左子树和右子树都是二叉搜索树
// 测试链接 : https://leetcode.cn/problems/maximum-sum-bst-in-binary-tree/

struct Info
{
    int maxval;    // 当前子树的最大值
    int minval;    // 当前子树的最小值
    bool isBst;    // 是否是BST
    int maxBstSum; // 最大累加和
    int sumval;    // 当前累加和
    Info(int maxval, int minval, bool isBst, int maxBstSum, int sumval)
        : maxval(maxval), minval(minval), isBst(isBst), maxBstSum(maxBstSum),
          sumval(sumval) {}
};
class Solution
{
public:
    int maxSumBST(TreeNode *root)
    {
        return f(root)->maxBstSum;
    }

    Info *f(TreeNode *x)
    {
        if (x == nullptr)
        {
            return new Info(INT_MIN, INT_MAX, true, 0, 0);
        }
        Info *infol = f(x->left);
        Info *infor = f(x->right);
        int maxval = max(x->val, max(infol->maxval, infor->maxval));
        int minval = min(x->val, min(infol->minval, infor->minval));
        int sumval = infol->sumval + infor->sumval + x->val;
        bool isBst = infol->isBst && infor->isBst && infol->maxval < x->val &&
                     x->val < infor->minval;
        int maxBstSum = max(infol->maxBstSum, infor->maxBstSum);
        if (isBst)
        {
            maxBstSum = max(maxBstSum, sumval);
        }
        return new Info(maxval, minval, isBst, maxBstSum, sumval);
    }
};