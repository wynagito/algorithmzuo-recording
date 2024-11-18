// 机器人的移动区域
// 二维网格中只有x和y的值都为整数的坐标，才叫格点
// 某个机器人从格点(0,0)出发，每次机器人都走直线到达(x + dx, y + dy)的格点
// 一共移动n次，每次的(dx, dy)都给定，途中路线不会交叉，输入保证机器人最终回到(0,0)
// 机器人走的路线所围成的区域一定是多边形，输入保证机器人一定沿着逆时针方向行动
// 返回多边形的内部一共几个格点，多边形的边上一共几个格点，多边形的面积
// 3 <= n <= 100
// -100 <= dx、dy <= 100
// 测试链接 : http://poj.org/problem?id=1265

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

long gcd(long a, long b)
{
    return b == 0 ? a : gcd(b, a % b);
}

int main()
{
    int cases;
    cin >> cases;

    for (int t = 1; t <= cases; t++)
    {
        int n;
        cin >> n;

        int edges = 0;
        double area = 0;
        int x = 0, y = 0;

        for (int i = 1; i <= n; i++)
        {
            int dx, dy;
            cin >> dx >> dy;

            // 使用gcd计算边界上的格点数
            edges += gcd(abs(dx), abs(dy));

            // 应用鞋带公式
            area += x * (y + dy) - (x + dx) * y;
            x += dx;
            y += dy;
        }

        // 鞋带公式最后要/2
        area /= 2;

        // 根据Pick定理计算内部格点数
        int inners = static_cast<int>(area) - edges / 2 + 1;

        cout << "Scenario #" << t << ":\n";
        cout << inners << " " << edges << " ";
        cout << fixed << setprecision(1) << area << "\n\n";
    }

    return 0;
}