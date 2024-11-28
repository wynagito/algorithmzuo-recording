// 平衡因子影响替罪羊树的实验
// 一旦，max(左树节点数，右树节点数) > 平衡因子 * 整树节点数，就会发生重构
// 平衡因子范围是(0.5, 1.0)，否则无意义
// 平衡因子等于0.5时，树高很小，查询效率高，但是重构发生很频繁
// 平衡因子等于1.0时，重构完全不发生，但是树高很大，查询效率低
// 保证查询效率、同时保证重构的节点总数不多，0.7为最常用的平衡因子
// 这保证了查询效率，因为树高几乎是O(log n)
// 同时重构触发的时机合适，单次调整的均摊代价为O(log n)

#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 100001;
int key[MAXN];
int count[MAXN];
int left[MAXN];
int right[MAXN];
int size[MAXN];
int diff[MAXN];
int collect[MAXN];
int head = 0;
int cnt = 0;
double ALPHA = 0.7;
int cost = 0;

void clear()
{
    std::fill(key + 1, key + cnt + 1, 0);
    std::fill(count + 1, count + cnt + 1, 0);
    std::fill(left + 1, left + cnt + 1, 0);
    std::fill(right + 1, right + cnt + 1, 0);
    std::fill(size + 1, size + cnt + 1, 0);
    std::fill(diff + 1, diff + cnt + 1, 0);
    cnt = 0;
    head = 0;
}

int init(int num)
{
    key[++cnt] = num;
    left[cnt] = right[cnt] = 0;
    count[cnt] = size[cnt] = diff[cnt] = 1;
    return cnt;
}

void up(int i)
{
    size[i] = size[left[i]] + size[right[i]] + count[i];
    diff[i] = diff[left[i]] + diff[right[i]] + (count[i] > 0 ? 1 : 0);
}

bool balance(int i)
{
    return ALPHA * diff[i] >= std::max(diff[left[i]], diff[right[i]]);
}

void inorder(int i, int &ci)
{
    if (i != 0)
    {
        inorder(left[i], ci);
        if (count[i] > 0)
        {
            collect[++ci] = i;
        }
        inorder(right[i], ci);
    }
}

int build(int l, int r)
{
    if (l > r)
    {
        return 0;
    }
    int m = (l + r) / 2;
    int h = collect[m];
    left[h] = build(l, m - 1);
    right[h] = build(m + 1, r);
    up(h);
    return h;
}

void rebuild(int &top, int &father, int &side)
{
    if (top != 0)
    {
        int ci = 0;
        inorder(top, ci);
        if (ci > 0)
        {
            cost += ci; // 统计重构节点数
            if (father == 0)
            {
                head = build(1, ci);
            }
            else if (side == 1)
            {
                left[father] = build(1, ci);
            }
            else
            {
                right[father] = build(1, ci);
            }
        }
    }
}

void add(int &top, int &father, int &side, int num)
{
    if (head == 0)
    {
        head = init(num);
    }
    else
    {
        int i = head;
        while (true)
        {
            if (key[i] == num)
            {
                count[i]++;
                break;
            }
            else if (key[i] > num)
            {
                if (left[i] == 0)
                {
                    left[i] = init(num);
                    break;
                }
                i = left[i];
            }
            else
            {
                if (right[i] == 0)
                {
                    right[i] = init(num);
                    break;
                }
                i = right[i];
            }
            up(i);
            if (!balance(i))
            {
                top = i;
                father = (top == head) ? 0 : (side == 1 ? father : head);
                side = (top == left[i]) ? 1 : 2;
            }
        }
    }
}

// 统计树高
int deep(int i)
{
    if (i == 0)
    {
        return 0;
    }
    return std::max(deep(left[i]), deep(right[i])) + 1;
}

// 主函数
int main()
{
    ALPHA = 0.7;     // 设置平衡因子
    int max = 10000; // 设置插入范围
    std::cout << "测试开始" << std::endl;
    cost = 0; // 清空重构节点计数
    for (int num = 1; num <= max; num++)
    {
        int top = 0, father = 0, side = 0;
        add(top, father, side, num);
        rebuild(top, father, side);
    }
    std::cout << "插入数字 : " << "1~" << max << std::endl;
    std::cout << "平衡因子 : " << ALPHA << std::endl;
    std::cout << "树的高度 : " << deep(head) << std::endl; // 需要实现 deep 函数
    std::cout << "重构节点 : " << cost << std::endl;
    std::cout << "测试结束" << std::endl;
    clear();
    return 0;
}