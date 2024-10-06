// 打印n层汉诺塔问题的最优移动轨迹

#include <iostream>
#include <string>

using namespace std;

void f(int i, string from, string to, string other);

// 左 中 右
// 1
// 2
// 3

// 移动圆盘 1 从 左 到 右
// 移动圆盘 2 从 左 到 中
// 移动圆盘 1 从 右 到 中
// 移动圆盘 3 从 左 到 右
// 移动圆盘 1 从 中 到 左
// 移动圆盘 2 从 中 到 右
// 移动圆盘 1 从 左 到 右

//       1
//       2
//       3
void hanoi(int n)
{
    if (n > 0)
    {
        f(n, "左", "右", "中");
    }
}

void f(int i, string from, string to, string other)
{
    if (i == 1)
    {
        cout << "移动圆盘 1 从 " << from << " 到 " << to << endl;
    }
    else
    {
        f(i - 1, from, other, to);
        cout << "移动圆盘 " << i << " 从 " << from << " 到 " << to << endl;
        f(i - 1, other, to, from);
    }
}

int main()
{
    int n = 3;
    hanoi(n);
    return 0;
}