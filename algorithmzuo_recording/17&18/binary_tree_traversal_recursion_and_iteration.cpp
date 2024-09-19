#include <vector>
#include <stack>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
                                                       right(right) {}
};

// 递归方法
vector<int> preorderTraversal(TreeNode *root)
{
    vector<int> ans;
    if (root == nullptr)
        return ans;
    ans.push_back(root->val);
    if (root->left)
    {
        vector<int> left_ans = preorderTraversal(root->left);
        for (int i : left_ans)
            ans.push_back(i);
    }
    if (root->right)
    {
        vector<int> right_ans = preorderTraversal(root->right);
        for (int i : right_ans)
            ans.push_back(i);
    }
    return ans;
}

vector<int> inorderTraversal(TreeNode *root)
{
    vector<int> ans;
    if (root == nullptr)
        return ans;
    if (root->left)
    {
        vector<int> left_ans = inorderTraversal(root->left);
        for (int i : left_ans)
            ans.push_back(i);
    }
    ans.push_back(root->val);
    if (root->right)
    {
        vector<int> right_ans = inorderTraversal(root->right);
        for (int i : right_ans)
            ans.push_back(i);
    }
    return ans;
}

vector<int> postorderTraversal(TreeNode *root)
{
    vector<int> ans;
    if (root == nullptr)
        return ans;
    if (root->left)
    {
        vector<int> left_ans = postorderTraversal(root->left);
        for (int i : left_ans)
            ans.push_back(i);
    }
    if (root->right)
    {
        vector<int> right_ans = postorderTraversal(root->right);
        for (int i : right_ans)
            ans.push_back(i);
    }
    ans.push_back(root->val);
    return ans;
}

// 用一个栈完成先序遍历
// 根左右 对应入栈顺序 反过来即可
// 测试链接 : https://leetcode.cn/problems/binary-tree-preorder-traversal/
vector<int> preorderTraversal(TreeNode *head)
{
    vector<int> ans;
    if (head != nullptr)
    {
        stack<TreeNode *> stk;
        stk.push(head);
        while (!stk.empty())
        {
            head = stk.top();
            stk.pop();
            ans.push_back(head->val);
            if (head->right != nullptr)
            {
                stk.push(head->right);
            }
            if (head->left != nullptr)
            {
                stk.push(head->left);
            }
        }
    }
    return ans;
}

// 用一个栈完成中序遍历
// 测试链接 : https://leetcode.cn/problems/binary-tree-inorder-traversal/
vector<int> inorderTraversal(TreeNode *head)
{
    vector<int> ans;
    stack<TreeNode *> stk;
    while (!stk.empty() || head != nullptr)
    {
        if (head != nullptr)
        {
            stk.push(head);
            head = head->left;
        }
        else
        {
            head = stk.top();
            stk.pop();
            ans.push_back(head->val);
            head = head->right;
        }
    }
    return ans;
}

// 用两个栈完成后序遍历
// 根右左 反过来 左右根
// 测试链接 : https://leetcode.cn/problems/binary-tree-postorder-traversal/
vector<int> postorderTraversalTwoStacks(TreeNode *head)
{
    vector<int> ans;
    if (head != nullptr)
    {
        stack<TreeNode *> stk;
        stack<TreeNode *> collect;
        stk.push(head);
        while (!stk.empty())
        {
            head = stk.top();
            stk.pop();
            collect.push(head);
            if (head->left != nullptr)
            {
                stk.push(head->left);
            }
            if (head->right != nullptr)
            {
                stk.push(head->right);
            }
        }
        while (!collect.empty())
        {
            ans.push_back(collect.top()->val);
            collect.pop();
        }
    }
    return ans;
}

// 用一个栈完成后序遍历
vector<int> postorderTraversalOneStack(TreeNode *h)
{
    vector<int> ans;
    if (h != nullptr)
    {
        stack<TreeNode *> stk;
        stk.push(h);
        // 如果始终没有打印过节点，h就一直是头节点
        // 一旦打印过节点，h就变成打印节点
        // 之后h的含义 : 上一次打印的节点
        while (!stk.empty())
        {
            TreeNode *cur = stk.top();
            if (cur->left != nullptr && h != cur->left && h != cur->right)
            {
                // 有左树且左树没处理过
                stk.push(cur->left);
            }
            else if (cur->right != nullptr && h != cur->right)
            {
                // 有右树且右树没处理过
                stk.push(cur->right);
            }
            else
            {
                // 左树、右树 没有 或者 都处理过了
                ans.push_back(cur->val);
                h = stk.top();
                stk.pop();
            }
        }
    }
    return ans;
}