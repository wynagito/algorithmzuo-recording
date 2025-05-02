// 错误答案数量，带权并查集模版题3
// 有n个数字，下标1 ~ n，但是并不知道每个数字是多少
// 操作 l r v，代表l~r范围上累加和为v
// 一共m个操作，如果某个操作和之前的操作信息自相矛盾，认为当前操作是错误的，不进行这个操作
// 最后打印错误操作的数量
// 1 <= n <= 200000    1 <= m <= 40000
// 累加和不会超过int类型范围
// 测试链接 : https://acm.hdu.edu.cn/showproblem.php?pid=3038
// 测试链接 : https://vjudge.net/problem/HDU-3038

#include <iostream>

using namespace std;

const int MAXN = 200002;

int n, m, ans;

int father[MAXN], dist[MAXN];

void prepare()
{
    ans = 0;
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

void unionSets(int l, int r, int v)
{
    int lf = find(l), rf = find(r);
    if (lf != rf)
    {
        father[lf] = rf;
        dist[lf] = v + dist[r] - dist[l];
    }
}

bool check(int l, int r, int v)
{
    if (find(l) == find(r))
    {
        if ((dist[l] - dist[r]) != v)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    cin >> n >> m;
    prepare();
    for (int i = 1, l, r, v; i <= m; i++)
    {
        cin >> l >> r >> v;
        r++;
        if (!check(l, r, v))
        {
            ans++;
        }
        else
        {
            unionSets(l, r, v);
        }
    }
    cout << ans << endl;
    return 0;
}
