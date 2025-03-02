// 监控二叉树
// 给定一个二叉树，我们在树的节点上安装摄像头
// 节点上的每个摄影头都可以监视其父对象、自身及其直接子对象
// 计算监控树的所有节点所需的最小摄像头数量
// 测试链接 : https://leetcode.cn/problems/binary-tree-cameras/

class Solution
{
private:
    int result;
    // 递归含义
    // 假设x上方一定有父亲的情况下，这个假设很重要
    // x为头的整棵树，最终想都覆盖，
    // 并且想使用最少的摄像头，x应该是什么样的状态
    // 返回值含义
    // 0: x是无覆盖的状态，x下方的节点都已经被覆盖
    // 1: x是覆盖状态，x上没摄像头，x下方的节点都已经被覆盖
    // 2: x是覆盖状态，x上有摄像头，x下方的节点都已经被覆盖
    int traversal(TreeNode *cur)
    {
        if (cur == NULL)
            return 1;
        int left = traversal(cur->left);   // 左
        int right = traversal(cur->right); // 右
        if (left == 1 && right == 1)
            return 0; // 贪心思想，将摄像头安装在 cur 的父节点
        if (left == 0 || right == 0)
        {
            result++;
            return 2;
        }
        return 1; // 有至少1个孩子上安装了摄像头
    }

public:
    int minCameraCover(TreeNode *root)
    {
        result = 0;
        if (traversal(root) == 0)
        { // root 无覆盖
            result++;
        }
        return result;
    }
};