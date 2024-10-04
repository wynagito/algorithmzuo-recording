// 验证平衡二叉树
// 测试链接 : https://leetcode.cn/problems/balanced-binary-tree/

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    int dfs(TreeNode *t)
    {
        if (!t)
            return 0;
        int l = dfs(t->left);
        if (l == -1)
            return -1;
        int r = dfs(t->right);
        if (r == -1)
            return -1;
        if (abs(l - r) > 1)
            return -1;
        return max(l, r) + 1;
    }
    bool isBalanced(TreeNode *root)
    {
        return dfs(root) != -1;
    }
};