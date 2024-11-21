// 小k的农场
// 一共有n个农场，编号1~n，给定m条关系，每条关系是如下三种形式中的一种
// 关系1 a b c : 表示农场a比农场b至少多种植了c个作物
// 关系2 a b c : 表示农场a比农场b至多多种植了c个作物
// 关系3 a b   : 表示农场a和农场b种植了一样多的作物
// 如果关系之间能推出矛盾，打印"No"，不存在矛盾，打印"Yes"
// 1 <= n、m <= 5 * 10^3
// 1 <= c <= 5 * 10^3
// 测试链接 : https://www.luogu.com.cn/problem/P1993

#include <iostream>
#include <limits.h>
#include <cstring>

using namespace std;

const int MAXN = 5001;
const int MAXM = 20001;
const int MAXQ = 20000001;

int head[MAXN], nxt[MAXM], to[MAXM], weight[MAXM];
int cnt;

int dist[MAXN];
int update[MAXN];
int queue[MAXQ];
bool enter[MAXN];
int n, m;

void prepare()
{
    cnt = 1;
    memset(head, 0, sizeof(head));
    memset(dist, 0, sizeof(dist));
    memset(update, 0, sizeof(update));
    memset(enter, false, sizeof(enter));
    fill(dist, dist + n + 1, INT_MAX);
}

void addEdge(int u, int v, int w)
{
    nxt[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

bool spfa(int s)
{
    dist[s] = 0;
    update[s] = 1;
    int h = 0, t = 0;
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
                        return true;
                    }
                    queue[t++] = v;
                    enter[v] = true;
                }
            }
        }
    }
    return false;
}

int main()
{

    cin >> n >> m;
    prepare();

    for (int i = 1; i <= n; i++)
    {
        addEdge(0, i, 0);
    }

    for (int i = 1, type, u, v, w; i <= m; i++)
    {
        cin >> type >> u >> v;
        if (type == 1)
        {
            cin >> w;
            addEdge(u, v, -w);
        }
        else if (type == 2)
        {
            cin >> w;
            addEdge(v, u, w);
        }
        else
        {
            addEdge(u, v, 0);
            addEdge(v, u, 0);
        }
    }

    if (spfa(0))
    {
        cout << "No" << endl;
    }
    else
    {
        cout << "Yes" << endl;
    }

    return 0;
}