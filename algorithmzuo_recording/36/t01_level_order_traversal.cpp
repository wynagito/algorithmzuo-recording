// 二叉树的层序遍历
// 测试链接 : https://leetcode.cn/problems/binary-tree-level-order-traversal/

#include <vector>
#include <queue>
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
    vector<vector<int>> res;
    void bfs(TreeNode *r)
    {
        queue<TreeNode *> qu;
        qu.push(r);
        while (!qu.empty())
        {
            int n = qu.size();
            vector<int> tmp;
            for (int i = 0; i < n; ++i)
            {
                TreeNode *p = qu.front();
                qu.pop();
                tmp.push_back(p->val);
                if (p->left)
                {
                    qu.push(p->left);
                }
                if (p->right)
                {
                    qu.push(p->right);
                }
            }
            res.push_back(tmp);
        }
    }
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        if (!root)
            return res;
        bfs(root);
        return res;
    }
};