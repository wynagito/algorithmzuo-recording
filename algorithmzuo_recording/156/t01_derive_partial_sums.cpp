// 带权并查集的原理，一维数轴相对距离模型
// 1，点权代表当前节点到集合头节点的距离，并不保证实时正确，可以经过find过程修正正确
// 2，void union(l, r, v)，l和r属于两个集合，并且l到r距离为v，合并两个集合
//     find(l)头为lf，find(r)头rf，find过程会修正dist[l]和dist[r]
//     father[lf] = rf
//     dist[lf] = dist[r] - dist[l] + v
// 3，int find(i)，寻找i所在集合的头，同时修正dist[i]的值
//     路径压缩之前i的父为t，路径压缩之后，dist[i] += dist[t]
// 4，int query(l, r)，查询l和r之间的距离关系
//     find(l) == find(r)，才有距离关系，距离 = dist[l] - dist[r]

// 带权并查集的所有变化，都来自一维数轴相对距离模型

// 推导部分和，带权并查集模版题1
// 有n个数字，下标1 ~ n，但是并不知道每个数字是多少
// 先给出m个数字段的累加和，再查询q个数字段的累加和
// 给出数字段累加和的操作 l r v，代表l~r范围上的数字，累加和为v
// 查询数字段累加和的操作 l r，代表查询l~r范围上的数字累加和
// 请根据m个给定，完成q个查询，如果某个查询无法给出答案，打印"UNKNOWN"
// 1 <= n, m, q <= 10^5
// 累加和不会超过long类型范围
// 测试链接 : https://www.luogu.com.cn/problem/P8779

#include <iostream>
#include <vector>
#include <climits>
#include <cstdio>
using namespace std;

const int MAXN = 100002;
const long long INF = LLONG_MAX;

int n, m, q;
vector<int> father(MAXN);
vector<long long> dist(MAXN);

void prepare()
{
    for (int i = 0; i <= n; i++)
    {
        father[i] = i;
        dist[i] = 0;
    }
}

int find(int i)
{
    if (i != father[i])
    {
        int tmp = father[i];
        father[i] = find(tmp);
        dist[i] += dist[tmp];
    }
    return father[i];
}

void unionSets(int l, int r, long long v)
{
    int lf = find(l), rf = find(r);
    if (lf != rf)
    {
        father[lf] = rf;
        dist[lf] = v + dist[r] - dist[l];
    }
}

long long query(int l, int r)
{
    if (find(l) != find(r))
    {
        return INF;
    }
    return dist[l] - dist[r];
}

int main()
{

    cin >> n >> m >> q;
    n++; // Adjust for 1-based indexing
    prepare();

    int l, r;
    long long v;
    for (int i = 1; i <= m; i++)
    {
        cin >> l >> r >> v;
        r++; // Adjust for 1-based indexing
        unionSets(l, r, v);
    }

    for (int i = 1; i <= q; i++)
    {
        cin >> l >> r;
        r++; // Adjust for 1-based indexing
        v = query(l, r);
        if (v == INF)
        {
            cout << "UNKNOWN\n";
        }
        else
        {
            cout << v << "\n";
        }
    }

    return 0;
}
