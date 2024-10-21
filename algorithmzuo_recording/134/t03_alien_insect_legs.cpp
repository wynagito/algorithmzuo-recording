// 外星千足虫
// 一共有n种虫子，编号1~n，虫子腿为奇数认为是外星虫，偶数认为是地球虫
// 一共有m条虫子腿的测量记录，记录编号1~m
// 比如其中一条测量记录为，011 1，表示1号虫没参与，2号、3号虫参与了，总腿数为奇数
// 测量记录保证不会有自相矛盾的情况，但是可能有冗余的测量结果
// 也许拥有从第1号到第k号测量记录就够了，k+1~m号测量记录有或者没有都不影响测量结果
// 打印这个k，并且打印每种虫子到底是外星虫还是地球虫
// 如果使用所有的测量结果，依然无法确定每种虫子的属性，打印"Cannot Determine"
// 1 <= n <= 1000
// 1 <= m <= 2000
// 测试链接 : https://www.luogu.com.cn/problem/P2447

#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>

using namespace std;

const int BIT = 64;
const int MAXN = 2002;
const int MAXM = MAXN / BIT + 1;

long long mat[MAXN][MAXM];
int n, m, s;
int need;

int get(int row, int col);
void set(int row, int col, int v);
void eor(int row1, int row2, int bits);

// 高斯消元解决异或方程组模版 + 位图
void gauss(int n)
{
    need = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            if (get(j, i) == 1)
            {
                swap(mat[i], mat[j]);
                need = max(need, j);
                break;
            }
        }
        if (get(i, i) == 0)
        {
            return; // 一旦没有唯一解，可以结束了
        }
        for (int j = 1; j <= n; j++)
        {
            if (i != j && get(j, i) == 1)
            {
                // 因为列从1开始，所以从第1位状态开始才有用
                // 于是1~n+1列的状态，对应1~n+1位
                // 但是位图中永远有0位，只不过从来不使用
                // 于是一共有n+2位状态，都需要异或
                eor(i, j, n + 2);
            }
        }
    }
}

// 设置行row，列col的状态为v
void set(int row, int col, int v)
{
    if (v == 0)
    {
        mat[row][col / BIT] &= ~(1LL << (col % BIT));
    }
    else
    {
        mat[row][col / BIT] |= 1LL << (col % BIT);
    }
}

// 得到行row，列col的状态
int get(int row, int col)
{
    return ((mat[row][col / BIT] >> (col % BIT)) & 1) == 1 ? 1 : 0;
}

// 行row2状态 ^= 行row1状态
// 状态一共有bits位
void eor(int row1, int row2, int bits)
{
    for (int k = 0; k <= bits / BIT; k++)
    {
        mat[row2][k] ^= mat[row1][k];
    }
}

int main()
{

    cin >> n >> m;
    s = max(n, m);

    for (int i = 1; i <= m; i++)
    {
        string line;
        cin >> line;

        for (int j = 1; j <= n; j++)
        {
            set(i, j, line[j - 1] - '0');
        }
        int val;
        cin >> val;
        set(i, s + 1, val);
    }

    gauss(s);

    int sign = 1;
    for (int i = 1; i <= n; i++)
    {
        if (get(i, i) == 0)
        {
            sign = 0;
            break;
        }
    }

    if (sign == 0)
    {
        cout << "Cannot Determine" << endl;
    }
    else
    {
        cout << need << endl;
        for (int i = 1; i <= n; i++)
        {
            if (get(i, s + 1) == 1)
            {
                cout << "?y7M#" << endl;
            }
            else
            {
                cout << "Earth" << endl;
            }
        }
    }

    return 0;
}
