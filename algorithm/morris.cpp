#include <vector>
#include <iostream>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Morris遍历
void morris(TreeNode *head)
{
    TreeNode *cur = head;
    TreeNode *mostRight = nullptr;
    while (cur != nullptr)
    {
        mostRight = cur->left;
        if (mostRight != nullptr)
        { // cur有左树
            // 找到左树最右节点
            // 注意左树最右节点的右指针可能指向空，也可能指向cur
            while (mostRight->right != nullptr && mostRight->right != cur)
            {
                mostRight = mostRight->right;
            }
            // 判断左树最右节点的右指针状态
            if (mostRight->right == nullptr)
            { // 第一次到达
                mostRight->right = cur;
                cur = cur->left;
            }
            else
            { // 第二次到达
                mostRight->right = nullptr;
                cur = cur->right;
            }
        }
        else
        {
            cur = cur->right;
        }
    }
}

// Morris遍历实现先序遍历
std::vector<int> preorderTraversal(TreeNode *head)
{
    std::vector<int> ans;
    morrisPreorder(head, ans);
    return ans;
}

void morrisPreorder(TreeNode *head, std::vector<int> &ans)
{
    TreeNode *cur = head;
    TreeNode *mostRight = nullptr;
    while (cur != nullptr)
    {
        mostRight = cur->left;
        if (mostRight != nullptr)
        { // cur有左树
            // 找到左树最右节点
            // 注意左树最右节点的右指针可能指向空，也可能指向cur
            while (mostRight->right != nullptr && mostRight->right != cur)
            {
                mostRight = mostRight->right;
            }
            // 判断左树最右节点的右指针状态
            if (mostRight->right == nullptr)
            { // 第一次到达
                ans.push_back(cur->val);
                mostRight->right = cur;
                cur = cur->left;
                continue;
            }
            else
            { // 第二次到达
                mostRight->right = nullptr;
            }
        }
        else
        { // cur无左树
            ans.push_back(cur->val);
        }
        cur = cur->right;
    }
}

// Morris遍历实现中序遍历
std::vector<int> inorderTraversal(TreeNode *head)
{
    std::vector<int> ans;
    morrisInorder(head, ans);
    return ans;
}

void morrisInorder(TreeNode *head, std::vector<int> &ans)
{
    TreeNode *cur = head;
    TreeNode *mostRight = nullptr;
    while (cur != nullptr)
    {
        mostRight = cur->left;
        if (mostRight != nullptr)
        { // cur有左树
            // 找到左树最右节点
            // 注意左树最右节点的右指针可能指向空，也可能指向cur
            while (mostRight->right != nullptr && mostRight->right != cur)
            {
                mostRight = mostRight->right;
            }
            // 判断左树最右节点的右指针状态
            if (mostRight->right == nullptr)
            { // 第一次到达
                mostRight->right = cur;
                cur = cur->left;
                continue;
            }
            else
            { // 第二次到达
                mostRight->right = nullptr;
            }
        }
        ans.push_back(cur->val);
        cur = cur->right;
    }
}

// 提交如下的方法
std::vector<int> postorderTraversal(TreeNode *head)
{
    std::vector<int> ans;
    morrisPostorder(head, ans);
    return ans;
}

void morrisPostorder(TreeNode *head, std::vector<int> &ans)
{
    TreeNode *cur = head;
    TreeNode *mostRight = nullptr;
    while (cur != nullptr)
    {
        mostRight = cur->left;
        if (mostRight != nullptr)
        { // cur有左树
            // 找到左树最右节点
            // 注意左树最右节点的右指针可能指向空，也可能指向cur
            while (mostRight->right != nullptr && mostRight->right != cur)
            {
                mostRight = mostRight->right;
            }
            // 判断左树最右节点的右指针状态
            if (mostRight->right == nullptr)
            { // 第一次到达
                mostRight->right = cur;
                cur = cur->left;
                continue;
            }
            else
            { // 第二次到达
                mostRight->right = nullptr;
                collect(cur->left, ans);
            }
        }
        cur = cur->right;
    }
    collect(head, ans);
}

// 以head为头的子树，树的右边界逆序收集
void collect(TreeNode *head, std::vector<int> &ans)
{
    TreeNode *tail = reverse(head);
    TreeNode *cur = tail;
    while (cur != nullptr)
    {
        ans.push_back(cur->val);
        cur = cur->right;
    }
    reverse(tail);
}

// 从from出发，类似单链表翻转，去翻转right指针的方向
TreeNode *reverse(TreeNode *from)
{
    TreeNode *pre = nullptr;
    TreeNode *next = nullptr;
    while (from != nullptr)
    {
        next = from->right;
        from->right = pre;
        pre = from;
        from = next;
    }
    return pre;
}

// 提交如下的方法
bool isValidBST(TreeNode *head)
{
    TreeNode *cur = head;
    TreeNode *mostRight = nullptr;
    // 前一个遍历的节点
    TreeNode *pre = nullptr;
    bool ans = true;
    while (cur != nullptr)
    {
        mostRight = cur->left;
        if (mostRight != nullptr)
        {
            while (mostRight->right != nullptr && mostRight->right != cur)
            {
                mostRight = mostRight->right;
            }
            if (mostRight->right == nullptr)
            {
                mostRight->right = cur;
                cur = cur->left;
                continue;
            }
            else
            {
                mostRight->right = nullptr;
            }
        }
        if (pre != nullptr && pre->val >= cur->val)
        {
            // 不能直接返回
            // 树是乱序的
            // 只有T->F的逻辑
            // 所以最终结果是对的
            ans = false;
        }
        pre = cur;
        cur = cur->right;
    }
    return ans;
}

// 提交如下的方法
int minDepth(TreeNode *head)
{
    if (head == nullptr)
    {
        return 0;
    }
    TreeNode *cur = head;
    TreeNode *mostRight = nullptr;
    // morris遍历中，上一个节点所在的层数
    int preLevel = 0;
    // 树的右边界长度
    int rightLen;
    int ans = INT_MAX;
    while (cur != nullptr)
    {
        mostRight = cur->left;
        if (mostRight != nullptr)
        {
            rightLen = 1;
            while (mostRight->right != nullptr && mostRight->right != cur)
            {
                rightLen++;
                mostRight = mostRight->right;
            }
            if (mostRight->right == nullptr)
            {
                preLevel++;
                mostRight->right = cur;
                cur = cur->left;
                continue;
            }
            else
            {
                if (mostRight->left == nullptr)
                {
                    ans = std::min(ans, preLevel);
                }
                preLevel -= rightLen;
                mostRight->right = nullptr;
            }
        }
        else
        {
            preLevel++;
        }
        cur = cur->right;
    }
    // 不要忘了整棵树的最右节点
    rightLen = 1;
    cur = head;
    while (cur->right != nullptr)
    {
        rightLen++;
        cur = cur->right;
    }
    // 整棵树的最右节点是叶节点才纳入统计
    if (cur->left == nullptr)
    {
        ans = std::min(ans, rightLen);
    }
    return ans;
}

// 提交以下的方法
TreeNode *lowestCommonAncestor(TreeNode *head, TreeNode *o1, TreeNode *o2)
{
    if (preOrder(o1->left, o1, o2) != nullptr || preOrder(o1->right, o1, o2) != nullptr)
    {
        return o1;
    }
    if (preOrder(o2->left, o1, o2) != nullptr || preOrder(o2->right, o1, o2) != nullptr)
    {
        return o2;
    }
    TreeNode *left = preOrder(head, o1, o2);
    TreeNode *cur = head;
    TreeNode *mostRight = nullptr;
    TreeNode *lca = nullptr;
    while (cur != nullptr)
    {
        mostRight = cur->left;
        if (mostRight != nullptr)
        {
            while (mostRight->right != nullptr && mostRight->right != cur)
            {
                mostRight = mostRight->right;
            }
            if (mostRight->right == nullptr)
            {
                mostRight->right = cur;
                cur = cur->left;
                continue;
            }
            else
            { // 第二次来到cur
                mostRight->right = nullptr;
                if (lca == nullptr)
                {
                    // 检查left是否在cur左树的右边界上
                    if (rightCheck(cur->left, left))
                    {
                        // 检查left看看右树里是否有o2
                        if (preOrder(left->right, o1, o2) != nullptr)
                        {
                            lca = left;
                        }
                        left = cur;
                        // 为什么此时检查的是left而不是cur
                        // 因为cur右树上的某些右指针可能没有恢复回来
                        // 需要等右指针恢复回来之后检查才不出错
                        // 所以此时检查的是left而不是cur
                        // 课上已经重点图解了
                    }
                }
            }
        }
        cur = cur->right;
    }
    // 如果morris遍历结束了还没有收集到答案
    // 此时最后一个left还没有验证，它一定是答案
    return lca != nullptr ? lca : left;
}

// 以head为头的树进行先序遍历，o1和o2谁先被找到就返回谁
TreeNode *preOrder(TreeNode *head, TreeNode *o1, TreeNode *o2)
{
    TreeNode *cur = head;
    TreeNode *mostRight = nullptr;
    TreeNode *ans = nullptr;
    while (cur != nullptr)
    {
        mostRight = cur->left;
        if (mostRight != nullptr)
        {
            while (mostRight->right != nullptr && mostRight->right != cur)
            {
                mostRight = mostRight->right;
            }
            if (mostRight->right == nullptr)
            {
                if (ans == nullptr && (cur == o1 || cur == o2))
                {
                    ans = cur;
                }
                mostRight->right = cur;
                cur = cur->left;
                continue;
            }
            else
            {
                mostRight->right = nullptr;
            }
        }
        else
        {
            if (ans == nullptr && (cur == o1 || cur == o2))
            {
                ans = cur;
            }
        }
        cur = cur->right;
    }
    return ans;
}

// 以head为头的树遍历右边界，返回是否找到了target
bool rightCheck(TreeNode *head, TreeNode *target)
{
    while (head != nullptr)
    {
        if (head == target)
        {
            return true;
        }
        head = head->right;
    }
    return false;
}
