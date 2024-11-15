// 建图的三种方式
// 1，邻接矩阵（适合点的数量不多的图）
// 2，邻接表（最常用的方式）
// 3，链式前向星（空间要求严苛情况下使用。比赛必用，大厂笔试、面试不常用）

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

// 点的最大数量
const int MAXN = 11;

// 边的最大数量
// 只有链式前向星方式建图需要这个数量
// 注意如果无向图的最大数量是m条边，数量要准备m*2
// 因为一条无向边要加两条有向边
const int MAXM = 21;

// 邻接矩阵方式建图
int graph1[MAXN][MAXN];

// 邻接表方式建图
vector<vector<pair<int, int>>> graph2;

// 链式前向星方式建图
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
// 如果边有权重，那么需要这个数组
int weight[MAXM];
int cnt;

void build(int n)
{
    // 邻接矩阵清空
    memset(graph1, 0, sizeof(graph1));

    // 邻接表清空和准备
    graph2.resize(n + 1);
    for (auto &v : graph2)
    {
        v.clear();
    }

    // 链式前向星清空
    cnt = 1;
    memset(head, 0, sizeof(head));
}

// 链式前向星加边
void addEdge(int u, int v, int w)
{
    // u -> v , 边权重是w
    nxt[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

// 三种方式建立有向图带权图
void directGraph(int edges[][3], int edgeCount)
{
    // 邻接矩阵建图
    for (int i = 0; i < edgeCount; i++)
    {
        graph1[edges[i][0]][edges[i][1]] = edges[i][2];
    }

    // 邻接表建图
    for (int i = 0; i < edgeCount; i++)
    {
        graph2[edges[i][0]].push_back({edges[i][1], edges[i][2]});
    }

    // 链式前向星建图
    for (int i = 0; i < edgeCount; i++)
    {
        addEdge(edges[i][0], edges[i][1], edges[i][2]);
    }
}

// 三种方式建立无向图带权图
void undirectGraph(int edges[][3], int edgeCount)
{
    // 邻接矩阵建图
    for (int i = 0; i < edgeCount; i++)
    {
        graph1[edges[i][0]][edges[i][1]] = edges[i][2];
        graph1[edges[i][1]][edges[i][0]] = edges[i][2];
    }

    // 邻接表建图
    for (int i = 0; i < edgeCount; i++)
    {
        graph2[edges[i][0]].push_back({edges[i][1], edges[i][2]});
        graph2[edges[i][1]].push_back({edges[i][0], edges[i][2]});
    }

    // 链式前向星建图
    for (int i = 0; i < edgeCount; i++)
    {
        addEdge(edges[i][0], edges[i][1], edges[i][2]);
        addEdge(edges[i][1], edges[i][0], edges[i][2]);
    }
}

void traversal(int n)
{
    cout << "邻接矩阵遍历 :" << endl;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << graph1[i][j] << " ";
        }
        cout << endl;
    }

    cout << "邻接表遍历 :" << endl;
    for (int i = 1; i <= n; i++)
    {
        cout << i << "(邻居、边权) : ";
        for (auto edge : graph2[i])
        {
            cout << "(" << edge.first << "," << edge.second << ") ";
        }
        cout << endl;
    }

    cout << "链式前向星 :" << endl;
    for (int i = 1; i <= n; i++)
    {
        cout << i << "(邻居、边权) : ";
        for (int ei = head[i]; ei > 0; ei = nxt[ei])
        {
            cout << "(" << to[ei] << "," << weight[ei] << ") ";
        }
        cout << endl;
    }
}

int main()
{
    // 理解了带权图的建立过程，也就理解了不带权图
    // 点的编号为1...n
    // 例子1自己画一下图，有向带权图，然后打印结果
    int n1 = 4;
    int edges1[6][3] = {{1, 3, 6}, {4, 3, 4}, {2, 4, 2}, {1, 2, 7}, {2, 3, 5}, {3, 1, 1}};
    build(n1);
    directGraph(edges1, 6);
    traversal(n1);
    cout << "======================" << endl;

    // 例子2自己画一下图，无向带权图，然后打印结果
    int n2 = 5;
    int edges2[7][3] = {{3, 5, 4}, {4, 1, 1}, {3, 4, 2}, {5, 2, 4}, {2, 3, 7}, {1, 5, 5}, {4, 2, 6}};
    build(n2);
    undirectGraph(edges2, 7);
    traversal(n2);

    return 0;
}
