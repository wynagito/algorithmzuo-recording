// 验证完全二叉树
// 测试链接 : https://leetcode.cn/problems/check-completeness-of-a-binary-tree/

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

class Solution {
public:
    bool isCompleteTree(TreeNode* root) {
        if (root == NULL)
            return true;
        
        queue<TreeNode*> q;
        q.push(root);
        // 1. 找到第一个空结点
        while (!q.empty()) 
        { 
            TreeNode* front = q.front();
            q.pop();
            if (front == NULL) 
                break;
            else 
            {
                q.push(front->left);
                q.push(front->right);
            }
        }
        // 2. 检查队列中剩余结点是否有非空结点
        while (!q.empty()) 
        {
            TreeNode* front = q.front();
            q.pop();
            if (front) 
                return false;
        }
        return true;
    }
};