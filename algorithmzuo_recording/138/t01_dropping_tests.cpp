// 01分数规划最简化的问题
// 给定n个数据，每个数据有(a, b)两个值，并且没有负数
// (a1, b1)、(a2, b2)、(a3, b3)、.. (an, bn)
// 其中选出k个数据，希望让 : k个a的和 / k个b的和，这个比值尽量大，返回最大的比值

// 错误的贪心：选择a/b最大的前k个数据，反例：(5, 5)  (0, 1)  (2, 6)
// 暴力方法 : 2的n次方，每个数据都枚举要和不要两种选择
// 计算机里关于小数的精度是有限的 或者 具体题目要求返回的比值精度也是规定好的
// 那么此时没有必要精确求解，可以用二分答案法来逼近求解，保证规定精度内正确即可

// 01分数规划的核心：
// 数据转化成结余表达式的形式，当确定一个比值x，就在最优决策下，计算结余和
// 最终希望获得在最优决策下，当结余和最接近0时，x的值
// 手段：利用单调性进行二分

// 二分答案法找到最大比值的过程
// 数据这么来看 :
// a1 - x * b1 = 结余1
// a2 - x * b2 = 结余2
// a3 - x * b3 = 结余3
// ..

// 规定精度的最小单位sml，找到x的可能范围[l, r]，然后二分逻辑如下：
// 首先令x = (l + r) / 2，计算每一个结余，然后选出结余最大的前k名，然后加起来看看累加和
// 1) 如果 结余累加和 >= 0，答案更新成此时的x，然后去右侧二分，范围变成[x + sml, r]
// 2) 如果 结余累加和 <  0，答案不更新，然后去左侧二分，范围变成[l, x - sml]
// 3) 如果发现范围[l,r]的大小 <= sml，过程停止，返回答案即可
// 时间复杂度O(n * logn * logv)

// 01分数规划模版题
// 给定n个数据，每个数据有(a, b)两个值，都为整数，并且都是非负的
// 请舍弃掉k个数据，希望让剩下数据做到，所有a的和 / 所有b的和，这个比值尽量大
// 如果剩下数据所有b的和为0，认为无意义
// 最后，将该比值 * 100，小数部分四舍五入的整数结果返回
// 1 <= n <= 100
// 0 <= a、b <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/P10505
// 测试链接 : http://poj.org/problem?id=2976

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 1001;
const double sml = 1e-6;

// arr[i][0] = i号数据的a
// arr[i][1] = i号数据的b
// arr[i][2] = i号数据的结余，a - x * b
vector<vector<double>> arr(MAXN, vector<double>(3));
int n, k;

bool check(double x)
{
    // x固定的情况下，得到所有数据的结余
    for (int i = 1; i <= n; i++)
    {
        arr[i][2] = arr[i][0] - x * arr[i][1];
    }
    // 结余从大到小排序
    sort(arr.begin() + 1, arr.begin() + n + 1, [](const vector<double> &o1, const vector<double> &o2)
         { return o1[2] > o2[2]; });
    // 最大k个结余的累加和
    double sum = 0;
    for (int i = 1; i <= k; i++)
    {
        sum += arr[i][2];
    }
    return sum >= 0;
}

int main()
{

    while (true)
    {
        cin >> n >> k;
        if (n == 0 && k == 0)
            break;

        k = n - k; // 题目要求舍弃掉k个，其实就是挑选n-k个

        for (int i = 1; i <= n; i++)
        {
            cin >> arr[i][0];
        }
        for (int i = 1; i <= n; i++)
        {
            cin >> arr[i][1];
        }

        double l = 0, r = 0, x;
        for (int i = 1; i <= n; i++)
        {
            r += arr[i][0];
        }
        double ans = 0;

        while (l < r && r - l >= sml)
        {
            x = (l + r) / 2;
            if (check(x))
            {
                ans = x;
                l = x + sml;
            }
            else
            {
                r = x - sml;
            }
        }

        cout << static_cast<int>(100 * (ans + 0.005)) << '\n';
    }

    return 0;
}