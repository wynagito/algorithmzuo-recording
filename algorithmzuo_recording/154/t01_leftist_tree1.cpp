// 左偏树是一种可并堆结构，支持堆的合并，两个堆的合并过程，时间复杂度O(log n)

// 可并堆结构还有，配对堆、斜堆、二项堆、斐波那契堆等等
// 左偏树因为方便进行可持久化，所以只学习左偏树即可，下节课会讲述可持久化左偏树

// 左偏树表示的堆结构，不是完全二叉树，而是广义的堆结构，平衡性由dist值来维护
// 节点的dist值表示，离开该节点后，至少经过几个节点能到达空，dist[0] = -1
// 合并后如果发现，左儿子dist值 < 右儿子dist值，就交换左右树
// 左偏树的每个节点满足，左儿子dist值 >= 右儿子dist值，节点dist值 = 右儿子dist值 + 1

// 左偏树的平衡性，只是方便了合并的过程，树上依然可能出现很长的链，所以查询快需要结合并查集

// 左偏树结构，合并操作非常方便，但是树上依然可能出现很长的链
// 任何节点找堆顶的过程，不能依赖左偏树的结构，所以建立并查集

// 利用并查集压缩路径的特点，任何节点找堆顶的过程就得到了加速
// 需要保证，并查集最上方的代表节点 = 左偏树的头也就是堆顶

// 左偏树删除堆顶节点
// 1，堆顶节点的左右树合并，形成新树
// 2，堆顶节点的left、right、dist信息清空
// 3，堆顶节点的father指向新树的头，很重要！课上会重点解释

// 左偏树模版题1
// 依次给定n个非负数字，表示有n个小根堆，每个堆只有一个数
// 实现如下两种操作，操作一共调用m次
// 1 x y : 第x个数字所在的堆和第y个数字所在的堆合并
//         如果两个数字已经在一个堆或者某个数字已经删除，不进行合并
// 2 x   : 打印第x个数字所在堆的最小值，并且在堆里删掉这个最小值
//         如果第x个数字已经被删除，也就是找不到所在的堆，打印-1
//         若有多个最小值，优先删除编号小的
// 1 <= n, m <= 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P3377

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100001;
int n, m;
int num[MAXN];
int ls[MAXN];
int rs[MAXN];
int dist[MAXN];
int fa[MAXN];

void prepare()
{
    dist[0] = -1;
    for (int i = 1; i <= n; i++)
    {
        ls[i] = rs[i] = dist[i] = 0;
        fa[i] = i;
    }
}

int find(int i)
{
    fa[i] = fa[i] == i ? i : find(fa[i]);
    return fa[i];
}

int merge(int i, int j)
{
    if (i == 0 || j == 0)
    {
        return i + j;
    }
    if (num[i] > num[j] || (num[i] == num[j] && i > j))
    {
        int tmp = i;
        i = j;
        j = tmp;
    }
    rs[i] = merge(rs[i], j);
    if (dist[ls[i]] < dist[rs[i]])
    {
        int tmp = ls[i];
        ls[i] = rs[i];
        rs[i] = tmp;
    }
    dist[i] = dist[rs[i]] + 1;
    fa[ls[i]] = fa[rs[i]] = i;
    return i;
}

int pop(int i)
{
    fa[ls[i]] = ls[i];
    fa[rs[i]] = rs[i];
    fa[i] = merge(ls[i], rs[i]);
    ls[i] = rs[i] = dist[i] = 0;
    return fa[i];
}

int main()
{
    cin >> n >> m;
    prepare();
    for (int i = 1; i <= n; i++)
    {
        cin >> num[i];
    }
    for (int i = 1; i <= m; i++)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int x, y;
            cin >> x >> y;
            if (num[x] != -1 && num[y] != -1)
            {
                int l = find(x);
                int r = find(y);
                if (l != r)
                {
                    merge(l, r);
                }
            }
        }
        else
        {
            int x;
            cin >> x;
            if (num[x] == -1)
            {
                cout << -1 << "\n";
            }
            else
            {
                int ans = find(x);
                cout << num[ans] << "\n";
                pop(ans);
                num[ans] = -1;
            }
        }
    }
    return 0;
}