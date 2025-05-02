// 银河英雄传说
// 一共有30000搜战舰，编号1~30000，一开始每艘战舰各自成一队
// 如果若干战舰变成一队，那么队伍里的所有战舰竖直地排成一列
// 实现如下两种操作，操作一共调用t次
// M l r : 合并l号战舰所在队伍和r号战舰所在队伍
//         l号战舰的队伍，整体移动到，r号战舰所在队伍的最末尾战舰的后面
//         如果l号战舰和r号战舰已经是一队，不进行任何操作
// C l r : 如果l号战舰和r号战舰不在一个队伍，打印-1
//         如果l号战舰和r号战舰在一个队伍，打印它俩中间隔着几艘战舰
// 1 <= t <= 5 * 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P1196

#include <iostream>

using namespace std;

const int MAXN = 30001;

int n = 30000;

int father[MAXN];
int dist[MAXN];
int size[MAXN];

void prepare()
{
    for (int i = 1; i <= n; i++)
    {
        father[i] = i;
        dist[i] = 0;
        size[i] = 1;
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

void unionSets(int l, int r)
{
    int lf = find(l), rf = find(r);
    if (lf != rf)
    {
        father[lf] = rf;
        dist[lf] += size[rf];
        size[rf] += size[lf];
    }
}

int query(int l, int r)
{
    if (find(l) != find(r))
    {
        return -1;
    }
    return abs(dist[l] - dist[r]) - 1;
}

int main()
{
    int t, l, r;
    char c;
    cin >> t;
    prepare();
    while (t--)
    {
        cin >> c >> l >> r;
        if (c == 'M')
        {
            unionSets(l, r);
        }
        else if (c == 'C')
        {
            cout << query(l, r) << endl;
        }
    }
    return 0;
}
