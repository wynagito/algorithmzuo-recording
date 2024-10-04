// 二叉树打家劫舍问题
// 测试链接 : https://leetcode.cn/problems/house-robber-iii/

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
    int yes = 0; // 打劫当前房屋的最大金额
    int no = 0;  // 不打劫当前房屋的最大金额
    int rob(TreeNode *root)
    {
        f(root);
        return max(yes, no);
    }
    
    void f(TreeNode *r)
    {
        if (!r)
        {
            yes = 0;
            no = 0;
            return;
        }
        else
        {
            int y = r->val; // 已打劫
            int n = 0;      // 不打劫
            f(r->left);
            y += no;           // 相连房屋不打劫的最大金额
            n += max(yes, no); //  max(打劫相连房屋 , 不打劫相连房屋)
            f(r->right);
            y += no;
            n += max(yes, no);
            yes = y;
            no = n;
        }
    }
};
