#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution
{
public:
    int cherryPickup(vector<vector<int>> &grid)
    {
        if (grid.empty() || grid[0].empty())
        {
            return 0; // 处理空网格的情况
        }

        int n = grid.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n, -2)));

        int ans = f(grid, n, 0, 0, 0, dp);
        return ans == -1 ? 0 : ans;
    }

    // 双倍起点同步问题
    // a , b : 第一个人的行列号
    // c , d : 第二个人的行列号
    // a + b - c == d
   int f(vector<vector<int>> &grid, int n, int a, int b, int c, vector<vector<vector<int>>> &dp)
    {
        int d = a + b - c;
        if (a == n || b == n || c == n || d == n || grid[a][b] == -1 || grid[c][d] == -1)
        {
            return -1;
        }
        if (a == n - 1 && b == n - 1)
        {
            return grid[a][b];
        }
        if (dp[a][b][c] != -2)
        {
            return dp[a][b][c];
        }
        int get = (a == c && b == d) ? grid[a][b] : (grid[a][b] + grid[c][d]);
        int next = f(grid, n, a + 1, b, c + 1, dp);
        next = max(next, f(grid, n, a + 1, b, c, dp));
        next = max(next, f(grid, n, a, b + 1, c + 1, dp));
        next = max(next, f(grid, n, a, b + 1, c, dp));
        int ans = -1;
        if (next != -1)
        {
            ans = get + next;
        }
        dp[a][b][c] = ans;
        return ans;
    }
};

int main()
{

    return 0;
}
