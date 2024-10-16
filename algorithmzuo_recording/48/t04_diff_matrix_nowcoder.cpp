// 二维差分模版(牛客)
// 测试链接 : https://www.nowcoder.com/practice/50e1a93989df42efb0b1dec386fb4ccc
#include <iostream>

using namespace std;

const int MAXN = 1005;

long long diff[MAXN][MAXN];

int n, m, q;

void build()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
        }
    }
}

void add(int a, int b, int c, int d, int v)
{
    diff[a][b] += v;
    diff[c + 1][b] -= v;
    diff[a][d + 1] -= v;
    diff[c + 1][d + 1] += v;
}

int main()
{
    cin >> n >> m >> q;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1, v; j <= m; ++j)
        {
            cin >> v;
            add(i, j, i, j, v);
        }
    }
    for (int i = 1, a, b, c, d, k; i <= q; i++)
    {
        cin >> a >> b >> c >> d >> k;
        add(a, b, c, d, k);
    }
    build();
    for (int i = 1; i <= n; i++)
    {
        cout << diff[i][1];
        for (int j = 2; j <= m; j++)
        {
            cout << " " << diff[i][j];
        }
        cout << endl;
    }
    return 0;
}