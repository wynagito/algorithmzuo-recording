#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;

const int MAXN = 102;
int data[MAXN][MAXN];
double mat[MAXN][MAXN];
int n;
double sml = 1e-7;

void gauss(int n)
{
    for (int i = 1; i <= n; i++)
    {
        int max = i;
        for (int j = 1; j <= n; j++)
        {
            if (j < i && fabs(mat[j][j]) >= sml)
            {
                continue;
            }
            if (fabs(mat[j][i]) > fabs(mat[max][i]))
            {
                max = j;
            }
        }
        swap(mat[i], mat[max]);
        if (fabs(mat[i][i]) >= sml)
        {
            double tmp = mat[i][i];
            for (int j = i; j <= n + 1; j++)
            {
                mat[i][j] /= tmp;
            }
            for (int j = 1; j <= n; j++)
            {
                if (i != j)
                {
                    double rate = mat[j][i] / mat[i][i];
                    for (int k = i; k <= n + 1; k++)
                    {
                        mat[j][k] -= mat[i][k] * rate;
                    }
                }
            }
        }
    }
}

// 如果计算结果不是合法方案返回0
// 如果计算结果是合法方案返回最重三角形的编号
int check()
{
    gauss(n);
    double maxv = numeric_limits<double>::min();
    int maxt = 0, ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (mat[i][i] == 0)
        {
            return 0;
        }
        if (mat[i][n + 1] <= 0 || mat[i][n + 1] != (int)mat[i][n + 1])
        {
            return 0;
        }
        if (maxv < mat[i][n + 1])
        {
            maxv = mat[i][n + 1];
            maxt = 1;
            ans = i;
        }
        else if (maxv == mat[i][n + 1])
        {
            maxt++;
        }
    }
    if (maxt > 1)
    {
        return 0;
    }
    return ans;
}

void swapData(int i, int j)
{
    swap(data[i], data[j]);
}

int main()
{
    cin >> n;
    for (int i = 1, m; i <= n + 1; i++)
    {
        cin >> m;
        for (int j = 1, cur; j <= m; j++)
        {
            cin >> cur;
            data[i][cur] = 1;
        }
        cin >> data[i][n + 1];
    }

    int ans = 0, times = 0;
    for (int k = 1; k <= n + 1; k++)
    {
        swapData(k, n + 1);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n + 1; j++)
            {
                mat[i][j] = data[i][j];
            }
        }
        swapData(k, n + 1);
        int cur = check();
        if (cur != 0)
        {
            times++;
            ans = cur;
        }
    }

    if (times != 1)
    {
        cout << "illegal" << endl;
    }
    else
    {
        cout << ans << endl;
    }

    return 0;
}
