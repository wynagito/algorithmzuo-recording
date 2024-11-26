// 不含递增三元组的排列方法数
// 数字从1到n，可以形成很多排列，要求任意从左往右的三个位置，不能出现依次递增的样子
// 返回排列的方法数，答案对 1000000 取模
// 1 <= n <= 1000
// 测试链接 : https://www.luogu.com.cn/problem/SP7897
// 测试链接 : https://www.spoj.com/problems/SKYLINE

#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000;
const int MAXN = 1001;
vector<long long> f(MAXN);

void build()
{
    f[0] = f[1] = 1;
    for (int i = 2; i < MAXN; i++)
    {
        for (int l = 0, r = i - 1; l < i; l++, r--)
        {
            f[i] = (f[i] + f[l] * f[r] % MOD) % MOD;
        }
    }
}

int main()
{
    build();
    double n;
    while (true)
    {
        cin >> n;
        if (n == 0)
        {
            break;
        }
        cout << f[(int)n] << endl;
    }
    return 0;
}
