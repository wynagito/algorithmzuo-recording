// 子矩阵最大累加和问题
// 给定一个二维数组grid，找到其中子矩阵的最大累加和
// 返回拥有最大累加和的子矩阵左上角和右下角坐标
// 如果有多个子矩阵都有最大累加和，返回哪一个都可以
// 测试链接 : https://leetcode.cn/problems/max-submatrix-lcci/

class Solution
{
public:
    // 如果行和列的规模都是n，时间复杂度O(n^3)，最优解了
    vector<int> getMaxMatrix(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        int maxval = INT_MIN;
        int a = 0, b = 0, c = 0, d = 0;
        int *nums = new int[m];
        for (int up = 0; up < n; up++)
        {
            for (int i = 0; i < m; ++i)
                nums[i] = 0;
            for (int down = up; down < n; down++)
            {
                // 如下代码就是题目1的附加问题 :
                // 子数组中找到拥有最大累加和的子数组
                for (int l = 0, r = 0, pre = INT_MIN; r < m; r++)
                {
                    // 压缩矩阵
                    nums[r] += grid[down][r];
                    if (pre >= 0)
                    {
                        pre += nums[r];
                    }
                    else
                    {
                        pre = nums[r];
                        l = r;
                    }
                    if (pre > maxval)
                    {
                        maxval = pre;
                        a = up;
                        b = l;
                        c = down;
                        d = r;
                    }
                }
            }
        }
        return {a, b, c, d};
    }
};