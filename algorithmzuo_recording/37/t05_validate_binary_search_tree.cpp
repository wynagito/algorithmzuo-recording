// 验证搜索二叉树
// 测试链接 : https://leetcode.cn/problems/validate-binary-search-tree/

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
    TreeNode *pre = NULL;
    bool isValidBST(TreeNode *root)
    {
        if (root == NULL)
            return true;
        bool left = isValidBST(root->left);

        if (pre != NULL && pre->val >= root->val)
            return false;
        pre = root; // 记录前一个节点

        bool right = isValidBST(root->right);
        return left && right;
    }
};