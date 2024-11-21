// 倍杀测量者
// 如果 A的分数 >= B的分数 * k，k是正实数，就称 A k倍杀 B，或称 B被A k倍杀了
// 一场比赛中，一共有n个选手，有m1条誓言记录，有m2条选手得分记录，得分只可能是正实数
// 类型1的誓言 u v k : 选手u 没有k倍杀 选手v，那么选手u就穿女装
// 类型2的誓言 u v k : 选手u 被选手v k倍杀了，那么选手u就穿女装
// 选手的得分    u w : 选手u得了w分，如果某选手没有得分记录，按照尽量不穿女装的情况推测
// 你希望看到比赛后有人穿女装，但不想看到很多人穿女装，于是想制定正实数ans，效果如下
// 类型1的誓言，比例调整成(k-ans)，类型2的誓言，比例调整成(k+ans)，即提高了穿女装的条件
// 计算ans最大多少，依然有人穿女装，保留小数点后4位，如果不干预也没人穿女装，返回-1
// 1 <= n, m1, m2 <= 1000
// 1 <= k <= 10
// 1 <= w <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/P4926

#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <cstdio>

using namespace std;

const int MAXN = 1002;
const int MAXM = 3001;
const double INF = 1e10;
const double sml = 1e-6;

int n, m1, m2;
int vow[MAXN][4];   // 誓言记录(誓言类型, u, v, k)
int score[MAXN][2]; // 得分记录(u, w)

int head[MAXN]; // 链式前向星需要
int nxt[MAXM];
int to[MAXM];
double weight[MAXM];
int cnt;

double dist[MAXN]; // spfa需要
int update[MAXN];
const int MAXQ = 1000001;
int queue[MAXQ];
int h, t;
bool enter[MAXN];

void prepare();
void addEdge(int u, int v, double w);
bool check(double limit);
bool spfa(int s);
double compute();

void prepare()
{
    cnt = 1;
    h = t = 0;
    fill(head, head + n + 2, 0);
    fill(dist, dist + n + 2, INF);
    fill(update, update + n + 2, 0);
    fill(enter, enter + n + 2, false);
}

void addEdge(int u, int v, double w)
{
    nxt[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

bool check(double limit)
{
    prepare();
    for (int i = 1; i <= n; i++)
    {
        addEdge(0, i, 0);
    }
    for (int i = 1; i <= m1; i++)
    {
        if (vow[i][0] == 1)
        {
            addEdge(vow[i][1], vow[i][2], -log(-limit + vow[i][3]));
        }
        else
        {
            addEdge(vow[i][1], vow[i][2], log(limit + vow[i][3] - sml));
        }
    }
    for (int i = 1; i <= m2; i++)
    {
        addEdge(n + 1, score[i][0], log(score[i][1]));
        addEdge(score[i][0], n + 1, -log(score[i][1]));
    }
    return spfa(0);
}

bool spfa(int s)
{
    dist[s] = 0;
    update[s] = 1;
    queue[t++] = s;
    enter[s] = true;

    while (h < t)
    {
        int u = queue[h++];
        enter[u] = false;

        for (int ei = head[u]; ei > 0; ei = nxt[ei])
        {
            int v = to[ei];
            double w = weight[ei];
            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                if (!enter[v])
                {
                    if (++update[v] > n + 1)
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

double compute()
{
    double l = 0, r = INF, m, ans = 0;
    while (r - l >= sml)
    {
        m = (l + r) / 2;
        if (check(m))
        {
            ans = m;
            l = m + sml;
        }
        else
        {
            r = m - sml;
        }
    }
    return ans;
}

int main()
{
    cin >> n >> m1 >> m2;
    for (int i = 1; i <= m1; i++)
    {
        cin >> vow[i][0] >> vow[i][1] >> vow[i][2] >> vow[i][3];
    }
    for (int i = 1; i <= m2; i++)
    {
        cin >> score[i][0] >> score[i][1];
    }

    double ans = compute();
    if (ans == 0)
    {
        cout << "-1" << endl;
    }
    else
    {
        cout << ans << endl;
    }

    return 0;
}