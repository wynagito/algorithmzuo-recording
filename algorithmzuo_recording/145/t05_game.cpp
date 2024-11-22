// 游戏(递归版)
// 一共有n个节点，n <= 5000，n为偶数，其中有m个点属于小A，有m个点属于小B，m为n的一半
// 给定n-1条边，节点之间组成一颗树，1号节点是根节点
// 给定长度为n的数组arr，arr[i]的值表示i号节点由谁拥有，0为小A拥有，1为小B拥有
// 游戏有m回合，每回合都有胜负，两人需要选择一个自己拥有、但之前没选过的点，作为本回合当前点
// 小A当前点的子树里有小B当前点，则小A胜；小B当前点的子树里有小A当前点，则小B胜；否则平局
// 返回m回合里能出现k次非平局的游戏方法数，打印k=0..m时的所有答案，对 998244353 取模
// 两场游戏视为不同的定义：当且仅当存在小A拥有的点x，小B在小A选择x的那个回合所选择的点不同
// 测试链接 : https://www.luogu.com.cn/problem/P6478

#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 5001;
const int MOD = 998244353;

int n, m;
int arr[MAXN];
long long fac[MAXN];
long long c[MAXN][MAXN];

// 链式前向星需要
int head[MAXN];
int nxt[MAXN * 2];
int to[MAXN * 2];
int cnt;

// dfs需要
int size[MAXN];
int belong[MAXN][2];
long long dp[MAXN][MAXN];
long long backup[MAXN];

// 反演需要
long long g[MAXN];

// 最后答案
long long f[MAXN];

void build()
{
    cnt = 1;
    fac[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        head[i] = 0;
        fac[i] = fac[i - 1] * i % MOD;
    }
    for (int i = 0; i <= n; i++)
    {
        c[i][0] = 1;
        for (int j = 1; j <= i; j++)
        {
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
        }
    }
}

void addEdge(int u, int v)
{
    nxt[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

void dfs(int u, int fa)
{
    size[u] = 1;
    belong[u][arr[u]] = 1;
    dp[u][0] = 1;
    // 首先计算不包含头节点的方法数
    for (int e = head[u], v; e > 0; e = nxt[e])
    {
        v = to[e];
        if (v != fa)
        {
            dfs(v, u);
            // 之前所有子树结合的计算结果，拷贝进backup
            for (int i = 0; i <= min(size[u] / 2, m); i++)
            {
                backup[i] = dp[u][i];
                dp[u][i] = 0;
            }
            // 树型dp的枚举行为利用子树的节点数做上限进行复杂度优化
            for (int l = 0; l <= min(size[u] / 2, m); l++)
            {
                for (int r = 0; r <= min(size[v] / 2, m - l); r++)
                {
                    dp[u][l + r] = (dp[u][l + r] + backup[l] * dp[v][r] % MOD) % MOD;
                }
            }
            size[u] += size[v];
            belong[u][0] += belong[v][0];
            belong[u][1] += belong[v][1];
        }
    }
    // 最后计算包含头节点的方法数
    // u为头的子树中，对手有几个节点
    int num = belong[u][arr[u] ^ 1];
    // 不包含头节点的方法数，拷贝到backup
    for (int i = 1; i <= min(num, m); i++)
    {
        backup[i] = dp[u][i];
    }
    // 计算包含头节点的方法数，累加上
    for (int i = 1; i <= min(num, m); i++)
    {
        dp[u][i] = (dp[u][i] + backup[i - 1] * (num - i + 1) % MOD) % MOD;
    }
}

void compute()
{
    dfs(1, 0); // dfs是递归版
    for (int i = 0; i <= m; i++)
    {
        g[i] = dp[1][i] * fac[m - i] % MOD;
    }
    for (int k = 0; k <= m; k++)
    {
        for (int i = k; i <= m; i++)
        {
            if (((i - k) & 1) == 0)
            {
                f[k] = (f[k] + c[i][k] * g[i] % MOD) % MOD;
            }
            else
            {
                f[k] = (f[k] + c[i][k] * g[i] % MOD * (MOD - 1) % MOD) % MOD;
            }
        }
    }
}

int main()
{
    cin >> n;
    m = n >> 1;
    build();
    string str;
    cin >> str;
    for (int i = 1; i <= n; i++)
    {
        arr[i] = str[i - 1] - '0';
    }
    for (int i = 1, u, v; i < n; i++)
    {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    compute();
    for (int k = 0; k <= m; k++)
    {
        cout << f[k] << endl;
    }
    return 0;
}
