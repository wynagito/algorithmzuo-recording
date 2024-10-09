// 基站选址
// 一共有n个村庄排成一排，从左往右依次出现1号、2号、3号..n号村庄
// dist[i]表示i号村庄到1号村庄的距离，该数组一定有序且无重复值
// fix[i]表示i号村庄建立基站的安装费用
// range[i]表示i号村庄的接收范围，任何基站和i号村庄的距离不超过这个数字，i号村庄就能得到服务
// warranty[i]表示如果i号村庄最终没有得到任何基站的服务，需要给多少赔偿费用
// 最多可以选择k个村庄安装基站，返回总花费最少是多少，总花费包括安装费用和赔偿费用
// 1 <= n <= 20000
// 1 <= k <= 100
// k <= n
// 1 <= dist[i] <= 10^9
// 1 <= fix[i] <= 10^4
// 1 <= range[i] <= 10^9
// 1 <= warranty[i] <= 10^4
// 测试链接 : https://www.luogu.com.cn/problem/P2605

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>

using namespace std;

// 因为要补充一个村庄(无穷远处)，所以村庄编号1~20001，那么空间为20002
const int MAXN = 20002;
int n, k;

// dist 和1号村庄之间的距离
// fix 安装费用
// range 接收范围
// warranty 赔偿费用
int dist[MAXN], fix[MAXN], range[MAXN], warranty[MAXN];

// leftarr[i]表示最左在第几号村庄建基站，i号村庄依然能获得服务
// rightarr[i]表示最右在第几号村庄建基站，i号村庄依然能获得服务
int leftarr[MAXN], rightarr[MAXN];

// 链式前向星
// 保存每个村庄的预警列表，i号村庄的预警列表是指
// 如果只有一个基站建在i号村庄，现在这个基站要移动到i+1号村庄
// 哪些村庄会从有服务变成无服务的状态
int head[MAXN], nxt[MAXN], to[MAXN], cnt;

// minSeg 线段树维护最小值信息
// addarr 线段树维护加的懒更新
int minSeg[MAXN << 2], addarr[MAXN << 2];

// 动态规划表
// dp[t][i]表示最多建t个基站，并且最右的基站一定要建在i号村庄，1..i号村庄的最少花费
// 因为dp[t][i]，只依赖dp[t-1][..]，所以能空间压缩变成一维数组
int dp[MAXN];

void addEdge(int u, int v)
{
    nxt[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

// Segment Tree Functions
void up(int i)
{
    minSeg[i] = min(minSeg[i << 1], minSeg[i << 1 | 1]);
}

void down(int i)
{
    if (addarr[i] != 0)
    {
        minSeg[i << 1] += addarr[i];
        minSeg[i << 1 | 1] += addarr[i];
        addarr[i << 1] += addarr[i];
        addarr[i << 1 | 1] += addarr[i];
        addarr[i] = 0;
    }
}

void build(int l, int r, int i)
{
    if (l == r)
    {
        minSeg[i] = dp[l];
    }
    else
    {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
    addarr[i] = 0;
}

void add(int jobl, int jobr, int jobv, int l, int r, int i)
{
    if (jobl <= l && r <= jobr)
    {
        minSeg[i] += jobv;
        addarr[i] += jobv;
    }
    else
    {
        down(i);
        int mid = (l + r) >> 1;
        if (jobl <= mid)
        {
            add(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid)
        {
            add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}

int query(int jobl, int jobr, int l, int r, int i)
{
    if (jobl <= l && r <= jobr)
    {
        return minSeg[i];
    }
    down(i);
    int mid = (l + r) >> 1;
    int ans = numeric_limits<int>::max();
    if (jobl <= mid)
    {
        ans = min(ans, query(jobl, jobr, l, mid, i << 1));
    }
    if (jobr > mid)
    {
        ans = min(ans, query(jobl, jobr, mid + 1, r, i << 1 | 1));
    }
    return ans;
}

// Binary Search to find left border
int search(int d)
{
    int l = 1, r = n, ans = 0;
    while (l <= r)
    {
        int m = (l + r) / 2;
        if (dist[m] >= d)
        {
            ans = m;
            r = m - 1;
        }
        else
        {
            l = m + 1;
        }
    }
    return ans;
}

// 生成left[0..n]
// 生成right[0..n]
// 生成预警[0..n]
void prepare()
{
    cnt = 1;
    for (int i = 1; i <= n; i++)
    {
        leftarr[i] = search(dist[i] - range[i]);
        rightarr[i] = search(dist[i] + range[i]);
        if (dist[rightarr[i]] > dist[i] + range[i])
        {
            // 如果if逻辑命中
            // 说明此时right[i]上建基站，其实i号村庄是收不到信号的
            // 此时right[i]要减1
            rightarr[i]--;
        }
        // 生成预警列表
        //  比如right[3] = 17
        //  那么17号村庄的预警列表里有3
        addEdge(rightarr[i], i);
    }
}

// n是加上补充村庄(无穷远处)之后的村子数量
// 所以dp[t][n]的值代表
// 最右有一个单独的基站，去负责补充村庄，这一部分的花费是0
// 剩余有最多t-1个基站，去负责真实出现的村庄，最少的总费用
// 所以t一定要从1枚举到k+1，对应真实村子最多分到0个~k个基站的情况
// 这么做可以减少边界讨论，课上进行了图解
int compute()
{
    // Max build t = 1
    for (int i = 1, w = 0; i <= n; i++)
    {
        dp[i] = w + fix[i];
        for (int ei = head[i]; ei != 0; ei = nxt[ei])
        {
            w += warranty[to[ei]];
        }
    }

    // Max build t >= 2
    for (int t = 2; t <= k + 1; t++)
    {
        build(1, n, 1);
        for (int i = 1; i <= n; i++)
        {
            if (i >= t)
            {
                dp[i] = min(dp[i], query(1, i - 1, 1, n, 1) + fix[i]);
            }
            for (int ei = head[i], uncover; ei != 0; ei = nxt[ei])
            {
                uncover = to[ei];
                if (leftarr[uncover] > 1)
                {
                    add(1, leftarr[uncover] - 1, warranty[uncover], 1, n, 1);
                }
            }
        }
    }
    return dp[n];
}

int main()
{
    cin >> n >> k;
    for (int i = 2; i <= n; i++)
    {
        cin >> dist[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> fix[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> range[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> warranty[i];
    }
    // Add a virtual village at infinity
    dist[++n] = numeric_limits<int>::max();
    fix[n] = range[n] = warranty[n] = 0;
    prepare();
    cout << compute() << endl;
    return 0;
}