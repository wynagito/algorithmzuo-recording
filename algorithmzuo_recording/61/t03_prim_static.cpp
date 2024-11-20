// Prim算法优化（洛谷）
// 静态空间实现
// 时间复杂度O(n + m) + O((m+n) * log n)
// 测试链接 : https://www.luogu.com.cn/problem/P3366

#include <iostream>

// 建图用链式前向星
// 堆也是用数组结构手写的、且只和节点个数有关
const int MAXN = 5001;
const int MAXM = 400001;

int n, m;
// 链式前向星建图
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt;

// 改写的堆结构
int heap[MAXN][2];
// where[v] = -1，表示v这个节点，从来没有进入过堆
// where[v] = -2，表示v这个节点，已经弹出过了
// where[v] = i(>=0)，表示v这个节点，在堆上的i位置
int where[MAXN];
int heapSize;
int nodeCnt;

void build();
void addEdge(int u, int v, int w);
void heapInsert(int i);
void addOrUpdateOrIgnore(int ei);
void pop();
void heapify(int i);
bool isEmpty();
int prim();

void build()
{
    cnt = 1;
    heapSize = 0;
    std ::fill(head + 1, head + n + 1, 0);
    std ::fill(where + 1, where + n + 1, -1);
}

// 堆上，i位置的信息 和 j位置的信息 交换！
void swap(int i, int j)
{
    int a = heap[i][0];
    int b = heap[j][0];
    where[a] = j;
    where[b] = i;
    int tmp1 = heap[i][0];
    heap[i][0] = heap[j][0];
    heap[j][0] = tmp1;
    int tmp2 = heap[i][1];
    heap[i][1] = heap[j][1];
    heap[j][1] = tmp2;
}

void addEdge(int u, int v, int w)
{
    nxt[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

void heapInsert(int i)
{
    while (heap[i][1] < heap[(i - 1) / 2][1])
    {
        swap(i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

// 当前处理的是编号为ei的边！
void addOrUpdateOrIgnore(int ei)
{
    int v = to[ei];
    int w = weight[ei];
    // 去往v点，权重w
    if (where[v] == -1)
    {
        // v这个点，从来没有进入过堆！
        heap[heapSize][0] = v;
        heap[heapSize][1] = w;
        where[v] = heapSize++;
        heapInsert(where[v]);
    }
    else if (where[v] >= 0)
    {
        // v这个点的记录，在堆上的位置是where[v]
        heap[where[v]][1] = std::min(heap[where[v]][1], w);
        heapInsert(where[v]);
    }
}

int u;
int w;

// 堆顶的记录：节点 -> u、到节点的花费 -> w
void pop()
{
    u = heap[0][0];
    w = heap[0][1];
    swap(0, --heapSize);
    heapify(0);
    where[u] = -2;
    nodeCnt++;
}

void heapify(int i)
{
    int l = i * 2 + 1;
    while (l < heapSize)
    {
        int best = l + 1 < heapSize && heap[l + 1][1] < heap[l][1] ? l + 1 : l;
        best = heap[best][1] < heap[i][1] ? best : i;
        if (best == i)
        {
            break;
        }
        swap(best, i);
        i = best;
        l = i * 2 + 1;
    }
}

bool isEmpty()
{
    return heapSize == 0;
}

int prim()
{
    nodeCnt = 1;
    where[1] = -2;
    for (int ei = head[1]; ei > 0; ei = nxt[ei])
    {
        addOrUpdateOrIgnore(ei);
    }
    int ans = 0;
    while (!isEmpty())
    {
        pop();
        ans += w;
        for (int ei = head[u]; ei > 0; ei = nxt[ei])
        {
            addOrUpdateOrIgnore(ei);
        }
    }
    return ans;
}

int main()
{
    while (std::cin >> n >> m)
    {
        build();
        for (int i = 0, u, v, w; i < m; i++)
        {
            std::cin >> u >> v >> w;
            addEdge(u, v, w);
            addEdge(v, u, w);
        }
        int ans = prim();
        if (nodeCnt == n)
        {
            std::cout << ans << "\n";
        }
        else
        {
            std::cout << "orz\n";
        }
    }
    return 0;
}