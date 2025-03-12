// 售货员的难题 - TSP问题
// 某乡有n个村庄(1<=n<=20)，有一个售货员，他要到各个村庄去售货
// 各村庄之间的路程s(1<=s<=1000)是已知的
// 且A村到B村的路程，与B到A的路大多不同(有向带权图)
// 为了提高效率，他从商店出发到每个村庄一次，然后返回商店所在的村，
// 假设商店所在的村庄为1
// 他不知道选择什么样的路线才能使所走的路程最短
// 请你帮他选择一条最短的路
// 测试链接 : https://www.luogu.com.cn/problem/P1171

#include <iostream>
#include <cstring>
#include <climits>   // 用于INT_MAX
#include <algorithm> // 用于std::min

using namespace std;

const int MAXN = 20;     // 最大节点数
int graph[MAXN][MAXN];   // 邻接矩阵存储图
int dp[1 << MAXN][MAXN]; // 状态压缩DP表
int n;                   // 实际节点数

// 初始化DP表为-1
void build()
{
    memset(dp, -1, sizeof(dp)); // 快速初始化整个DP表
}

// 记忆化搜索函数
// s : 村里走没走过的状态，1走过了不要再走了，0可以走
// i : 目前在哪个村
int f(int s, int i)
{
    // 基础情况：所有节点已访问
    if (s == (1 << n) - 1)
    {
        // n : 000011111
        return graph[i][0]; // 返回最后一个节点到起点的距离
    }

    // 查备忘录
    if (dp[s][i] != -1)
    {
        return dp[s][i];
    }

    int ans = INT_MAX;
    // 遍历所有可能的下一节点
    for (int j = 0; j < n; ++j)
    {
        // 0...n-1这些村，都看看是不是下一个落脚点
        if (!(s & (1 << j)))
        { // 如果节点j未访问
            ans = min(ans, graph[i][j] + f(s | (1 << j), j));
        }
    }

    return dp[s][i] = ans; // 存储并返回结果
}

// 计算入口
int compute()
{
    return f(1, 0); // 初始状态：只访问过节点0
}

int main()
{
    // 关闭同步加速输入输出
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n)
    {
        build(); // 初始化DP表

        // 读取邻接矩阵
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                cin >> graph[i][j];
            }
        }

        cout << compute() << "\n"; // 输出结果
    }

    return 0;
}