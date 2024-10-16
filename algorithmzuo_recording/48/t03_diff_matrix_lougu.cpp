// 在二维数组中，如果经历如下的过程
// 1 批量的做如下的操作，每个操作都有独立的a、b、c、d、v
// void add(a, b, c, d, v) : 左上角(a,b)到右下角(c,d)范围上，每个数字+v，怎么快速处理？
// 2 操作做完后，如何正确得到二维数组中每个位置的值？

// 这就是二维差分的主要工作，add时候快速处理，最后build得到每个位置的值，修改操作必须集中在一起，不能边修改边查询。
// 1）add方法实现，比较巧妙！
// 2）build方法实现，和处理前缀和类似
// 3）真实数据用一圈0包裹起来，可以减少很多边界讨论

// 二维差分模版(洛谷)
// 测试链接 : https://www.luogu.com.cn/problem/P3397

#include <iostream>

using namespace std;

const int MAXN = 1002;

int diff[MAXN][MAXN];

int n, q;

void build()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
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
    cin >> n >> q;
    for (int i = 1, a, b, c, d; i <= q; i++)
    {
        cin >> a >> b >> c >> d;

        add(a, b, c, d, 1);
    }
    build();
    for (int i = 1; i <= n; i++)
    {
        cout << diff[i][1];
        for (int j = 2; j <= n; j++)
        {
            cout << " " << diff[i][j];
        }
        cout << endl;
    }
    return 0;
}