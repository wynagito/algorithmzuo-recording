// AVL树是理解平衡树的起点结构，也是最经典的平衡搜索二叉树
// 平衡性：任意子树上，左树高度和右树高度，相差不超过1
// 单次增、删、改、查，时间复杂度都为O(log n)

// AVL树的核心是理解以下内容：
// 1，静态数组实现AVL树，空间的使用方式
// 2，处理不同查询，有时需要多维护一些数据，value信息、词频计数信息、子树的数字总数信息等等
// 3，左旋和右旋操作
// 4，四种违规情况：LL型、LR型、RL型、RR型，每种违规情况对应的调整
// 5，增加节点的过程
// 6，删除节点的过程，其中替换节点的过程是重点

// 注意点：
// 删除某个节点后，可能LL型、LR型同时出现，按照LL型调整；可能RR型、RL型同时出现，按照RR型调整
// 增加或者删除节点之后，从被影响的位置开始，往上每个节点都检查，是否有违规情况
// 即便每步都调整，时间复杂度也就是O(log n)，其实真实发生的调整次数极少，复杂度就是走过树高而已

// AVL树的实现
// 实现一种结构，支持如下操作，要求单次调用的时间复杂度O(log n)
// 1，增加x，重复加入算多个词频
// 2，删除x，如果有多个，只删掉一个
// 3，查询x的排名，x的排名为，比x小的数的个数+1
// 4，查询数据中排名为x的数
// 5，查询x的前驱，x的前驱为，小于x的数中最大的数，不存在返回整数最小值
// 6，查询x的后继，x的后继为，大于x的数中最小的数，不存在返回整数最大值
// 所有操作的次数 <= 10^5
// -10^7 <= x <= +10^7
// 测试链接 : https://www.luogu.com.cn/problem/P3369

#include <iostream>
#include <algorithm>
#include <climits>
#include <cstring>

using namespace std;

const int MAXN = 100001;

// 空间使用计数
int cnt = 0;
// 整棵树的头节点编号
int head = 0;
// 节点的key
int key[MAXN];
// 子树高度
int height[MAXN];
// 左孩子
int ls[MAXN];
// 右孩子
int rs[MAXN];
// 节点key的计数
int key_count[MAXN];
// 子树的数字总数
int size[MAXN];

// 修正信息
void up(int i)
{
    size[i] = size[ls[i]] + size[rs[i]] + key_count[i];
    height[i] = max(height[ls[i]], height[rs[i]]) + 1;
}

// i节点为头的树左旋，返回左旋后头节点的空间编号
int leftRotate(int i)
{
    int r = rs[i];
    rs[i] = ls[r];
    ls[r] = i;
    up(i);
    up(r);
    return r;
}

// i节点为头的树右旋，返回右旋后头节点的空间编号
int rightRotate(int i)
{
    int l = ls[i];
    ls[i] = rs[l];
    rs[l] = i;
    up(i);
    up(l);
    return l;
}

// 检查i节点为头的树是否违规
// 如果命中了某种违规情况，就进行相应调整
// 返回树的头节点的空间编号
int maintain(int i)
{
    int lh = height[ls[i]];
    int rh = height[rs[i]];
    if (lh - rh > 1)
    {
        // LL型违规
        if (height[ls[ls[i]]] >= height[rs[ls[i]]])
        {
            i = rightRotate(i);
        }
        else // LR型违规
        {
            ls[i] = leftRotate(ls[i]);
            i = rightRotate(i);
        }
    }
    else if (rh - lh > 1)
    {
        // RR型违规
        if (height[rs[rs[i]]] >= height[ls[rs[i]]])
        {
            i = leftRotate(i);
        }
        else // RL型违规
        {
            rs[i] = rightRotate(rs[i]);
            i = leftRotate(i);
        }
    }
    return i;
}

// 当前来到i号节点，num这个数字一定会加入以i为头的树
// 树结构有可能变化，返回头节点编号
int add(int i, int num)
{
    if (i == 0)
    {
        key[++cnt] = num;
        key_count[cnt] = size[cnt] = height[cnt] = 1;
        return cnt;
    }
    if (key[i] == num)
    {
        key_count[i]++;
    }
    else if (key[i] > num)
    {
        ls[i] = add(ls[i], num);
    }
    else
    {
        rs[i] = add(rs[i], num);
    }
    up(i);
    return maintain(i);
}

// 增加数字num，重复加入算多个词频
void add(int num)
{
    head = add(head, num);
}

int getRank(int i, int num)
{
    if (i == 0)
    {
        return 0;
    }
    if (key[i] >= num)
    {
        return getRank(ls[i], num);
    }
    else
    {
        return size[ls[i]] + key_count[i] + getRank(rs[i], num);
    }
}

int getRank(int num)
{
    return getRank(head, num) + 1;
}

// 以i号节点为头的树上，最左节点的编号一定是mostLeft
// 删掉这个节点，并保证树的平衡性，返回头节点的编号
int removeMostLeft(int i, int mostLeft)
{
    if (i == mostLeft)
    {
        return rs[i];
    }
    else
    {
        ls[i] = removeMostLeft(ls[i], mostLeft);
        up(i);
        return maintain(i);
    }
}

// 当前来到i号节点，以i为头的树一定会减少1个num
// 树结构有可能变化，返回头节点编号
int remove(int i, int num)
{
    if (key[i] < num)
    {
        rs[i] = remove(rs[i], num);
    }
    else if (key[i] > num)
    {
        ls[i] = remove(ls[i], num);
    }
    else
    {
        if (key_count[i] > 1)
        {
            key_count[i]--;
        }
        else
        {
            if (ls[i] == 0 && rs[i] == 0)
            {
                return 0;
            }
            else if (ls[i] != 0 && rs[i] == 0)
            {
                i = ls[i];
            }
            else if (ls[i] == 0 && rs[i] != 0)
            {
                i = rs[i];
            }
            else
            {
                int mostLeft = rs[i];
                while (ls[mostLeft] != 0)
                {
                    mostLeft = ls[mostLeft];
                }
                rs[i] = removeMostLeft(rs[i], mostLeft);
                ls[mostLeft] = ls[i];
                rs[mostLeft] = rs[i];
                i = mostLeft;
            }
        }
    }
    up(i);
    return maintain(i);
}

// 删除数字num，如果有多个，只删掉一个
void remove(int num)
{
    if (getRank(num) != getRank(num + 1))
    {
        head = remove(head, num);
    }
}

int getIndex(int i, int x)
{
    if (size[ls[i]] >= x)
    {
        return getIndex(ls[i], x);
    }
    else if (size[ls[i]] + key_count[i] < x)
    {
        return getIndex(rs[i], x - size[ls[i]] - key_count[i]);
    }
    return key[i];
}

int getIndex(int x)
{
    return getIndex(head, x);
}

int pre(int i, int num)
{
    if (i == 0)
    {
        return INT_MIN;
    }
    if (key[i] >= num)
    {
        return pre(ls[i], num);
    }
    else
    {
        return max(key[i], pre(rs[i], num));
    }
}

int pre(int num)
{
    return pre(head, num);
}

int post(int i, int num)
{
    if (i == 0)
    {
        return INT_MAX;
    }
    if (key[i] <= num)
    {
        return post(rs[i], num);
    }
    else
    {
        return min(key[i], post(ls[i], num));
    }
}

int post(int num)
{
    return post(head, num);
}

void clear()
{
    memset(key + 1, 0, cnt * sizeof(int));
    memset(height + 1, 0, cnt * sizeof(int));
    memset(ls + 1, 0, cnt * sizeof(int));
    memset(rs + 1, 0, cnt * sizeof(int));
    memset(key_count + 1, 0, cnt * sizeof(int));
    memset(size + 1, 0, cnt * sizeof(int));
    cnt = 0;
    head = 0;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 1, op, x; i <= n; i++)
    {
        cin >> op >> x;
        if (op == 1)
        {
            add(x);
        }
        else if (op == 2)
        {
            remove(x);
        }
        else if (op == 3)
        {
            cout << getRank(x) << endl;
        }
        else if (op == 4)
        {
            cout << getIndex(x) << endl;
        }
        else if (op == 5)
        {
            cout << pre(x) << endl;
        }
        else
        {
            cout << post(x) << endl;
        }
    }
    clear();
    return 0;
}