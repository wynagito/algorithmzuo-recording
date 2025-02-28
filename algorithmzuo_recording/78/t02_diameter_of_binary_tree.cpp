// 二叉树的直径
// 给你一棵二叉树的根节点，返回该树的直径
// 二叉树的 直径 是指树中任意两个节点之间最长路径的长度
// 这条路径可能经过也可能不经过根节点 root
// 两节点之间路径的 长度 由它们之间边数表示
// 测试链接 : https://leetcode.cn/problems/diameter-of-binary-tree/

struct Info
{
    int height;
    int diameter;
    Info(int height, int diameter) : height(height), diameter(diameter) {}
}

class Solution
{
public:
    int diameterOfBinaryTree(TreeNode *root)
    {
        return dfs(root)->diameter;
    }

    Info *dfs(TreeNode *root)
    {
        if (!root)
            return new Info(0, 0);
        Info *left = dfs(root->left);
        Info *right = dfs(root->right);
        int height = max(left->height, right->height) + 1;
        int diameter = max(left->diameter, right->diameter, left->height + right->height + 1);
        return new Info(height, diameter);
    }
};