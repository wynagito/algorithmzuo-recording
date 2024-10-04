// 二叉树的锯齿形层序遍历
// 测试链接 : https://leetcode.cn/problems/binary-tree-zigzag-level-order-traversal/

#include <vector>
#include <queue>
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
    vector<vector<int>> zigzagLevelOrder(TreeNode *root)
    {
        vector<vector<int>> res;
        if (!root)
            return res;
        queue<TreeNode *> qu;
        qu.push(root);
        int cnt = 0;
        while (!qu.empty())
        {
            int size = qu.size();
            vector<int> tmp;
            for (int i = 0; i < size; ++i)
            {
                TreeNode *p = qu.front();
                qu.pop();
                tmp.push_back(p->val);
                if (p->left)
                    qu.push(p->left);
                if (p->right)
                    qu.push(p->right);
            }
            cnt++;
            if (cnt % 2 == 0)
                reverse(tmp.begin(), tmp.end());
            res.push_back(tmp);
        }
        return res;
    }
};