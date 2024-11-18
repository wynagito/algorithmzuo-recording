// 青蛙的约会
// 有一个周长为l的环，从环的0位置开始，规定只能沿着顺时针方向不停转圈
// 青蛙A在环的x1位置，每秒跳m个单位，青蛙B在x2位置，每秒跳n个单位
// 只有在某时刻，青蛙A和青蛙B来到环的同一个位置，才算相遇
// 如果两只青蛙相遇不了，打印"Impossible"
// 如果可以相遇，打印两只青蛙至少多久才能相遇
// 1 <= l <= 3 * 10^9
// 1 <= x1、x2、m、n <= 2 * 10^9
// x1 != x2
// 测试链接 : https://www.luogu.com.cn/problem/P1516

#include <iostream>
#include <stdexcept>

using namespace std;

// 扩展欧几里得算法
long d, x, y, px, py;

void exgcd(long a, long b)
{
    if (b == 0)
    {
        d = a;
        x = 1;
        y = 0;
    }
    else
    {
        exgcd(b, a % b);
        px = x;
        py = y;
        x = py;
        y = px - py * (a / b);
    }
}

int main()
{
    try
    {
        long x1, x2, m, n, l;

        cin >> x1 >> x2 >> m >> n >> l;

        long a, c;
        if (x1 < x2)
        {
            a = m - n;
            c = x2 - x1;
        }
        else
        {
            a = n - m;
            c = x1 - x2;
        }

        if (a < 0)
        {
            a = -a;
            c = l - c;
        }

        exgcd(a, l);

        if (c % d != 0)
        {
            cout << "Impossible" << endl;
        }
        else
        {
            // 解出的特解
            long x0 = x * c / d;
            // 单次幅度
            long xd = l / d;
            // x0调整成>=1的最小正整数
            if (x0 < 0)
            {
                x0 += (1 - x0 + xd - 1) / xd * xd;
            }
            else
            {
                x0 -= (x0 - 1) / xd * xd;
            }
            cout << x0 << endl;
        }
    }
    catch (const exception &e)
    {
        cerr << "An error occurred: " << e.what() << endl;
    }

    return 0;
}
