// 接取落水的最小花盆
// 老板需要你帮忙浇花。给出 N 滴水的坐标，y 表示水滴的高度，x 表示它下落到 x 轴的位置
// 每滴水以每秒1个单位长度的速度下落。你需要把花盆放在 x 轴上的某个位置
// 使得从被花盆接着的第 1 滴水开始，到被花盆接着的最后 1 滴水结束，之间的时间差至少为 D
// 我们认为，只要水滴落到 x 轴上，与花盆的边沿对齐，就认为被接住
// 给出 N 滴水的坐标和 D 的大小，请算出最小的花盆的宽度 W
// 测试链接 : https://www.luogu.com.cn/problem/P2698

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <climits>

using namespace std;

const int MAXN = 100005;

vector<vector<int>> arr(MAXN, vector<int>(2));
int n, d;
int maxDeque[MAXN], minDeque[MAXN];
int maxh, maxt, minh, mint;

// 当前窗口 最大值 - 最小值 是不是>=d
bool ok()
{
    int maxVal = (maxh < maxt) ? arr[maxDeque[maxh]][1] : 0;
    int minVal = (minh < mint) ? arr[minDeque[minh]][1] : 0;
    return (maxVal - minVal >= d);
}

void push(int r)
{
    while (maxh < maxt && arr[maxDeque[maxt - 1]][1] <= arr[r][1])
    {
        maxt--;
    }
    maxDeque[maxt++] = r;

    while (minh < mint && arr[minDeque[mint - 1]][1] >= arr[r][1])
    {
        mint--;
    }
    minDeque[mint++] = r;
}

void pop(int l)
{
    if (maxh < maxt && maxDeque[maxh] == l)
    {
        maxh++;
    }
    if (minh < mint && minDeque[minh] == l)
    {
        minh++;
    }
}

int compute()
{
    // arr[0...n-1][2]: x(0), 高度(1)
    // 所有水滴根据x排序，谁小谁在前
    sort(arr.begin(), arr.begin() + n, [](const vector<int> &a, const vector<int> &b)
         { return a[0] < b[0]; });

    maxh = maxt = minh = mint = 0;
    int ans = INT_MAX;

    for (int l = 0, r = 0; l < n; l++)
    {
        // [l,r) : 水滴的编号
        // l : 当前花盘的左边界，arr[l][0]
        while (!ok() && r < n)
        {
            push(r++);
        }
        if (ok())
        {
            ans = min(ans, arr[r - 1][0] - arr[l][0]);
        }
        pop(l);
    }
    return ans;
}

int main()
{

    while (cin >> n >> d)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i][0] >> arr[i][1];
        }
        int ans = compute();
        cout << (ans == INT_MAX ? -1 : ans) << '\n';
    }

    return 0;
}