// 二叉树的最大特殊宽度
// 测试链接 : https://leetcode.cn/problems/maximum-width-of-binary-tree/

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
    TreeNode *qu[3030];
    unsigned long long iq[3030];
    int l = 0, r = 0;
    int widthOfBinaryTree(TreeNode *root)
    {
        qu[r] = root;
        iq[r++] = 1L;
        unsigned long long res = 1;
        while (l < r)
        {
            int size = r - l;
            res = max(res, iq[r - 1] - iq[l] + 1);
            for (int i = 0; i < size; ++i)
            {
                TreeNode *p = qu[l];
                unsigned long long id = iq[l++];
                if (p->left)
                {
                    qu[r] = p->left;
                    iq[r++] = id * 2;
                }
                if (p->right)
                {
                    qu[r] = p->right;
                    iq[r++] = id * 2 + 1;
                }
            }
        }
        return res;
    }
};