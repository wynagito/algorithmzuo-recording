// 分组背包：多个物品分组，每组只能取1件
//         每一组的物品都可能性展开就可以了。注意时间复杂度不会升阶，O(物品数量 * 背包容量)

// 分组背包(模版)
// 给定一个正数m表示背包的容量，有n个货物可供挑选
// 每个货物有自己的体积(容量消耗)、价值(获得收益)、组号(分组)
// 同一个组的物品只能挑选1件，所有挑选物品的体积总和不能超过背包容量
// 怎么挑选货物能达到价值最大，返回最大的价值
// 测试链接 : https://www.luogu.com.cn/problem/P1757

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

// 最大物品数量和最大容量
const int MAXN = 1001;
const int MAXM = 1001;

// arr[i][0] 表示第i号物品的体积
// arr[i][1] 表示第i号物品的价值
// arr[i][2] 表示第i号物品的组号
vector<vector<int>> arr(MAXN, vector<int>(3, 0));
int dp[MAXM];
int m, n;

// 使用二维DP表计算结果
int compute1()
{
    int teams = 1;
    for (int i = 2; i <= n; i++)
    {
        if (arr[i - 1][2] != arr[i][2])
        {
            teams++;
        }
    }

    // DP表 dp_table[i][j] 表示前i组物品，容量不超过j时的最大收益
    vector<vector<int>> dp_table(teams + 1, vector<int>(m + 1, 0));

    for (int start = 1, end = 2, i = 1; start <= n; i++)
    {
        while (end <= n && arr[end][2] == arr[start][2])
        {
            end++;
        }

        // 处理组 start 到 end-1
        for (int j = 0; j <= m; j++)
        {
            dp_table[i][j] = dp_table[i - 1][j];
            for (int k = start; k < end; k++)
            {
                if (j - arr[k][0] >= 0)
                {
                    dp_table[i][j] = max(dp_table[i][j], dp_table[i - 1][j - arr[k][0]] + arr[k][1]);
                }
            }
        }
        start = end++;
    }

    return dp_table[teams][m];
}

// 使用压缩后的1D DP表计算结果
int compute2()
{
    // 初始化DP表，所有值设置为0
    memset(dp, 0, sizeof(dp));

    for (int start = 1, end = 2; start <= n;)
    {
        while (end <= n && arr[end][2] == arr[start][2])
        {
            end++;
        }

        // 处理组 start 到 end-1
        for (int j = m; j >= 0; j--)
        {
            for (int k = start; k < end; k++)
            {
                if (j - arr[k][0] >= 0)
                {
                    dp[j] = max(dp[j], arr[k][1] + dp[j - arr[k][0]]);
                }
            }
        }
        start = end++;
    }

    return dp[m];
}

int main()
{

    // 读取输入并处理每个测试用例
    while (cin >> m >> n)
    {
        for (int i = 1; i <= n; i++)
        {
            cin >> arr[i][0] >> arr[i][1] >> arr[i][2];
        }

        // 根据组号排序物品
        sort(arr.begin() + 1, arr.begin() + n + 1, [](const vector<int> &a, const vector<int> &b)
             { return a[2] < b[2]; });

        // 使用 compute1 函数计算结果并输出
        cout << compute1() << endl;

        // 如果你想使用压缩空间的版本，取消下面的注释：
        // cout << compute2() << endl;
    }

    return 0;
}
