// 路径总和 III
// 给定一个二叉树的根节点 root ，和一个整数 targetSum
// 求该二叉树里节点值之和等于 targetSum 的 路径 的数目
// 路径 不需要从根节点开始，也不需要在叶子节点结束
// 但是路径方向必须是向下的（只能从父节点到子节点）
// 测试链接 : https://leetcode.cn/problems/path-sum-iii/

class Solution
{
public:
    unordered_map<long long, int> prefix; // 前缀和 : 出现次数
    // 全局变量 prefix 要考虑回溯
    // 入参 curr 已保证回溯，不需要额外修改
    int dfs(TreeNode *root, long long curr, int targetSum)
    {
        if (!root)
        {
            return 0;
        }

        int ret = 0;
        curr += root->val;
        if (prefix.count(curr - targetSum))
        {
            ret = prefix[curr - targetSum];
        }

        prefix[curr]++;
        ret += dfs(root->left, curr, targetSum);
        ret += dfs(root->right, curr, targetSum);
        prefix[curr]--; // 回溯

        return ret;
    }

    int pathSum(TreeNode *root, int targetSum)
    {
        prefix[0] = 1;
        return dfs(root, 0, targetSum);
    }
};