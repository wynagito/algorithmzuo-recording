// 节点数为n高度不大于m的二叉树个数
// 现在有n个节点，计算出有多少个不同结构的二叉树
// 满足节点个数为n且树的高度不超过m的方案
// 因为答案很大，所以答案需要模上1000000007后输出
// 测试链接 : https://www.nowcoder.com/practice/aaefe5896cce4204b276e213e725f3ea

#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 51;

const int MOD = 1000000007;

// 记忆化搜索
vector<vector<long long>> dp1(MAXN, vector<long long>(MAXN, -1));

// 二叉树节点数为n
// 高度不能超过m
// 结构数返回
// 记忆化搜索
int compute1(int n, int m)
{
    if (n == 0)
    {
        return 1;
    }
    // n > 0
    if (m == 0)
    {
        return 0;
    }
    if (dp1[n][m] != -1)
    {
        return (int)dp1[n][m];
    }
    long long ans = 0;
    // n个点，头占掉1个
    for (int k = 0; k < n; k++)
    {
        // 一共n个节点，头节点已经占用了1个名额
        // 如果左树占用k个，那么右树就占用n-k-1个
        ans = (ans + ((long long)compute1(k, m - 1) * compute1(n - k - 1, m - 1)) % MOD) % MOD;
    }
    dp1[n][m] = ans;
    return (int)ans;
}

// 严格位置依赖的动态规划
vector<vector<long long>> dp2(MAXN, vector<long long>(MAXN));

int compute2(int n, int m)
{
    for (int j = 0; j <= m; j++)
    {
        dp2[0][j] = 1;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            dp2[i][j] = 0;
            for (int k = 0; k < i; k++)
            {
                // 一共i个节点，头节点已经占用了1个名额
                // 如果左树占用k个，那么右树就占用i-k-1个
                dp2[i][j] = (dp2[i][j] + dp2[k][j - 1] * dp2[i - k - 1][j - 1] % MOD) % MOD;
            }
        }
    }
    return (int)dp2[n][m];
}

// 空间压缩
vector<long long> dp3(MAXN);

int compute3(int n, int m)
{
    dp3[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        dp3[i] = 0;
    }
    for (int j = 1; j <= m; j++)
    {
        // 根据依赖，一定要先枚举列
        for (int i = n; i >= 1; i--)
        {
            // 再枚举行，而且i不需要到达0，i>=1即可
            dp3[i] = 0;
            for (int k = 0; k < i; k++)
            {
                // 枚举
                dp3[i] = (dp3[i] + dp3[k] * dp3[i - k - 1] % MOD) % MOD;
            }
        }
    }
    return (int)dp3[n];
}

int main()
{
    int n, m;
    while (cin >> n >> m)
    {
        cout << compute3(n, m) << endl;
    }
    return 0;
}