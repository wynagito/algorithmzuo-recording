// 跳表的节点结构，类似链表节点结构，但可能包含多层指针
// 每个节点能拥有多少层指针，类似骰子扔大小，扔出小就增加层数，一旦扔出大就确定层数，总层数有限制

// 跳表的理解核心
// 1，跳表建立、查询、删除大概过程
// 2，查询num排名多少、查询排名为x的key是什么，需要维护每个指针的长度，最底层跨越数字的个数
// 3，静态数组实现跳表的空间使用方式
// 4，增加节点的过程和代码详解
// 5，删除节点的过程和代码详解
// 6，常见查询的过程和代码详解

// 跳表利用随机化规避倾斜数据，组织结构类似平衡树，增、删、改、查，时间复杂度为O(log n)

// 跳表的实现
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
#include <vector>
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <cstring>

using namespace std;

// 跳表最大层的限制
const int MAXL = 20;
const int MAXN = 100001;

// 空间使用计数
int cnt;
// 节点的key
int key[MAXN];
int key_count[MAXN];
// 节点拥有多少层指针
int level[MAXN];
// 节点每一层指针指向哪个节点
int next_node[MAXN][MAXL + 1];
// 节点每一层指针的长度(底层跨过多少数，左开右闭)
int len[MAXN][MAXL + 1];

// 建立跳表
void build()
{
    cnt = 1;
    key[cnt] = INT_MIN;
    level[cnt] = MAXL;
}

// 使用多少空间一律清空
void clear()
{
    memset(key + 1, 0, cnt * sizeof(int));
    memset(key_count + 1, 0, cnt * sizeof(int));
    memset(level + 1, 0, cnt * sizeof(int));
    for (int i = 1; i <= cnt; i++)
    {
        memset(next_node[i], 0, (MAXL + 1) * sizeof(int));
        memset(len[i], 0, (MAXL + 1) * sizeof(int));
    }
    cnt = 0;
}

// 扔骰子决定节点的层数
int randomLevel()
{
    int ans = 1;
    while ((std::rand() / double(RAND_MAX)) < 0.5)
    {
        ans++;
    }
    return min(ans, MAXL);
}

// 当前在i号节点的h层，返回key为num的节点，空间编号是多少
int find(int i, int h, int num)
{
    while (next_node[i][h] != 0 && key[next_node[i][h]] < num)
    {
        i = next_node[i][h];
    }
    if (h == 1)
    {
        if (next_node[i][h] != 0 && key[next_node[i][h]] == num)
        {
            return next_node[i][h];
        }
        else
        {
            return 0;
        }
    }
    return find(i, h - 1, num);
}

// 当前在i号节点的h层，num增加一个词频
void addCount(int i, int h, int num)
{
    while (next_node[i][h] != 0 && key[next_node[i][h]] < num)
    {
        i = next_node[i][h];
    }
    if (h == 1)
    {
        key_count[next_node[i][h]]++;
    }
    else
    {
        addCount(i, h - 1, num);
    }
    len[i][h]++;
}

// 当前在i号节点的h层，插入空间编号为j的节点
// 返回值：从i号节点出发，直到把空间编号为j的节点插入，底层总共有多少数字比key[j]小
// 返回值很重要，因为上游需要这个信息来改动指针的长度信息
int addNode(int i, int h, int j)
{
    int rightCnt = 0;
    while (next_node[i][h] != 0 && key[next_node[i][h]] < key[j])
    {
        rightCnt += len[i][h];
        i = next_node[i][h];
    }
    if (h == 1)
    {
        next_node[j][h] = next_node[i][h];
        next_node[i][h] = j;
        len[j][h] = key_count[next_node[j][h]];
        len[i][h] = key_count[next_node[i][h]];
        return rightCnt;
    }
    else
    {
        int downCnt = addNode(i, h - 1, j);
        if (h > level[j])
        {
            len[i][h]++;
        }
        else
        {
            next_node[j][h] = next_node[i][h];
            next_node[i][h] = j;
            len[j][h] = len[i][h] + 1 - downCnt - key_count[j];
            len[i][h] = downCnt + key_count[j];
        }
        return rightCnt + downCnt;
    }
}

// 增加num，重复加入算多个词频
void add(int num)
{
    if (find(1, MAXL, num) != 0)
    {
        addCount(1, MAXL, num);
    }
    else
    {
        key[++cnt] = num;
        key_count[cnt] = 1;
        level[cnt] = randomLevel();
        addNode(1, MAXL, cnt);
    }
}

// 当前在i号节点的h层，num减少一个词频
void removeCount(int i, int h, int num)
{
    while (next_node[i][h] != 0 && key[next_node[i][h]] < num)
    {
        i = next_node[i][h];
    }
    if (h == 1)
    {
        key_count[next_node[i][h]]--;
    }
    else
    {
        removeCount(i, h - 1, num);
    }
    len[i][h]--;
}

// 当前在i号节点的h层，删除空间编号为j的节点
void removeNode(int i, int h, int j)
{
    if (h < 1)
    {
        return;
    }
    while (next_node[i][h] != 0 && key[next_node[i][h]] < key[j])
    {
        i = next_node[i][h];
    }
    if (h > level[j])
    {
        len[i][h]--;
    }
    else
    {
        next_node[i][h] = next_node[j][h];
        len[i][h] += len[j][h] - 1;
    }
    removeNode(i, h - 1, j);
}

// 删除x，如果有多个，只删掉一个
void remove(int num)
{
    int j = find(1, MAXL, num);
    if (j != 0)
    {
        if (key_count[j] > 1)
        {
            removeCount(1, MAXL, num);
        }
        else
        {
            removeNode(1, MAXL, j);
        }
    }
}

// 当前在i号节点的h层，查询有多少个数字比num小
int small(int i, int h, int num)
{
    int rightCnt = 0;
    while (next_node[i][h] != 0 && key[next_node[i][h]] < num)
    {
        rightCnt += len[i][h];
        i = next_node[i][h];
    }
    if (h == 1)
    {
        return rightCnt;
    }
    else
    {
        return rightCnt + small(i, h - 1, num);
    }
}

// 查询num的排名
int getRank(int num)
{
    return small(1, MAXL, num) + 1;
}

int index(int i, int h, int x)
{
    int c = 0;
    while (next_node[i][h] != 0 && c + len[i][h] < x)
    {
        c += len[i][h];
        i = next_node[i][h];
    }
    if (h == 1)
    {
        return key[next_node[i][h]];
    }
    else
    {
        return index(i, h - 1, x - c);
    }
}

// 查询排名第x的key是什么
int index(int x)
{
    return index(1, MAXL, x);
}

int pre(int i, int h, int num)
{
    while (next_node[i][h] != 0 && key[next_node[i][h]] < num)
    {
        i = next_node[i][h];
    }
    if (h == 1)
    {
        return i == 1 ? INT_MIN : key[i];
    }
    else
    {
        return pre(i, h - 1, num);
    }
}

// 查询x的前驱
int pre(int num)
{
    return pre(1, MAXL, num);
}

int post(int i, int h, int num)
{
    while (next_node[i][h] != 0 && key[next_node[i][h]] < num)
    {
        i = next_node[i][h];
    }
    if (h == 1)
    {
        if (next_node[i][h] == 0)
        {
            return INT_MAX;
        }
        if (key[next_node[i][h]] > num)
        {
            return key[next_node[i][h]];
        }
        i = next_node[i][h];
        if (next_node[i][h] == 0)
        {
            return INT_MAX;
        }
        else
        {
            return key[next_node[i][h]];
        }
    }
    else
    {
        return post(i, h - 1, num);
    }
}

// 查询x的后继
int post(int num)
{
    return post(1, MAXL, num);
}

int main()
{
    srand(time(0));
    build();
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
            cout << index(x) << endl;
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