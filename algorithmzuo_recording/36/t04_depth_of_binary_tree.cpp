// 求二叉树的最大、最小深度

#include <algorithm>

using namespace std;

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
    // 测试链接 : https://leetcode.cn/problems/maximum-depth-of-binary-tree/
    int maxDepth(TreeNode *root)
    {
        return root == nullptr ? 0 : max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }

    // 测试链接 : https://leetcode.cn/problems/minimum-depth-of-binary-tree/
    int minDepth(TreeNode *root)
    {
        if (root == nullptr)
        {
            // 当前的树是空树
            return 0;
        }
        if (root->left == nullptr && root->right == nullptr)
        {
            // 当前root是叶节点
            return 1;
        }
        int ldeep = INT_MAX;
        int rdeep = INT_MAX;
        if (root->left != nullptr)
        {
            ldeep = minDepth(root->left);
        }
        if (root->right != nullptr)
        {
            rdeep = minDepth(root->right);
        }
        return min(ldeep, rdeep) + 1;
    }
};
