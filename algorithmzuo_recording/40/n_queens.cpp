// 解决N皇后问题的时间复杂度是O(n!)，好的方法可以大量剪枝，大量优化常数时间

// 用数组表示路径的方法（经典、常数时间慢，不推荐）
// 1) 记录之前每一行的皇后放在了什么列
// 2) 来到第i行的时候，可以根据0..i-1行皇后的位置，判断能放哪些列
// 3) 把能放的列都尝试一遍，每次尝试修改路径数组表示当前的决策，后续返回的答案都累加返回

// 用位运算的方法（巧妙、常数时间快，推荐）
// 1) int col   : 0..i-1行皇后放置的位置因为正下方向延伸的原因，哪些列不能再放皇后
// 2) int left  : 0..i-1行皇后放置的位置因为左下方向延伸的原因，哪些列不能再放皇后
// 3) int right : 0..i-1行皇后放置的位置因为右下方向延伸的原因，哪些列不能再放皇后
// 4) 根据col、left、right，用位运算快速判断能放哪些列
// 5) 把能放的列都尝试一遍，每次尝试修改3个数字表示当前的决策，后续返回的答案都累加返回

// N皇后问题
// 测试链接 : https://leetcode.cn/problems/n-queens-ii/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Solution
{
public:
    // 用数组表示路径实现的N皇后问题，不推荐
    int totalNQueens1(int n)
    {
        if (n < 1)
        {
            return 0;
        }
        vector<int> path(n);
        return f1(0, path, n);
    }

    // i : 当前来到的行
    // path : 0...i-1行的皇后，都摆在了哪些列
    // n : 是几皇后问题
    // 返回 : 0...i-1行已经摆完了，i....n-1行可以去尝试的情况下还能找到几种有效的方法
    int f1(int i, vector<int> &path, int n)
    {
        if (i == n)
        {
            return 1;
        }

        int ans = 0;
        // 0 1 2 3 .. n-1
        // i j
        for (int j = 0; j < n; j++)
        {
            if (check(path, i, j))
            {
                path[i] = j;
                ans += f1(i + 1, path, n);
            }
        }
        return ans;
    }

    // 当前在i行、j列的位置，摆了一个皇后
    // 0...i-1行的皇后状况，path[0...i-1]
    // 返回会不会冲突，不会冲突，有效！true
    // 会冲突，无效，返回false
    bool check(const vector<int> &path, int i, int j)
    {
        for (int k = 0; k < i; k++)
        {
            // 同一列 或 斜线冲突
            if (j == path[k] || abs(i - k) == abs(j - path[k]))
            {
                return false;
            }
        }
        return true;
    }

    // 用位信息表示路径实现的N皇后问题，推荐
    int totalNQueens2(int n)
    {
        if (n < 1)
        {
            return 0;
        }
        // n = 5
        // 1 << 5 = 0...100000 - 1
        // limit  = 0...011111;
        // n = 7
        // limit  = 0...01111111;
        int limit = (1 << n) - 1;
        return f2(limit, 0, 0, 0);
    }

    // limit : 当前是几皇后问题
    // 之前皇后的列影响：col
    // 之前皇后的右上 -> 左下对角线影响：left
    // 之前皇后的左上 -> 右下对角线影响：right
    int f2(int limit, int col, int left, int right)
    {
        if (col == limit)
        {
            // 所有皇后放完了！
            return 1;
        }
        // 总限制
        int ban = col | left | right;
        // ~ban : 1可放皇后，0不能放
        int candidate = limit & (~ban);
        // 放置皇后的尝试！
        int place = 0;
        // 一共有多少有效的方法
        int ans = 0;
        while (candidate != 0)
        {
            // 提取出最右侧的1
            // 0 0 1 1 1 0
            // 5 4 3 2 1 0
            // place :
            // 0 0 0 0 1 0
            // candidate :
            // 0 0 1 1 0 0
            // 5 4 3 2 1 0
            // place :
            // 0 0 0 1 0 0
            // candidate :
            // 0 0 1 0 0 0
            // 5 4 3 2 1 0
            // place :
            // 0 0 1 0 0 0
            // candidate :
            // 0 0 0 0 0 0
            // 5 4 3 2 1 0
            place = candidate & (-candidate);
            candidate ^= place;
            ans += f2(limit, col | place, (left | place) >> 1, (right | place) << 1);
        }
        return ans;
    }
};
