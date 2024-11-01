// 彩灯
// 一共有n个灯泡，开始都是不亮的状态，有m个开关
// 每个开关能改变若干灯泡的状态，改变是指，亮变不亮、不亮变亮
// 比如n=5，某个开关为XXOOO，表示这个开关只能改变后3个灯泡的状态
// 可以随意使用开关，返回有多少种亮灯的组合，全不亮也算一种组合
// 答案可能很大，对 2008 取模
// 1 <= n <= 50
// 1 <= m <= 50
// 测试链接 : https://www.luogu.com.cn/problem/P3857

#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 51;
const int MOD = 2008;

long arr[MAXN];
long basis[MAXN];
int n, m;

// 线性基里插入num，如果线性基增加了返回true，否则返回false
bool insert(long num)
{
    for (int i = n; i >= 0; i--)
    {
        if ((num >> i) & 1)
        {
            if (basis[i] == 0)
            {
                basis[i] = num;
                return true;
            }
            num ^= basis[i];
        }
    }
    return false;
}

// 普通消元
// 计算线性基的大小
int compute()
{
    int size = 0;
    for (int i = 1; i <= m; i++)
    {
        if (insert(arr[i]))
        {
            size++;
        }
    }
    return size;
}

int main()
{
    cin >> n;
    cin >> m;
    n--; // 根据原代码，n应该减1
    char s[MAXN];

    for (int i = 1; i <= m; i++)
    {
        cin >> s;
        long num = 0;
        for (int j = 0; j <= n; j++)
        {
            if (s[j] == 'O')
            {
                num |= (1L << j);
            }
        }
        arr[i] = num;
    }
    int size = compute();
    cout << (1LL << size) % MOD << endl;

    return 0;
}
