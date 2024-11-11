// 路径最大异或和
// 一共有n个点，编号1~n，由m条无向边连接
// 每条边有权值，输入保证图是连通的，可能有环
// 找到1到n的一条路径，路径可以重复经过某些点或边
// 当一条边在路径中出现了多次时，异或的时候也要算多次
// 希望找到一条从1到n的路径，所有边权异或和尽量大，返回这个最大异或和
// 1 <= n <= 50000
// 1 <= m <= 100000
// 0 <= 边权 <= 10^18
// 测试链接 : https://www.luogu.com.cn/problem/P4151

#include <iostream>
#include <algorithm>
#include <cstring>

const int MAXN = 50001;
const int MAXM = 200002;
const int BIT = 60;

// 链式前向星
int head[MAXN];
int next[MAXM];
int to[MAXM];
long long weight[MAXM];
int cnt;

// 所有环的异或和构建的线性基
long long basis[BIT + 1];

// 某个节点在dfs过程中是否被访问过
bool visited[MAXN];

// 从头结点到当前节点的异或和
long long path[MAXN];

void prepare(int n);
void addEdge(int u, int v, long long w);
bool insert(long long num);
void dfs(int u, int f, long long p);
long long query(long long init);

void prepare(int n)
{
    cnt = 1;
    std::fill(head + 1, head + n + 1, 0);
    std::fill(basis, basis + BIT + 1, 0);
}

void addEdge(int u, int v, long long w)
{
    next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

bool insert(long long num)
{
    for (int i = BIT; i >= 0; i--)
    {
        if ((num >> i) & 1)
        {
            if (basis[i] == 0)
            {
                basis[i] = num;
                return true;
            }
            num ^= basis[i];
        }
    }
    return false;
}

void dfs(int u, int f, long long p)
{
    path[u] = p;
    visited[u] = true;
    for (int e = head[u]; e != 0; e = next[e])
    {
        int v = to[e];
        if (v != f)
        {
            long long xorValue = p ^ weight[e];
            if (visited[v])
            {
                insert(xorValue ^ path[v]);
            }
            else
            {
                dfs(v, u, xorValue);
            }
        }
    }
}

long long query(long long init)
{
    for (int i = BIT; i >= 0; i--)
    {
        init = std::max(init, init ^ basis[i]);
    }
    return init;
}

int main()
{

    int n, m;
    std::cin >> n >> m;
    prepare(n);

    for (int i = 1; i <= m; i++)
    {
        int u, v;
        long long w;
        std::cin >> u >> v >> w;
        addEdge(u, v, w);
        addEdge(v, u, w);
    }

    dfs(1, 0, 0);
    std::cout << query(path[n]) << std::endl;

    return 0;
}
