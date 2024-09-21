// 寻找最近和次近
// 给定一个长度为n的数组arr，下标1 ~ n范围，数组无重复值
// 关于近的定义，距离的定义如下:
// 对i位置的数字x来说，只关注右侧的数字，和x的差值绝对值越小就越近
// 距离为差值绝对值，如果距离一样，数值越小的越近
// 数值 : 3 5 7 1
// 下标 : 1 2 3 4
// 对1位置的数字3来说，第一近是4位置的1，距离为2；第二近是2位置的5，距离为2
// 每个位置的数字都求第一近的位置及其距离、第二近的位置及其距离
// 分别用to1、dist1、to2、dist2数组表示，0表示不存在
// 有序表的实现 + 数组手搓双向链表的实现
// 对数器验证

#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>
#include <unordered_set>
#include <random>

const int MAXN = 10001;

std::vector<int> arr(MAXN);
int n;
std::vector<int> to1(MAXN);
std::vector<int> dist1(MAXN);
std::vector<int> to2(MAXN);
std::vector<int> dist2(MAXN);

// The following three arrays are only needed for the near2 method
std::vector<std::vector<int>> rankarr(MAXN, std::vector<int>(2));
std::vector<int> last(MAXN);
std::vector<int> nextarr(MAXN);

void near1();
void near2();
void update(int i, int j);
void delete_node(int i);
void random(int v);
bool check();

struct cmp
{
    bool operator()(const std::vector<int> &a, const std::vector<int> &b) const
    {
        return a[1] < b[1];
    }
};

// Implementation using ordered set
void near1()
{
    std::set<std::vector<int>, cmp> set;
    for (int i = n; i >= 1; i--)
    {
        to1[i] = 0;
        dist1[i] = 0;
        to2[i] = 0;
        dist2[i] = 0;
        std::vector<int> cur = {i, arr[i]};
        auto it = set.lower_bound(cur);
        auto p1 = it != set.begin() ? std::prev(it) : set.end();
        auto p2 = p1 != set.end() && p1 != set.begin() ? std::prev(p1) : set.end();
        auto p3 = it;
        auto p4 = it != set.end() ? std::next(it) : set.end();
        update(i, p1 != set.end() ? (*p1)[0] : 0);
        update(i, p2 != set.end() ? (*p2)[0] : 0);
        update(i, p3 != set.end() ? (*p3)[0] : 0);
        update(i, p4 != set.end() ? (*p4)[0] : 0);
        set.insert(cur);
    }
}

// Implementation using array-based double-linked list
void near2()
{
    for (int i = 1; i <= n; i++)
    {
        rankarr[i][0] = i;
        rankarr[i][1] = arr[i];
    }
    std::sort(rankarr.begin() + 1, rankarr.begin() + n + 1,
              [](const auto &a, const auto &b)
              { return a[1] < b[1]; });
    rankarr[0][0] = 0;
    rankarr[n + 1][0] = 0;
    for (int i = 1; i <= n; i++)
    {
        last[rankarr[i][0]] = rankarr[i - 1][0];
        nextarr[rankarr[i][0]] = rankarr[i + 1][0];
    }
    for (int i = 1; i <= n; i++)
    {
        to1[i] = 0;
        dist1[i] = 0;
        to2[i] = 0;
        dist2[i] = 0;
        update(i, last[i]);
        update(i, last[last[i]]);
        update(i, nextarr[i]);
        update(i, nextarr[nextarr[i]]);
        delete_node(i);
    }
}

// Update the nearest or second nearest to the right of position i
void update(int i, int j)
{
    if (j == 0)
    {
        return;
    }
    int dist = abs(arr[i] - arr[j]);
    if (to1[i] == 0 || dist < dist1[i] || (dist == dist1[i] && arr[j] < arr[to1[i]]))
    {
        to2[i] = to1[i];
        dist2[i] = dist1[i];
        to1[i] = j;
        dist1[i] = dist;
    }
    else if (to2[i] == 0 || dist < dist2[i] || (dist == dist2[i] && arr[j] < arr[to2[i]]))
    {
        to2[i] = j;
        dist2[i] = dist;
    }
}

// Delete position i from the double-linked list
void delete_node(int i)
{
    int l = last[i];
    int r = nextarr[i];
    if (l != 0)
    {
        nextarr[l] = r;
    }
    if (r != 0)
    {
        last[r] = l;
    }
}

// Randomly generate arr[1...n] ensuring no duplicate values
void random(int v)
{
    std::unordered_set<int> set;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-v, v);
    for (int i = 1; i <= n; i++)
    {
        int cur;
        do
        {
            cur = dis(gen);
        } while (set.count(cur));
        set.insert(cur);
        arr[i] = cur;
    }
}

// The following four arrays are used for backup
std::vector<int> a(MAXN);
std::vector<int> b(MAXN);
std::vector<int> c(MAXN);
std::vector<int> d(MAXN);

// Verification process
bool check()
{
    near1();
    for (int i = 1; i <= n; i++)
    {
        a[i] = to1[i];
        b[i] = dist1[i];
        c[i] = to2[i];
        d[i] = dist2[i];
    }
    near2();
    for (int i = 1; i <= n; i++)
    {
        if (a[i] != to1[i] || b[i] != dist1[i])
        {
            return false;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (c[i] != to2[i] || d[i] != dist2[i])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    // Make sure the numbers in arr are unique, so let v be greater than n
    n = 100;
    int v = 1000;
    int testTime = 10000;
    std::cout << "测试开始" << std::endl;
    for (int i = 0; i < testTime; i++)
    {
        random(v);
        if (!check())
        {
            std::cout << "出错了!" << std::endl;
            return 0;
        }
    }
    std::cout << "测试结束" << std::endl;
    return 0;
}
