// 并查集的使用是如下的场景
// 1）一开始每个元素都拥有自己的集合，在自己的集合里只有这个元素自己
// 2）find(i)：查找i所在集合的代表元素，代表元素来代表i所在的集合
// 3）bool isSameSet(a, b)：判断a和b在不在一个集合里
// 4）void union(a, b)：a所在集合所有元素 与 b所在集合所有元素 合并成一个集合
// 5）各种操作单次调用的均摊时间复杂度为O(1)

// 并查集的两个优化，都发生在find方法里
// 1）扁平化（一定要做）
// 2）小挂大（可以不做，原论文中是秩的概念，可以理解为 粗略高度 或者 大小）

// 并查集的小扩展
// 可以定制信息：并查集目前有多少个集合，以及给每个集合打上标签信息

// 并查集时间复杂度的理解
// 作为如此简单、小巧的结构，
// 感性理解单次调用的均摊时间复杂度为O(1)即可，其实为α(n)，阿克曼函数。
// 当n=10^80次方即可探明宇宙原子量，α(n)的返回值也不超过6，那就可以认为是O(1)

// 并查集模版(牛客)
// 路径压缩 + 小挂大
// 测试链接 : https://www.nowcoder.com/practice/e7ed657974934a30b2010046536a5372

#include <cstdio>

const int MAXN = 1000001;
int father[MAXN];
int size[MAXN];
int stack[MAXN];
int n, m;

void build()
{
    for (int i = 0; i <= n; i++)
    {
        father[i] = i;
        size[i] = 1;
    }
}

// i号节点，往上一直找，找到合集根节点并返回！
int find(int i)
{
    // 沿途收集了几个点
    int top = 0;
    while (i != father[i])
    {
        stack[top++] = i;
        i = father[i];
    }
    // 沿途节点收集好了，i已经跳到代表节点了
    while (top > 0)
    {
        father[stack[--top]] = i;
    }
    return i;
}

bool isSameSet(int x, int y)
{
    return find(x) == find(y);
}

void unionSets(int x, int y)
{
    int fx = find(x);
    int fy = find(y);
    if (fx != fy)
    {
        // fx是集合的根节点
        // fy是集合的根节点
        // 小集合合并到大集合
        if (size[fx] >= size[fy])
        {
            size[fx] += size[fy];
            father[fy] = fx;
        }
        else
        {
            size[fy] += size[fx];
            father[fx] = fy;
        }
    }
}

int main()
{

    scanf("%d%d", &n, &m); // 输入节点数和操作数
    build();

    for (int i = 0; i < m; i++)
    {
        int op, x, y;
        scanf("%d%d%d", &op, &x, &y); // 输入操作类型和两个节点
        if (op == 1)
        {
            if (isSameSet(x, y))
            {
                printf("Yes\n");
            }
            else
            {
                printf("No\n");
            }
        }
        else
        {
            unionSets(x, y);
        }
    }

    return 0;
}
