// 同余最短路
// 给定n个正数，每种数的个数无限
// 求这n个正数能拼凑出多少的其他数
// 或者不能拼凑出的最小数、最大数等问题时
// 利用同余最短路构造一些同余状态，可以起到优化时间和空间的目的

// 两次转圈法实现同余最短路

// 给定一个基准数x，那么可能的余数为0..x-1
// 假设当前余数是cur，当前出现数字为y，(cur + y) % x 所出现的新余数，最终会回到cur
// 当前出现数字为y，0..x-1这些点，会形成gcd(x,y)个子环，所有子环的起点为：0 ~ gcd(x,y)-1

// 每个子环为单位，进行同余最短路的更新，所有子环的所有点的数量 = x，即更新一轮的代价O(x)
// 因为是最短路，所以每出现一个新的数字y，所形成的每个子环，只需要转一圈即可完成更新
// 特别注意：子环的起点不一定是点权最小的点，所以实现中，往往用转两圈的方式

// 如果一共有n个数字，基准数为x，那么同余最短路的更新代价为，O(n * x)
// spfa算法也可以实现同余最短路的更新，但是比赛中经常设计数据，让其时间复杂度高于O(n * x)
// 为了顺利通过，所以更推荐两次绕圈法

// 跳楼机
// 一座大楼一共有h层，楼层编号1~h，有如下四种移动方式
// 1, 向上移动x层
// 2, 向上移动y层
// 3, 向上移动z层
// 4, 回到1层
// 假设你正在第1层，请问大楼里有多少楼层你可以到达
// 1 <= h <= 2^63 - 1
// 1 <= x、y、z <= 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P3403

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>

using namespace std;

const int MAXN = 100001;
const int MAXM = 200001;

long long h;
int x, y, z;

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
long long weight[MAXM];
int cnt;

// dijkstra算法需要
// 0 : 当前节点
// 1 : 源点到当前点距离
priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> heap;

long long dist[MAXN];
bool visited[MAXN];

void prepare()
{
    cnt = 1;
    while (!heap.empty())
    {
        heap.pop();
    }
    memset(head, 0, sizeof(head));
    fill(dist, dist + x, LLONG_MAX);
    fill(visited, visited + x, false);
}

void addEdge(int u, int v, long long w)
{
    nxt[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

// 来自讲解064，dijkstra算法
void dijkstra()
{
    heap.push({0, 0}); // 存入 {距离, 节点}
    dist[0] = 0;
    while (!heap.empty())
    {
        auto cur = heap.top();
        heap.pop();
        int u = cur.second;
        long long w = cur.first;
        if (visited[u])
        {
            continue;
        }
        visited[u] = true;
        for (int ei = head[u], v; ei > 0; ei = nxt[ei])
        {
            v = to[ei];
            if (!visited[v] && dist[v] > w + weight[ei])
            {
                dist[v] = w + weight[ei];
                heap.push({dist[v], v});
            }
        }
    }
}

long long compute()
{
    dijkstra();
    long long ans = 0;
    for (int i = 0; i < x; i++)
    {
        if (dist[i] <= h)
        {
            ans += (h - dist[i]) / x + 1;
        }
    }
    return ans;
}

int main()
{
    cin >> h;
    h--;
    cin >> x >> y >> z;
    prepare();
    for (int i = 0; i < x; i++)
    {
        addEdge(i, (i + y) % x, y);
        addEdge(i, (i + z) % x, z);
    }
    cout << compute() << endl;
    return 0;
}