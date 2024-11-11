// 幸运数字
// 一共有n个点，编号1~n，由n-1条边连成一棵树，每个点上有数字
// 一共有q条查询，每次返回a到b的路径上，可以随意选择数字，能得到的最大异或和
// 1 <= n <= 2 * 10^4
// 1 <= q <= 2 * 10^5
// 0 <= 点上的数字 <= 2^60
// 测试链接 : https://www.luogu.com.cn/problem/P3292

#include <iostream>

const int MAXN = 20002;
const int LIMIT = 16;
const int BIT = 60;

long long arr[MAXN];
int head[MAXN];
int next[MAXN << 1];
int to[MAXN << 1];
int cnt;

int deep[MAXN];
int stjump[MAXN][LIMIT];
int power;
long long bases[MAXN][BIT + 1];
int levels[MAXN][BIT + 1];

void prepare(int n);
int log2(int n);
void addEdge(int u, int v);
void dfs(int u, int f);
bool insertReplace(long long curv, int curl, long long *basis, int *level);
int lca(int x, int y);
long long query(int x, int y);

void prepare(int n)
{
    cnt = 1;
    std::fill(head + 1, head + n + 1, 0);
    power = log2(n);
}

int log2(int n)
{
    int ans = 0;
    while ((1 << ans) <= (n >> 1))
    {
        ans++;
    }
    return ans;
}

void addEdge(int u, int v)
{
    next[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

void dfs(int u, int f)
{
    deep[u] = deep[f] + 1;
    stjump[u][0] = f;
    for (int p = 1; p <= power; p++)
    {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    for (int i = 0; i <= BIT; i++)
    {
        bases[u][i] = bases[f][i];
        levels[u][i] = levels[f][i];
    }
    insertReplace(arr[u], deep[u], bases[u], levels[u]);
    for (int e = head[u]; e != 0; e = next[e])
    {
        if (to[e] != f)
        {
            dfs(to[e], u);
        }
    }
}

// 插入和替换线性基
bool insertReplace(long long curv, int curl, long long *basis, int *level)
{
    for (int i = BIT; i >= 0; i--)
    {
        if (curv >> i & 1)
        {
            if (basis[i] == 0)
            {
                basis[i] = curv;
                level[i] = curl;
                return true;
            }
            if (curl > level[i])
            {
                std::swap(curv, basis[i]);
                std::swap(curl, level[i]);
            }
            curv ^= basis[i];
        }
    }
    return false;
}

int lca(int x, int y)
{
    if (deep[x] < deep[y])
    {
        std::swap(x, y);
    }
    for (int p = power; p >= 0; p--)
    {
        if (deep[stjump[x][p]] >= deep[y])
        {
            x = stjump[x][p];
        }
    }
    if (x == y)
    {
        return x;
    }
    for (int p = power; p >= 0; p--)
    {
        if (stjump[x][p] != stjump[y][p])
        {
            x = stjump[x][p];
            y = stjump[y][p];
        }
    }
    return stjump[x][0];
}

long long basis[BIT + 1];

long long query(int x, int y)
{
    int lcaNode = lca(x, y);
    long long *basisx = bases[x];
    int *levelx = levels[x];
    long long *basisy = bases[y];
    int *levely = levels[y];
    std::fill(basis, basis + BIT + 1, 0);

    for (int i = BIT; i >= 0; i--)
    {
        long long num = basisx[i];
        if (levelx[i] >= deep[lcaNode] && num != 0)
        {
            basis[i] = num;
        }
    }

    for (int i = BIT; i >= 0; i--)
    {
        long long num = basisy[i];
        if (levely[i] >= deep[lcaNode] && num != 0)
        {
            for (int j = i; j >= 0; j--)
            {
                if (num >> j & 1)
                {
                    if (basis[j] == 0)
                    {
                        basis[j] = num;
                        break;
                    }
                    num ^= basis[j];
                }
            }
        }
    }

    long long ans = 0;
    for (int i = BIT; i >= 0; i--)
    {
        ans = std::max(ans, ans ^ basis[i]);
    }
    return ans;
}

int main()
{
    int n, q;
    std::cin >> n >> q;
    prepare(n);
    for (int i = 1; i <= n; i++)
    {
        std::cin >> arr[i];
    }
    for (int i = 1, u, v; i < n; i++)
    {
        std::cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs(1, 0);
    for (int i = 1, x, y; i <= q; i++)
    {
        std::cin >> x >> y;
        std::cout << query(x, y) << '\n';
    }
    return 0;
}
