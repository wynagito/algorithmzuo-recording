// 提根操作的代码 + 长链高度变化的实验
// 分别去生成一字型长链和之字型长链
// 每一种长链都让最下方节点提根上去
// 然后看看长链的高度变化
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;
using std::max;

const int MAXN = 100001;

// 整棵树的头节点编号
int head = 0;

// 分配了多少节点编号
int cnt = 0;

// key[i]    : 编号为i的节点的key
int key[MAXN];

// father[i] : 编号为i的节点的父节点编号
int father[MAXN];

// left[i]   : 编号为i的节点的左孩子编号
int left[MAXN];

// right[i]  : 编号为i的节点的右孩子编号
int right[MAXN];

// size[i]   : 以编号为i的节点做头的子树，一共有多少个节点
int size[MAXN];

// 更新节点 i 的子树大小
void up(int i)
{
    size[i] = size[left[i]] + size[right[i]] + 1;
}

// 判断编号为 i 的节点，是其父亲的什么儿子
// 0代表左儿子，1代表右儿子
int lr(int i)
{
    return right[father[i]] == i ? 1 : 0;
}

// 编号为 i 的节点上升一步，在结构上做调整
void rotate(int i)
{
    int f = father[i], g = father[f], soni = lr(i), sonf = lr(f);
    if (soni == 1)
    {
        right[f] = left[i];
        if (right[f] != 0)
        {
            father[right[f]] = f;
        }
        left[i] = f;
    }
    else
    {
        left[f] = right[i];
        if (left[f] != 0)
        {
            father[left[f]] = f;
        }
        right[i] = f;
    }
    if (g != 0)
    {
        if (sonf == 1)
        {
            right[g] = i;
        }
        else
        {
            left[g] = i;
        }
    }
    father[f] = i;
    father[i] = g;
    up(f);
    up(i);
}

// 编号为 i 的节点提根，变成编号为 goal 的节点的儿子
// 如果 goal == 0，表示把编号为 i 的节点变成整棵树的头
void splay(int i, int goal)
{
    int f = father[i], g = father[f];
    while (f != goal)
    {
        if (g != goal)
        {
            if (lr(i) == lr(f))
            {
                rotate(f);
            }
            else
            {
                rotate(i);
            }
        }
        rotate(i);
        f = father[i];
        g = father[f];
    }
    if (goal == 0)
    {
        head = i;
    }
}

// 构建一字型长链
int build1(int l, int r)
{
    int h = cnt + 1;
    for (int i = l, last = 0; i <= r; i++, last = cnt)
    {
        key[++cnt] = i;
        father[cnt] = last;
        left[cnt] = right[cnt] = 0;
        size[cnt] = r - i + 1;
        if (last != 0)
        {
            right[last] = cnt;
        }
    }
    return h;
}

// 构建之字形长链
int build2(int l, int r, int fa)
{
    if (l > r)
    {
        return 0;
    }
    key[++cnt] = l;
    father[cnt] = fa;
    left[cnt] = right[cnt] = 0;
    int h = cnt;
    if (l < r)
    {
        key[++cnt] = r;
        father[cnt] = h;
        left[cnt] = right[cnt] = 0;
        int c = cnt;
        right[h] = c;
        left[c] = build2(l + 1, r - 1, c);
        up(c);
    }
    up(h);
    return h;
}

// 返回以 i 为头的树的高度
int height(int i)
{
    if (i == 0)
    {
        return 0;
    }
    return max(height(left[i]), height(right[i])) + 1;
}

int main()
{
    cout << "构建一字型长链" << endl;
    cout << "最下方节点执行splay，观察高度变化" << endl;
    head = build1(1, 1000);
    cout << "splay之前的链长度 : " << height(head) << endl;
    splay(cnt, 0);
    cout << "splay之后的链长度 : " << height(head) << endl;

    cout << "==================" << endl;

    cout << "构建之字型长链" << endl;
    cout << "最下方节点执行splay，观察高度变化" << endl;
    head = build2(1, 1000, 0);
    cout << "splay之前的链长度 : " << height(head) << endl;
    splay(cnt, 0);
    cout << "splay之后的链长度 : " << height(head) << endl;

    return 0;
}
