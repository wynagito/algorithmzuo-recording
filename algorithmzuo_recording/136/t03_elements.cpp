// 元素
// 给定n个魔法矿石，每个矿石有状态和魔力，都是整数
// 若干矿石组成的组合能否有效，根据状态异或的结果来决定
// 如果一个矿石组合内部会产生异或和为0的子集，那么这个组合无效
// 返回有效的矿石组合中，最大的魔力和是多少
// 1 <= n <= 1000
// 1 <= 状态 <= 10^18
// 1 <= 魔力 <= 10^4
// 测试链接 : https://www.luogu.com.cn/problem/P4570

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 1001;
const int BIT = 60;

vector<vector<long long>> arr(MAXN, vector<long long>(2));
long long basis[BIT + 1];
int n;

struct cmp
{
    bool operator()(const vector<long long> &a, const vector<long long> &b)
    {
        return a[1] > b[1];
    }
};

// 线性基里插入num，如果线性基增加了返回true，否则返回false
bool insert(long long num)
{
    for (int i = BIT; i >= 0; i--)
    {
        if (num >> i & 1)
        { // 判断第i位是否为1
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
// 计算得到最大线性基的最少花费
long long compute()
{
    long long ans = 0;
    sort(arr.begin() + 1, arr.begin() + n + 1, cmp());
    for (int i = 1; i <= n; i++)
    {
        if (insert(arr[i][0]))
        {
            ans += arr[i][1];
        }
    }
    return ans;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i][0] >> arr[i][1];
    }
    cout << compute() << endl;
    return 0;
}
