// 粉刷木板的最大收益
// 一共有n个木板，每个木板长度为1，最多粉刷一次，也可以不刷
// 一共有m个工人，每个工人用(li, pi, si)表示：
// 该工人必须刷连续区域的木板，并且连续的长度不超过li
// 该工人每刷一块木板可以得到pi的钱
// 该工人刷的连续区域必须包含si位置的木板
// 返回所有工人最多能获得多少钱
// 1 <= n <= 16000
// 1 <= m <= 100
// 1 <= pi <= 10000
// 测试链接 : http://poj.org/problem?id=1821

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

const int MAXN = 16001;
const int MAXM = 101;

vector<vector<int>> workers(MAXM, vector<int>(3));
int dp[MAXM][MAXN];
int qu[MAXN];
int l, r;
int n, m;

int value(int i, int pi, int j)
{
    return dp[i - 1][j] - pi * j;
}

struct cmp{
    bool operator()(const vector<int> &a, const vector<int> &b) const
    {
        return a[2] < b[2];
    }
};

int compute()
{
    sort(workers.begin() + 1, workers.begin() + m + 1, cmp());
    for (int i = 1; i <= m; i++)
    {
        int li = workers[i][0];
        int pi = workers[i][1];
        int si = workers[i][2];
        l = r = 0;

        for (int j = max(0, si - li); j < si; j++)
        {
            while (l < r && value(i, pi, qu[r - 1]) <= value(i, pi, j))
            {
                r--;
            }
            qu[r++] = j;
        }

        for (int j = 1; j <= n; j++)
        {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            if (j >= si)
            {
                if (l < r && qu[l] == j - li - 1)
                {
                    l++;
                }
                if (l < r)
                {
                    dp[i][j] = max(dp[i][j], value(i, pi, qu[l]) + pi * j);
                }
            }
        }
    }
    return dp[m][n];
}

int main()
{

    while (cin >> n >> m)
    {
        for (int i = 1; i <= m; i++)
        {
            cin >> workers[i][0] >> workers[i][1] >> workers[i][2];
        }
        cout << compute() << "\n";
    }

    return 0;
}