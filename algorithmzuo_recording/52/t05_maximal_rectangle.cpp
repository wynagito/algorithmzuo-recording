// 最大矩形
// 给定一个仅包含 0 和 1 、大小为 rows * cols 的二维二进制矩阵
// 找出只包含 1 的最大矩形，并返回其面积
// 测试链接：https://leetcode.cn/problems/maximal-rectangle/

class Solution
{
public:
    int height[210] = {0};
    int stack[210];
    int r;
    int maximalRectangle(vector<vector<char>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            // 来到i行，长方形一定要以i行做底！
            // 加工高度数组(压缩数组)
            for (int j = 0; j < m; j++)
            {
                height[j] = grid[i][j] == '0' ? 0 : height[j] + 1;
            }
            ans = max(largestRectangleArea(m), ans);
        }
        return ans;
    }
    int largestRectangleArea(int m)
    {
        r = 0;
        int ans = 0, cur, left;
        for (int i = 0; i < m; i++)
        {
            // i -> arr[i]
            while (r > 0 && height[stack[r - 1]] >= height[i])
            {
                cur = stack[--r];
                left = r == 0 ? -1 : stack[r - 1];
                ans = max(ans, height[cur] * (i - left - 1));
            }
            stack[r++] = i;
        }
        while (r > 0)
        {
            cur = stack[--r];
            left = r == 0 ? -1 : stack[r - 1];
            ans = max(ans, height[cur] * (m - left - 1));
        }
        return ans;
    }
};