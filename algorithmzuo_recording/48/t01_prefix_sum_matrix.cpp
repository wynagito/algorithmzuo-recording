// 目的是预处理出一个结构，以后每次查询二维数组任何范围上的累加和都是O(1)的操作
// 1 根据原始状况，生成二维前缀和数组sum，
//    sum[i][j]: 代表左上角(0,0)到右下角(i,j)这个范围的累加和
//    sum[i][j] += sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1];
// 2 查询左上角(a,b)到右下角(c,d)这个范围的累加和
//    sum[c][d] - sum[c][b-1] - sum[a-1][d] + sum[a-1][b-1];
// 3 实际过程中往往补第0行、第0列来减少很多条件判断。

// 利用二维前缀和信息迅速得到二维区域和
// 测试链接 : https://leetcode.cn/problems/range-sum-query-2d-immutable/

class NumMatrix
{
public:
    int s[220][220] = {0};
    NumMatrix(vector<vector<int>> &matrix)
    {
        int n = matrix.size(), m = matrix[0].size();
        // 将位序转为从1开始，减少边界讨论
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                s[i][j] = matrix[i - 1][j - 1];
            }
            cout << endl;
        }
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                s[i][j] += (s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1]);
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2)
    {
        return s[row2 + 1][col2 + 1] - s[row1][col2 + 1] - s[row2 + 1][col1] + s[row1][col1];
    }
};