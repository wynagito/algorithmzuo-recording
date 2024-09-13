// 过河踩过的最少石子数
// 在河上有一座独木桥，一只青蛙想沿着独木桥从河的一侧跳到另一侧
// 在桥上有一些石子，青蛙很讨厌踩在这些石子上
// 我们可以把独木桥上青蛙可能到达的点看成数轴上的一串整点0...n
// 其中n是桥的长度，坐标为0的点表示桥的起点，坐标为n的点表示桥的终点
// 青蛙从桥的起点开始，不停的向终点方向跳跃，一次跳跃的距离是[s,t]之间的任意正整数
// 当青蛙跳到或跳过坐标为n的点时，就算青蛙已经跳出了独木桥
// 题目给出独木桥的长度n，青蛙跳跃的距离范围s、t，题目还给定m个桥上石子的位置
// 你的任务是确定青蛙要想过河，最少需要踩到的石子数
// 1 <= n <= 10^7
// 1 <= s <= t <= 10
// 1 <= m <= 100
// 测试链接 : https://www.luogu.com.cn/problem/P1052

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 101;
const int MAXL = 100001;
const int MAXK = 201;

int arr[MAXN];
int where[MAXN];
int dp[MAXL];
bool stone[MAXL];
bool reach[MAXK];

int n, s, t, m, safe;

int reduce(int s, int t)
{
    fill(reach, reach + MAXK, false);
    int cnt = 0;
    int ans = 0;
    for (int i = 0; i < MAXK; i++)
    {
        for (int j = i + s; j < min(i + t + 1, MAXK); j++)
        {
            reach[j] = true;
        }
        if (!reach[i])
        {
            cnt = 0;
        }
        else
        {
            cnt++;
        }
        if (cnt == t)
        {
            ans = i;
            break;
        }
    }
    return ans;
}

int compute()
{
    sort(arr + 1, arr + m + 1);
    if (s == t)
    {
        int ans = 0;
        for (int i = 1; i <= m; i++)
        {
            if (arr[i] % s == 0)
            {
                ans++;
            }
        }
        return ans;
    }
    else
    { // s < t
        safe = reduce(s, t);
        for (int i = 1; i <= m; i++)
        {
            where[i] = where[i - 1] + min(arr[i] - arr[i - 1], safe);
            stone[where[i]] = true;
        }
        n = where[m] + safe;
        fill(dp, dp + n + 1, MAXN);
        dp[0] = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = max(i - t, 0); j <= i - s; j++)
            {
                dp[i] = min(dp[i], dp[j] + (stone[i] ? 1 : 0));
            }
        }
        int ans = MAXN;
        for (int i = where[m] + 1; i <= n; i++)
        {
            ans = min(ans, dp[i]);
        }
        return ans;
    }
}

int main()
{

    cin >> n >> s >> t >> m;
    for (int i = 1; i <= m; ++i)
    {
        cin >> arr[i];
    }

    cout << compute() << endl;

    return 0;
}
