// 并查集模版(洛谷)
// 本实现用递归函数实现路径压缩，而且省掉了小挂大的优化，一般情况下可以省略
// 测试链接 : https://www.luogu.com.cn/problem/P3367
#include <cstdio>

using namespace std;

const int MAXN = 10001;
int father[MAXN];
int n, m;

void build()
{
    for (int i = 0; i <= n; i++)
    {
        father[i] = i;
    }
}

int find(int i)
{
    if (i != father[i])
    {
        father[i] = find(father[i]);
    }
    return father[i];
}

bool isSameSet(int x, int y)
{
    return find(x) == find(y);
}

void unionSets(int x, int y)
{
    father[find(x)] = find(y);
}

int main()
{
    scanf("%d%d", &n, &m);
    build();
    for (int i = 0; i < m; i++)
    {
        int z, x, y;
        scanf("%d%d%d", &z, &x, &y); // 读取z、x、y
        if (z == 1)
        {
            unionSets(x, y);
        }
        else
        {
            if (isSameSet(x, y))
            {
                printf("Y\n");
            }
            else
            {
                printf("N\n");
            }
        }
    }

    return 0;
}
