// 布局奶牛
// 编号1到编号n的奶牛从左往右站成一排，你可以决定任意相邻奶牛之间的距离
// 有m1条好友信息，有m2条情敌信息，好友间希望距离更近，情敌间希望距离更远
// 每条好友信息为 : u v w，表示希望u和v之间的距离 <= w，输入保证u < v
// 每条情敌信息为 : u v w，表示希望u和v之间的距离 >= w，输入保证u < v
// 你需要安排奶牛的布局，满足所有的好友信息和情敌信息
// 如果不存在合法方案，返回-1
// 如果存在合法方案，返回1号奶牛和n号奶牛之间的最大距离
// 如果存在合法方案，并且1号奶牛和n号奶牛之间的距离可以无穷远，返回-2
// 测试链接 : https://www.luogu.com.cn/problem/P4878

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cstring>

using namespace std;

const int MAXN = 1001;
const int MAXM = 20001;
const int MAXQ = 1000001;

vector<int> head(MAXN, 0);
vector<int> nxt(MAXM, 0);
vector<int> to(MAXM, 0);
vector<int> weight(MAXM, 0);
int cnt;

vector<int> dist(MAXN, 0);
vector<int> update(MAXN, 0);
vector<bool> enter(MAXN, false);
int n, m1, m2;

void prepare()
{
    cnt = 1;
    fill(head.begin(), head.end(), 0);
}

void addEdge(int u, int v, int w)
{
    nxt[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

int spfa(int s)
{
    int h = 0, t = 0;
    fill(dist.begin(), dist.begin() + n + 1, numeric_limits<int>::max());
    fill(update.begin(), update.begin() + n + 1, 0);
    fill(enter.begin(), enter.begin() + n + 1, false);

    dist[s] = 0;
    update[s] = 1;

    vector<int> queue(MAXQ);
    queue[t++] = s;
    enter[s] = true;

    while (h < t)
    {
        int u = queue[h++];
        enter[u] = false;
        for (int ei = head[u]; ei > 0; ei = nxt[ei])
        {
            int v = to[ei];
            int w = weight[ei];
            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                if (!enter[v])
                {
                    if (++update[v] > n)
                    {
                        return -1;
                    }
                    queue[t++] = v;
                    enter[v] = true;
                }
            }
        }
    }

    if (dist[n] == numeric_limits<int>::max())
    {
        return -2;
    }
    return dist[n];
}

int main()
{

    cin >> n >> m1 >> m2;
    prepare();

    // 0号点是连通超级源点，保证图的连通性
    for (int i = 1; i <= n; i++)
    {
        addEdge(0, i, 0);
    }
    // 好友关系连边
    for (int i = 1, u, v, w; i <= m1; i++)
    {
        cin >> u >> v >> w;
        addEdge(u, v, w);
    }
    // 情敌关系连边
    for (int i = 1, u, v, w; i <= m2; i++)
    {
        cin >> u >> v >> w;
        addEdge(v, u, -w);
    }
    // 根据本题的模型，一定要增加如下的边，不然会出错
    for (int i = 1; i < n; i++)
    {
        addEdge(i + 1, i, 0);
    }

    int ans = spfa(0);
    if (ans == -1)
    {
        cout << ans << endl;
    }
    else
    {
        ans = spfa(1);
        cout << ans << endl;
    }

    return 0;
}
